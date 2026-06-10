# NSS packages for the OpenWrt qualcommax EDMA stack

This is an OpenWrt package feed that runs the Qualcomm NSS offload stack
(the UBI32 NSS cores in IPQ807x) **on top of OpenWrt main's upstream
qualcommax ethernet drivers** (`qca_edma`/`qca_ppe`, from
[openwrt/openwrt#22381](https://github.com/openwrt/openwrt/pull/22381)) —
not on the classic vendor pairing of `qca-nss-dp` + `qca-ssdk`.

It is developed and validated on a Xiaomi AX3600 (IPQ8071A, 512 MB RAM,
NSS firmware `NSS.FW.12.5-210-HK.R`) running PPPoE at 300 Mbit/s with
ECM NAT/PPPoE acceleration and NSS SQM shaping.

The companion OpenWrt tree (kernel patches, the `kmod-qca-ppe-nss` glue
package, device tree changes) lives at
[JuliusBairaktaris/openwrt-nss-edma](https://github.com/JuliusBairaktaris/openwrt-nss-edma),
branch `nss-edma-rework`.

## Tree layout and provenance

The base of this branch is the **CodeLinaro QSDK `nss-host` feed,
branch `win.nss.1.1`**
(<https://git.codelinaro.org/clo/qsdk/oss/system/feeds/nss-host>), with
its full history preserved (also mirrored here as the `win.nss.1.1`
branch). `win.nss.1.1` was chosen because it is the most recent line
Qualcomm maintains that still carries IPQ807x support: the nominally
higher `win.nss.1.10` is an April 2025 snapshot fully contained in it.

### Why win.nss.1.1 host sources with 12.5 firmware

The newest NSS firmware Qualcomm has ever published for IPQ807x is
`NSS.FW.12.5-210` from the 2024 SPF 12.5 release (the official
[quic/qca-sdk-nss-fw](https://github.com/quic/qca-sdk-nss-fw) stops at
SPF 12.0; qosmio's fork adds SPF 12.1–12.5; nothing newer exists
publicly, in particular no firmware matching the `win.nss.*` host
lines). Nominally that firmware pairs with the `NHSS.QSDK.12.5.x` host
branches — but those branches froze in 2024 (nss-drv in April 2024)
and predate kernel API changes that the maintained `win.nss.1.1` line
absorbed upstream, so basing on them was measured to mean *more*
local compatibility patches that this tree would then own forever,
on top of a code base with two fewer years of upstream fixes. The
mixed pairing — `win.nss.1.1` host sources driving the 12.5-210
firmware — is the configuration this stack was brought up and
soak-tested on, and the same pairing the community NSS builds run.
The driver/firmware wire interface is verified at runtime, not
assumed.

On top of that base sit a small number of commits that:

1. trim the working tree to the packages this stack uses,
2. convert each package to build standalone on OpenWrt main
   (pinned CodeLinaro sources instead of QSDK's `local-development.mk`
   and local `qca/src` trees), based on the packaging work in
   [qosmio/nss-packages](https://github.com/qosmio/nss-packages),
3. carry the kernel/toolchain compatibility patch queues (5.15 → 6.12),
   also from qosmio/nss-packages, rebased where the newer sources
   require it,
4. adapt the stack to the EDMA data plane (see below).

## Packages and source pins

| Package | Source | Pin | Why this pin |
|---|---|---|---|
| `qca-nss-drv` | [oss/lklm/nss-drv](https://git.codelinaro.org/clo/qsdk/oss/lklm/nss-drv) | `6aa14c7` (2025-12-26) | Tip of `win.nss.1.1`. Identical to the revision this stack was brought up on plus one trivial nss_crypto bounds fix. Proven against firmware 12.5-210 on IPQ807x. |
| `qca-nss-ecm` | [oss/lklm/qca-nss-ecm](https://git.codelinaro.org/clo/qsdk/oss/lklm/qca-nss-ecm) | `fafe228` (2026-01-16) | Tip of `win.nss.1.1` — the most recent ECM that exists, with the NSS front-end fully retained. |
| `qca-nss-clients` | [oss/lklm/nss-clients](https://git.codelinaro.org/clo/qsdk/oss/lklm/nss-clients) | `51be82d` (2024-09-11) | Tip of `NHSS.QSDK.12.5.5` — the most recent nss-clients commit that exists anywhere; the legacy NSS clients were never carried into the `win.*` lines. |
| `nss-firmware` | [qosmio/qca-sdk-nss-fw](https://github.com/qosmio/qca-sdk-nss-fw) | 12.5 Release 210 | The firmware line the driver source is pinned against (`NSS.FW.12.5-210-HK.R` on IPQ807x). |
| `sqm-scripts-nss` | local `files/` | — | NSS shaper integration for sqm-scripts. Ships exactly one queue setup script, `nss-edma.qos`, written for and verified on this stack. |

`qca-nss-clients` is trimmed to the three modules this stack uses
(the NSS qdisc, the ingress-shaping action and the PPPoE connection
manager); the other managers, their compatibility patches and init
scripts are intentionally not carried.

## How the EDMA data plane integration works

The classic NSS stack replaces the ethernet driver: `qca-nss-dp`
registers the GMAC netdevs and hands the data plane to the NSS cores,
with `qca-ssdk` programming the switch. This tree keeps OpenWrt main's
upstream `qca_edma` ethernet driver and DSA switch driver, and inserts a
small glue module (`kmod-qca-ppe-nss`, in the companion OpenWrt tree)
which:

- exports the six `nss_dp_*` symbols `qca-nss-drv` consumes
  (`nss_data_plane/nss_data_plane.c` is the driver's entire nss-dp
  surface),
- implements data-plane override per physical port: TX is redirected
  from `qca_edma`'s xmit into the NSS conduit, RX arrives via
  `nss_dp_receive` callbacks from the firmware,
- replays the port bring-up sequence the firmware expects
  (vsi_assign → MAC → MTU → open → link state) and re-asserts the
  PPE VSI flood masks the firmware clears.

Key consequences (all verified on hardware, not theory):

- **The IPQ807x EDMA block is shared between the host and the NSS
  firmware.** Once the firmware boots it remaps the PPE queue-to-ring
  delivery (QID2RID) so that *all* wired RX goes to firmware-owned
  rings. There is **no mixed mode**: with firmware up, every physical
  port must be attached to the NSS data plane, or it loses RX.
- **Nothing in this stack autoloads.** Loading `qca-nss-drv` boots the
  firmware; doing that before the glue is armed kills all wired RX
  until reboot. Bring-up is an explicit runtime sequence (load glue,
  arm `fw_mask`, load `qca-nss-drv`, attach ports, then optionally ECM,
  PPPoE manager and SQM). The init scripts in these packages
  deliberately do not start anything at boot, and the ECM and SQM
  scripts refuse to load their modules if `qca_nss_drv` is not already
  loaded.
- `qca-nss-drv` is built without PPE virtual-port support
  (`nss_ppe_vp.c` is the only ssdk consumer in the driver; ECM does not
  use ppe_vp).
- The NSS qdisc is built without PPE shaper and NSS-bridge support;
  the firmware accel mode (`accel_mode 0`) used by SQM is unaffected.
- bonding/LAG support is compiled out (the kernel-side hooks come from
  QSDK kernel patches this tree does not carry).

## Building

In `feeds.conf`:

```
src-link nss /path/to/this/repo
```

Minimum config for the validated AX3600 setup:

```
CONFIG_PACKAGE_kmod-qca-nss-drv=y
CONFIG_PACKAGE_kmod-qca-nss-ecm=y
CONFIG_PACKAGE_kmod-qca-nss-drv-pppoe=y     # PPPoE offload
CONFIG_PACKAGE_kmod-qca-nss-drv-qdisc=y     # NSS qdiscs for SQM
CONFIG_PACKAGE_kmod-qca-nss-drv-igs=y
CONFIG_PACKAGE_sqm-scripts-nss=y
CONFIG_NSS_FIRMWARE_VERSION_12_5=y
CONFIG_NSS_MEM_PROFILE_MEDIUM=y             # 512 MB boards (AX3600)!
```

`nss-firmware` is pulled in automatically by `kmod-qca-nss-drv` on
qualcommax. **Pick the memory profile to match your board's RAM** —
the Config.in default for ipq807x is the 1 GB profile, which is wrong
for 512 MB devices like the AX3600.

The NSS feature switches (`CONFIG_NSS_DRV_*`) follow the packages you
select (e.g. the PPPoE manager forces `NSS_DRV_PPPOE_ENABLE`); IPv4 is
always on, IPv6 follows global IPv6 support.

## Acknowledgements

- The OpenWrt packaging conversion, the 5.15–6.12 kernel compatibility
  patch queues and the prepackaged firmware tarballs come from
  [qosmio/nss-packages](https://github.com/qosmio/nss-packages) and the
  community NSS builds lineage it curates. This tree would not exist
  without that work.
- The EDMA driver rework this stack runs on is Ansuel's
  [openwrt/openwrt#22381](https://github.com/openwrt/openwrt/pull/22381).
