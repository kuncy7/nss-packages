#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x7377b0b2, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xf18e6c6c, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xd8fa87d1, __VMLINUX_SYMBOL_STR(param_ops_long) },
	{ 0x7fc2d32b, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0xe942080b, __VMLINUX_SYMBOL_STR(usbnet_tx_timeout) },
	{ 0x8bd23d55, __VMLINUX_SYMBOL_STR(usbnet_change_mtu) },
	{ 0x2d91279b, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x54e886d0, __VMLINUX_SYMBOL_STR(usbnet_stop) },
	{ 0x904ae87c, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xf936b407, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x3c3fce39, __VMLINUX_SYMBOL_STR(__local_bh_enable_ip) },
	{ 0x62fba241, __VMLINUX_SYMBOL_STR(netif_schedule_queue) },
	{ 0xda3e43d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock) },
	{ 0x7a2af7b4, __VMLINUX_SYMBOL_STR(cpu_number) },
	{ 0xd52bf1ce, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x4629334c, __VMLINUX_SYMBOL_STR(__preempt_count) },
	{ 0xeb70037e, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xfe18b9ae, __VMLINUX_SYMBOL_STR(netif_receive_skb) },
	{ 0xb5028a2a, __VMLINUX_SYMBOL_STR(hrtimer_start_range_ns) },
	{ 0xf29d337f, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xe6da44a, __VMLINUX_SYMBOL_STR(set_normalized_timespec) },
	{ 0x53569707, __VMLINUX_SYMBOL_STR(this_cpu_off) },
	{ 0x6e09dba2, __VMLINUX_SYMBOL_STR(netif_rx_ni) },
	{ 0xf0f6ee85, __VMLINUX_SYMBOL_STR(arp_create) },
	{ 0x349cba85, __VMLINUX_SYMBOL_STR(strchr) },
	{ 0x449ad0a7, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xd54f8114, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xd0b3ee43, __VMLINUX_SYMBOL_STR(usb_string) },
	{ 0x87b393c2, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2ecda6f9, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x59a961f7, __VMLINUX_SYMBOL_STR(usb_clear_halt) },
	{ 0x74df6a3e, __VMLINUX_SYMBOL_STR(usb_cdc_wdm_register) },
	{ 0xe763e530, __VMLINUX_SYMBOL_STR(usbnet_get_endpoints) },
	{ 0x9545af6d, __VMLINUX_SYMBOL_STR(tasklet_init) },
	{ 0xd80deab4, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0x71c4e78b, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0x522f1789, __VMLINUX_SYMBOL_STR(usbnet_skb_return) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x52492389, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xd13a26a4, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0xbc22fcd3, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x713c8584, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x2e0d2f7f, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x76b9fc67, __VMLINUX_SYMBOL_STR(netdev_rx_handler_register) },
	{ 0x22d1015f, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x23ee5d54, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xe02e7244, __VMLINUX_SYMBOL_STR(netif_device_attach) },
	{ 0x3a2c2887, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xbd671048, __VMLINUX_SYMBOL_STR(__alloc_percpu_gfp) },
	{ 0xd56b5f64, __VMLINUX_SYMBOL_STR(ktime_get_ts64) },
	{ 0x4414e104, __VMLINUX_SYMBOL_STR(hrtimer_init) },
	{ 0x1c1a1a97, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x71ba2145, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0x888d2aa9, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x16e6b4fe, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0x99a72409, __VMLINUX_SYMBOL_STR(netdev_rx_handler_unregister) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0x8f64aa4, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xbb495470, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x9327f5ce, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x88bfa7e, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x477cd74e, __VMLINUX_SYMBOL_STR(hrtimer_cancel) },
	{ 0x78024541, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0x29966a74, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0x57281808, __VMLINUX_SYMBOL_STR(usbnet_open) },
	{ 0xc4b0489a, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0x7d6fab20, __VMLINUX_SYMBOL_STR(eth_commit_mac_addr_change) },
	{ 0x90872dee, __VMLINUX_SYMBOL_STR(eth_prepare_mac_addr_change) },
	{ 0x5792f848, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xeaf9e62c, __VMLINUX_SYMBOL_STR(usbnet_get_drvinfo) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xe634c61b, __VMLINUX_SYMBOL_STR(netif_tx_wake_queue) },
	{ 0xd5e4bd09, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0x5b675a34, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xc0a3d105, __VMLINUX_SYMBOL_STR(find_next_bit) },
	{ 0x5ecfeec6, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xb152d87d, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0xb2be6e92, __VMLINUX_SYMBOL_STR(netdev_stats_to_stats64) },
	{ 0xb601be4c, __VMLINUX_SYMBOL_STR(__x86_indirect_thunk_rdx) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0x5794faf9, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x7de24c79, __VMLINUX_SYMBOL_STR(usb_driver_release_interface) },
	{ 0x455e6c0c, __VMLINUX_SYMBOL_STR(__dynamic_dev_dbg) },
	{ 0x9cc0b457, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0x1492f84e, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0xeacac14c, __VMLINUX_SYMBOL_STR(__dev_kfree_skb_any) },
	{ 0x26b17317, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe29bfceb, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x2ea2c95c, __VMLINUX_SYMBOL_STR(__x86_indirect_thunk_rax) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbnet,cdc-wdm";

MODULE_ALIAS("usb:v05C6p9003d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v05C6p9215d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0125d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0121d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp030Ed*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0191d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0195d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0700d*dc*dsc*dp*ic*isc*ip*in03*");
MODULE_ALIAS("usb:v2C7Cp0306d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp030Bd*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0512d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0296d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0435d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0620d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0316d*dc*dsc*dp*ic*isc*ip*in03*");
MODULE_ALIAS("usb:v2C7Cp0800d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0801d*dc*dsc*dp*ic*isc*ip*in04*");
MODULE_ALIAS("usb:v2C7Cp0122d*dc*dsc*dp*ic*isc*ip*in04*");

MODULE_INFO(srcversion, "BA2E7454FB67D58DFE8A444");
