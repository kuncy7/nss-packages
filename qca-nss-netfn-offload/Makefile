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
MAKE_OPTS+=capwap=y
MAKE_OPTS+=pkt_steer=y

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
  AUTOLOAD:=$(call AutoLoad,54,qca-nss-netfn-capwap)
endef

define KernelPackage/qca-nss-netfn-capwap/Description
NSS network function capwap offload module.
endef

define KernelPackage/qca-nss-netfn-capwap/install
	$(INSTALL_DIR) $(1)/usr/bin
endef

EXTRA_CFLAGS+= -I$(PKG_BUILD_DIR)/exports -I$(STAGING_DIR)/usr/include/qca-nss-ppe

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