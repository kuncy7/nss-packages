include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=aqr-phy
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=master
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/aqr-phy
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Support
  TITLE:=Github AQR driver
  ifeq ($(CONFIG_AQUANTIA_PHY),)
	  FILES:=$(PKG_BUILD_DIR)/linux-aqr-phy/drivers/net/phy/aquantia/aqr-phy.ko
  endif
  DEPENDS+=+kmod-hwmon-core
  AUTOLOAD:=$(call AutoLoad,07,aqr-phy)
  PROVIDES:=aqr-phy
endef

define KernelPackage/aqr-aqr/Description
This package contains aquantia PHY driver from github
endef

ifdef CONFIG_TARGET_NAME
AQR-PHY-CONFIG_OPTS+= \
	TARGET_NAME=$(CONFIG_TARGET_NAME)
endif

AQR-PHY-CONFIG_OPTS+= \
	LINUX_DIR=$(LINUX_DIR) \
	CROSS_COMPILE=$(TARGET_CROSS) \
	ARCH=$(LINUX_KARCH)

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./* $(PKG_BUILD_DIR)/
	cd $(PKG_BUILD_DIR); \
        git clone --filter=blob:none --no-checkout --depth 1 \
	--sparse https://github.com/Aquantia/linux-aqr-phy.git \
	-b aqr_mainline; \
	cd linux-aqr-phy/;git sparse-checkout add drivers/net/phy/aquantia; \
	git checkout; \
	git checkout c798fde2b7fb6cb6f2bfc75bdea4875d85177f83
	$(CP) $(PKG_BUILD_DIR)/src/Makefile $(PKG_BUILD_DIR)/linux-aqr-phy/drivers/net/phy/aquantia/

endef

define Build/Compile
	$(KERNEL_MAKE) M=$(PKG_BUILD_DIR)/linux-aqr-phy/drivers/net/phy/aquantia $(strip $(AQR-PHY-CONFIG_OPTS))
endef

define Build/InstallDev
endef

define KernelPackage/aqr-phy/install
endef
$(eval $(call KernelPackage,aqr-phy))
