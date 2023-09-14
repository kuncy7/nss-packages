include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=netstandby-drv
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=master
PKG_RELEASE:=2
LOCAL_SRC:=$(TOPDIR)/qca/src/qca-net-standby/driver/

include $(INCLUDE_DIR)/local-development.mk
ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_VERSION:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
endif

PKG_BUILD_DEPENDS :=
MAKE_OPTS:=

include $(INCLUDE_DIR)/package.mk

define KernelPackage/netstandby-drv
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Devices
  TITLE:=Standby module
  DEPENDS:=@TARGET_ipq95xx||TARGET_ipq53xx +kmod-qca-nss-ppe +kmod-qca-nss-ppe-rule +kmod-qca-nss-dp @!LINUX_3_18
  FILES:=$(PKG_BUILD_DIR)/qca-net-standby.ko
  AUTOLOAD:=$(call AutoLoad,53,qca-net-standby)
endef

define KernelPackage/netstandby-drv/Description
Kernel module for ErP network standby framework to interface
with subsystem drivers and netstandby application library
endef

EXTRA_CFLAGS+= \
	-I$(STAGING_DIR)/usr/include/qca-nss-ppe \
	-I$(STAGING_DIR)/usr/include/qca-ssdk \
	-I$(STAGING_DIR)/usr/include/qca-ssdk/fal \
	-I$(STAGING_DIR)/usr/include/qca-ssdk/init \
	-I$(STAGING_DIR)/usr/include/qca-nss-dp \
	-I$(LINUX_DIR)/user_headers/include/

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" $(strip $(MAKE_OPTS)) \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		M="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		modules
endef

# TODO: Can we copy on the data structures and API relevant for user space?
define Build/InstallDev/netstandby-drv
	$(INSTALL_DIR) $(1)/usr/include/netstandby-drv
	$(CP) $(PKG_BUILD_DIR)/include/* $(1)/usr/include/netstandby-drv/
endef

define Build/InstallDev
	$(call Build/InstallDev/netstandby-drv,$(1))
endef

$(eval $(call KernelPackage,netstandby-drv))
