include $(TOPDIR)/rules.mk

# nss-edma.qos is this tree's own SQM script: derived from nss-zk.qos
# (https://github.com/JuliusBairaktaris/sqm-scripts-nss @ a8c393c) and
# curated for the EDMA stack with fw-verified behavior notes (shaping
# point, encapsulation effects, no fw ECN marking, pbuf-aware queue
# limit cap) -- see the script header. It carries an EDMA boot-safety
# addition: the script refuses to load the NSS qdisc modules while
# qca-nss-drv is not already loaded, because modprobing them would
# boot the NSS firmware with no armed ports and kill all wired RX
# (same failure mode as the M3 ECM boot incident). SQM's interface
# hotplug retries once the NSS data plane is up.
PKG_NAME:=sqm-scripts-nss
PKG_VERSION:=20260215
PKG_RELEASE:=3

include $(INCLUDE_DIR)/package.mk

define Package/sqm-scripts-nss
  SECTION:=net
  CATEGORY:=Base system
  TITLE:=SQM Scripts (QoS for NSS)
  DEPENDS:=+sqm-scripts +kmod-qca-nss-drv-qdisc +kmod-qca-nss-drv-igs
  PKGARCH:=all
endef

define Package/sqm-scripts-nss/description
  Smart Queue Management scripts for NSS-accelerated shaping
  (nsstbl + nssfq_codel via nss-edma.qos).
endef

define Build/Compile
endef

define Package/sqm-scripts-nss/install
	$(INSTALL_DIR) $(1)/usr/lib/sqm
	$(INSTALL_DATA) ./files/nss-edma.qos $(1)/usr/lib/sqm/
	$(INSTALL_DATA) ./files/nss-edma.qos.help $(1)/usr/lib/sqm/
endef

$(eval $(call BuildPackage,sqm-scripts-nss))
