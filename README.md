# NSS packages for OpenWrt on IPQ50xx (IPQ5018)

An OpenWrt package feed for Qualcomm NSS offload on IPQ5018: the NSS driver,
ECM, the NSS clients and qdiscs, the firmware and the SQM scripts. It is the
companion of the `c3po-tag-8021q` branch of
[kuncy7/openwrt-nss-edma](https://github.com/kuncy7/openwrt-nss-edma), which
runs the NSS core on top of OpenWrt's upstream `stmmac` ethernet driver
instead of `qca-nss-dp` and `qca-ssdk`. The build and runtime story is in
that tree's `README.ipq50xx.md`, and prebuilt images are on its
[Releases page](https://github.com/kuncy7/openwrt-nss-edma/releases).

The working branch is **`ipq50xx-rebase`**. The repository's default branch,
`edma-nss`, is an old copy of the feed this one was forked from and is not
what the tree builds.

## Where this feed comes from

It is a fork of Julius Bairaktaris's `nss-packages`, branch `edma-nss`: the
vendor NSS stack on the upstream `qca_edma` and `qca_ppe` drivers of IPQ807x
and IPQ60xx. In October 2026 that project became
[PPE-NSS](https://github.com/JuliusBairaktaris/openwrt-ppe-nss), which has
no vendor stack and needs no feed, and `edma-nss` is archived. IPQ5018 has
no PPE, so this branch stays on the vendor stack and carries the feed by
itself from here on. Its base is `edma-nss` at the `vendor-nss-archive` tag
(10 October 2026).

The IPQ807x and IPQ60xx parts are still in the feed as they were, but
nothing here builds or tests them. For those SoCs use
[openwrt-ppe-nss](https://github.com/JuliusBairaktaris/openwrt-ppe-nss).

| Branch | What |
|---|---|
| `ipq50xx-rebase` | The working branch. Pull requests go here. |
| `ipq50xx-nss` | Archive of the series before the rebase. |
| `julius-archive/vendor-nss-archive` | The base of `ipq50xx-rebase`: `edma-nss` at its `vendor-nss-archive` tag. |
| `julius-archive/edma-nss` | The final state of `edma-nss`. |
| `julius-archive/edma-nss-7.3-feed-20261011` | The feed for the 7.3 testing kernel. |

The source archives of `qca-nss-drv`, `qca-nss-ecm`, `qca-nss-clients` and
`nss-userspace-oss` are downloaded from the
[`nss-source-tarballs` release](https://github.com/kuncy7/nss-packages/releases/tag/nss-source-tarballs)
of this repository. It is a byte-for-byte copy of the release of the same
name in the original feed.

## What this branch has on top

Julius's patches are kept as he has them. What differs:

- **`nss-firmware`: the 12.2 line as well.**
  `NSS_FIRMWARE_VERSION_12_2` installs `NSS.FW.12.2-156-MP.R` from the same
  tarball - the newest firmware published for IPQ5018 and the one most
  ipq50xx measurements were taken on.
- **The stack builds on ipq50xx.** `qca-nss-drv` gets its `nss-dp` API from
  `qca-dwmac-nss` there (from `qca-ppe-nss` on the PPE SoCs); the bridge
  manager stays a PPE package; the VLAN manager compiles its PPE half only
  on the PPE SoCs (`qca-nss-clients` `0054`). The 256 MB boards default to
  the LOW memory profile.
- **`qca-nss-drv`**: `0120` (deassert all UBI0 reset lines), `0121`
  (`nss_vlan` refuses messages until its handler is registered), `0136`
  (park the core before copying the firmware over it - the warm-reboot
  fix), `0138` (core clock first, enabled before its rate is set), `0141`
  (idle samples in the CPU utilisation average), `0144` (the wifili peer
  statistics layout of the 12.2 firmware), `0146` (the build picks the
  default QoS memory pool size), `0122`/`0123` (coredump and firmware log
  ring on demand; inert unless used). His `0111` carries one change: the
  N2H descriptor is bounded by the skb's real capacity, because the 12.2
  firmware sends wifili statistics larger than `max_buf_size`.
- **`qca-nss-ecm` on tag_8021q DSA ports**: a DSA user port whose switch
  talks 802.1Q to the CPU is a VLAN upper of its conduit (`0051`); a port of
  a VLAN-aware bridge carries the flow's VLAN, with the endpoint on the
  conduit and the firmware VLAN interface from `qca-dsa-nss` (`0052`); a
  routed flow gets each side's own bridge VLAN (`0053`); a tagged port that
  is not a DSA port stays on the host and the VLAN of a bridged flow is
  found once for both directions (`0054`, `0055`); a bridged flow to one of
  the box's own addresses stays on the host and rules check their source
  interface by default on ipq50xx (`0056`, `0057`) - the two things a guest
  network behind an access point needs. His `0048` (ports behind a qca-8021q
  switch) is not carried: `0051` and `0052` cover it and more.
- **Multicast through ECM is built off on ipq50xx** until it is measured
  with the DSA port nodes.
- **`sqm-scripts-nss`**: on a switch conduit only the WAN flows are shaped,
  each direction in its own class.

## Packages

| Package | Source | Version |
|---|---|---|
| `qca-nss-drv` | [lklm/nss-drv](https://git.codelinaro.org/clo/qsdk/oss/lklm/nss-drv) | `win.nss.1.0.r39`, `705629d` |
| `qca-nss-ecm` | [lklm/qca-nss-ecm](https://git.codelinaro.org/clo/qsdk/oss/lklm/qca-nss-ecm) | `win.nss.1.0.r39`, `7894b76` |
| `qca-nss-clients` | [lklm/nss-clients](https://git.codelinaro.org/clo/qsdk/oss/lklm/nss-clients) | `NHSS.QSDK.12.5.5`, `51be82d` |
| `nss-userspace-oss` | [nss-userspace](https://git.codelinaro.org/clo/qsdk/oss/nss-userspace) | `win.nss.1.0.r39`, `dc142b3` |
| `nss-firmware` | [qosmio/qca-sdk-nss-fw](https://github.com/qosmio/qca-sdk-nss-fw) | 12.2 release 156 (IPQ5018), 12.5 release 210, or 11.4.0.5 release 6 |
| `sqm-scripts-nss` | local | `nss-edma.qos` queue setup for SQM |

`qca-nss-clients` has no 14.0 branch. Only the modules this stack uses are
built: PPPoE, VLAN and bridge managers, the NSS qdisc, ingress shaping
(IGS), netlink, mirror and the Wi-Fi mesh manager. `nss-userspace-oss`
builds `libnl-nss` and `nssinfo`.

The default is 12.5-210 on every target, ipq50xx included: the ipq50xx
release images carry it since 2026-10-15, and on IPQ5018 it carries the same
traffic as 12.2. 12.2-156 stays selectable (`NSS_FIRMWARE_VERSION_12_2`).
A `.config` that already names a version keeps it.

The OpenWrt packaging comes from
[qosmio/nss-packages](https://github.com/qosmio/nss-packages).

## Runtime behaviour

No module loads at boot. NSS offload is enabled at runtime, and the ECM and
SQM scripts refuse to start until the NSS data plane is up. How the plane
comes up on IPQ5018 is described in the tree's `README.ipq50xx.md`.

## Building

The tree's `feeds.conf.default` already names the feed. In a `feeds.conf`
of your own it is:

```
src-git nss https://github.com/kuncy7/nss-packages.git;ipq50xx-rebase
```

Select `nss-tools-dwmac` in the tree's menuconfig, as `<*>`. It pulls in
every kernel module the IPQ5018 plane needs.

## Acknowledgements

- [Julius Bairaktaris](https://github.com/JuliusBairaktaris) for the feed
  this is forked from. His work can be supported through
  [GitHub Sponsors](https://github.com/sponsors/JuliusBairaktaris) or
  [PayPal](https://paypal.me/JuliusBairaktaris).
- [qosmio/nss-packages](https://github.com/qosmio/nss-packages) for the
  packaging, the kernel compatibility patches and the firmware tarballs.
- [Christian Marangi (Ansuel)](https://github.com/Ansuel) for the upstream
  EDMA and PPE drivers.
- [Robert Marko (robimarko)](https://github.com/robimarko) for maintaining the
  OpenWrt qualcommax target.
