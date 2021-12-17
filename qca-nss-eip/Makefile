include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=qca-nss-eip
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=master
PKG_RELEASE:=1

include $(INCLUDE_DIR)/local-development.mk
ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_VERSION:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
endif

include $(INCLUDE_DIR)/package.mk

ifeq ($(CONFIG_TARGET_ipq),y)
subtarget:=$(SUBTARGET)
else
subtarget:=$(CONFIG_TARGET_BOARD)
endif

NSS_EIP_DIR:=eip197
ifneq ($(CONFIG_PACKAGE_kmod-qca-nss-eip-crypto),y)
eip_crypto:=m
endif

define KernelPackage/qca-nss-eip
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Devices
  DEPENDS:=@TARGET_ipq95xx\
		+TARGET_ipq95xx:kmod-qca-nss-fw-eip-al
  TITLE:=Kernel driver for NSS EIP driver
  FILES:=$(PKG_BUILD_DIR)/driver/$(NSS_EIP_DIR)/qca-nss-eip.ko
  AUTOLOAD:=$(call AutoLoad,52,qca-nss-eip)
endef

define KernelPackage/qca-nss-eip/Description
This package contains a NSS EIP driver for QCA chipset
endef

define KernelPackage/qca-nss-eip/install
	$(INSTALL_DIR) $(1)/usr/include/qca-nss-eip
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/eip_dump.sh $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/driver/exports/* $(1)/usr/include/qca-nss-eip
endef

define KernelPackage/qca-nss-eip-crypto
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Devices
  DEPENDS:=@TARGET_ipq95xx||TARGET_ipq_ipq95xx_32\
		+kmod-qca-nss-eip\
		+kmod-crypto-authenc
  TITLE:=Kernel NSS EIP crypto client
  FILES:=$(PKG_BUILD_DIR)/clients/$(eip_crypto)/qca-nss-eip-crypto.ko
  AUTOLOAD:=$(call AutoLoad,52,qca-nss-eip-crypto)
endef

define KernelPackage/qca-nss-eip-crypto/Description
This package contains a NSS EIP crypto client for QCA chipset
endef

define Build/InstallDev/qca-nss-eip-crypto
	$(INSTALL_DIR) $(1)/usr/include/qca-nss-eip
	$(CP) $(PKG_BUILD_DIR)/clients/exports/* $(1)/usr/include/qca-nss-eip
endef

define Build/InstallDev
	$(call Build/InstallDev/qca-nss-eip,$(1))
endef

define Build/InstallDev
	$(call Build/InstallDev/qca-nss-eip-crypto,$(1))
endef

EXTRA_CFLAGS+= \
	-I$(STAGING_DIR)/usr/include/qca-nss-eip

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CC="$(TARGET_CC)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		M="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		NSS_EIP_DIR=$(NSS_EIP_DIR) \
		eip_crypto=$(eip_crypto) \
		SoC="$(subtarget)" \
		modules
endef

$(eval $(call KernelPackage,qca-nss-eip))
$(eval $(call KernelPackage,qca-nss-eip-crypto))
