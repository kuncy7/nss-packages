include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=qca-nss-netfn
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=master
PKG_RELEASE:=1

include $(INCLUDE_DIR)/local-development.mk
ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_VERSION:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
endif

PKG_BUILD_DEPENDS :=
MAKE_OPTS:=
MAKE_OPTS+=NETFN_FLOWMGR_AE_PPE_ENABLE=y
MAKE_OPTS+=NETFN_FLOWMGR_AE_SFE_ENABLE=y

include $(INCLUDE_DIR)/package.mk

ifeq ($(CONFIG_TARGET_ipq),y)
subtarget:=$(SUBTARGET)
else
subtarget:=$(CONFIG_TARGET_BOARD)
endif

define KernelPackage/qca-nss-netfn-pkt-steer
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Support
  DEPENDS:=@TARGET_ipq53xx
  TITLE:=NSS network function for pkt steer
  FILES:=$(PKG_BUILD_DIR)/offload/pkt_steer/qca-nss-netfn-pkt-steer.ko
  AUTOLOAD:=$(call AutoLoad,53,qca-nss-netfn-pkt-steer)
endef

ifneq ($(CONFIG_PACKAGE_kmod-qca-nss-netfn-pkt-steer),)
MAKE_OPTS+=pkt_steer=y
endif

define KernelPackage/qca-nss-netfn-pkt-steer/Description
NSS network function for pkt steer.
endef

define KernelPackage/qca-nss-netfn-pkt-steer/install
	$(INSTALL_DIR) $(1)/usr/bin
endef

define KernelPackage/qca-nss-netfn-capwap
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Support
  DEPENDS:=@TARGET_ipq53xx \
	  +kmod-qca-nss-ppe \
	  +kmod-qca-nss-ppe-vp \
	  +kmod-qca-nss-netfn-pkt-steer
  TITLE:=NSS network function capwap offload
  FILES:=$(PKG_BUILD_DIR)/offload/capwap/qca-nss-netfn-capwap.ko
endef

ifneq ($(CONFIG_PACKAGE_kmod-qca-nss-netfn-capwap),)
MAKE_OPTS+=capwap=y
endif

define KernelPackage/qca-nss-netfn-capwap/Description
NSS network function capwap offload module.
endef

define KernelPackage/qca-nss-netfn-capwap/install
	$(INSTALL_DIR) $(1)/usr/bin
endef

define KernelPackage/qca-nss-flowmgr
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Devices
  TITLE:=Kernel driver for Network function manager
  DEPENDS:=@TARGET_ipq53xx \
	  +kmod-qca-nss-ppe \
	  +kmod-qca-nss-sfe
  FILES:=$(PKG_BUILD_DIR)/mgr/flowmgr/qca-nss-flowmgr.ko
  AUTOLOAD:=$(call AutoLoad,50,qca-nss-flowmgr)
endef

define KernelPackage/qca-nss-flowmgr/Description
Networking module for network function flow manager.
endef

define Build/InstallDev/qca-nss-flowmgr
	$(INSTALL_DIR) $(1)/usr/include/qca-nss-netfn
	$(CP) $(PKG_BUILD_DIR)/exports/* $(1)/usr/include/qca-nss-netfn/
endef

define Build/InstallDev
        $(call Build/InstallDev/qca-nss-flowmgr,$(1))
endef

EXTRA_CFLAGS+= \
	-I$(PKG_BUILD_DIR)/exports \
	-I$(PKG_BUILD_DIR)/offload/exports \
	-I$(STAGING_DIR)/usr/include/qca-nss-ppe \
	-I$(STAGING_DIR)/usr/include/qca-nss-sfe

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" $(strip $(MAKE_OPTS)) \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		M="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,qca-nss-netfn-capwap))
$(eval $(call KernelPackage,qca-nss-netfn-pkt-steer))
$(eval $(call KernelPackage,qca-nss-flowmgr))
