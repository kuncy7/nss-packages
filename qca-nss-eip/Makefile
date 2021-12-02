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
		SoC="$(subtarget)" \
		modules
endef

$(eval $(call KernelPackage,qca-nss-eip))
