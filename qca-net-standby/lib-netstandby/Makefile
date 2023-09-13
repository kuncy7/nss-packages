include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=lib-netstandby
PKG_RELEASE:=1
LIB_NETSTANDBY_BUILD_DIR:=$(TOPDIR)/qca/src/qca-net-standby/

include $(INCLUDE_DIR)/package.mk

define Package/lib-netstandby
  SECTION:=Libs
  CATEGORY:=Libraries
  TITLE:=Library to facilitate communication from user to kernel for the network standby families
  DEPENDS:=@TARGET_ipq95xx||TARGET_ipq53xx +libnl +kmod-netstandby-drv
endef

define Package/lib-netstandby/Description
 Library to facilitate communication from user to kernel for the Network standby families.
endef

define Build/Prepare
	$(CP) $(LIB_NETSTANDBY_BUILD_DIR)/lib/*  $(PKG_BUILD_DIR)
endef

TOOL_CFLAGS:= -I$(STAGING_DIR)/usr/include/netstandby-drv \
              -I$(STAGING_DIR)/usr/include/libnl3 \
	      -I$(LINUX_DIR)/user_headers/include/

TOOL_LDFLAGS:= -L$(STAGING_DIR)/lib

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		AR="$(TARGET_AR) " \
		CFLAGS="$(TOOL_CFLAGS)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		LD_LIBRARY_PATH="$(TOOL_LDFLAGS)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/lib-netstandby
	$(CP) $(PKG_BUILD_DIR)/obj/lib-netstandby.so $(STAGING_DIR)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/include/* $(STAGING_DIR)/usr/include/lib-netstandby
endef

define Package/lib-netstandby/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/obj/lib-netstandby.so $(1)/lib
endef

$(eval $(call BuildPackage,lib-netstandby))
