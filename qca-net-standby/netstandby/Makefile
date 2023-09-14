include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

PKG_NAME:=netstandby
PKG_RELEASE:=1
NETSTANDBY_BUILD_DIR:=$(TOPDIR)/qca/src/qca-net-standby/netstandby
NETSTANDBYINIT_BUILD_DIR:=$(TOPDIR)/qca/src/qca-net-standby/netstandbyinit

define Package/netstandby
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Userspace application for ErP netstandby
  DEPENDS:=@TARGET_ipq95xx||TARGET_ipq53xx +lib-netstandby
endef

define Package/netstandby/description
Userspace application for ErP netstandby
endef

TOOL_CFLAGS:= $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include/lib-netstandby \
			       -I$(STAGING_DIR)/usr/include/netstandby-drv \
			       -I$(LINUX_DIR)/user_headers/include/

ifeq ($(CONFIG_TARGET_ipq53xx), y)
TOOL_CFLAGS+= -DMIAMI_PORT_ERP
endif

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)/netstandby
	mkdir -p $(PKG_BUILD_DIR)/netstandbyinit
	$(CP) $(NETSTANDBYINIT_BUILD_DIR)/*  $(PKG_BUILD_DIR)/netstandbyinit
	$(CP) $(NETSTANDBY_BUILD_DIR)/*  $(PKG_BUILD_DIR)/netstandby
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/netstandby \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TOOL_CFLAGS)" \
		LD_LIBRARY_PATH="$(TOOL_LDFLAGS)"
	$(MAKE) -C $(PKG_BUILD_DIR)/netstandbyinit \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TOOL_CFLAGS)" \
		LD_LIBRARY_PATH="$(TOOL_LDFLAGS)"
endef

define Package/netstandby/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/netstandby/obj/netstandby $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/netstandbyinit/obj/netstandbyinit $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,netstandby))
