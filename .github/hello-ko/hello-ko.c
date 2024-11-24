// Copyright (c) 2023-2025 fei_cong(https://github.com/feicong/ebpf-course)
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("feicong");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("https://github.com/feicong/ebpf-course");
MODULE_VERSION("1.0");

static int __init lkm_strong_init(void) {
	printk(KERN_INFO "hello kernel!\n");
	return 0;
}

static void __exit lkm_strong_exit(void) {
	printk(KERN_INFO "goodbye kernel!\n");
}

module_init(lkm_strong_init);
module_exit(lkm_strong_exit);
