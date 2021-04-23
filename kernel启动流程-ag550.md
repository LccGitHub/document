# 内核 启动流程

参考连接：https://www.cnblogs.com/icefree/p/8542935.html

## 编译内核的命令

    make O=xxx ARCH=yyy CROSS_COMPILE=zzz
    其中：
    O=xxx可以指定不在源代码目录下编译，而到另外一个单独文件夹下编译。
    ARCH=yyy yyy是arm 还是arm64
    CROSS_COMPILE=zzz 编译链的路径
    
    比如
    make O=/tmp/mykernel ARCH=arm CROSS_COMPILE=/usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-


## 连接脚本
编译的时候会将汇编文件vmlinux.lds.S 编译为真正的链接脚本vmlinux.lds， 入口符号ENTRY(stext)可以知道入口符号是stext

    $ grep -rsn "ENTRY(stext)"
    arch/unicore32/kernel/head.S:61:ENTRY(stext)
    arch/unicore32/kernel/vmlinux.lds.S:20:ENTRY(stext)
    arch/m32r/kernel/head.S:31:ENTRY(stext)
    arch/hexagon/kernel/head.S:33:ENTRY(stext)
    arch/hexagon/kernel/vmlinux.lds.S:26:ENTRY(stext)
    arch/arm/kernel/head.S:80:ENTRY(stext)
    arch/arm/kernel/vmlinux-xip.lds.S:50:ENTRY(stext)
    arch/arm/kernel/head-nommu.S:44:ENTRY(stext)
    arch/arm/kernel/head-nommu.S:47:ENTRY(stext)
    arch/arm/kernel/vmlinux.lds.S:57:ENTRY(stext)
    arch/arm64/kernel/head.S:119:ENTRY(stext)
    arch/arc/kernel/head.S:76:ENTRY(stext)
    build/arch/arm/kernel/vmlinux.lds:2:ENTRY(stext)


找到_stext在arch/arc/kernel/head.S中有定义，head.S是内核的启动文件，相当于uboot的start.S

### head.S文件分析
head.S定义了内存运行的物理地址与虚拟地址

    #define KERNEL_RAM_VADDR	(PAGE_OFFSET + KERNEL_IMAGE_START) //内核运行的虚拟地址 c0000000+0x00408000
    #define KERNEL_RAM_PADDR	(PHYS_OFFSET + KERNEL_IMAGE_START)  //内核运行的物理地址 PHYS_OFFSET+0x00408000


内核的真正入口    

- 内核的真正入口就是ENTRY(stext)处
- 前面的__HEAD定义了后面的代码属于段名为.head.text的段

汇编阶段主要就是：校验cpu_id，机器码和uboot传参、建立段式映射的页表并开启MMU以方便使用内存、跳入C阶段。

## start_kernel

- 总结：start_kernel函数中调用了很多的xx_init函数，全都是内核工作需要的模块的初始化函数。这些初始化之后内核就具有了一个基本的可以工作的条件了。
- 如果把内核比喻成一个复杂机器，那么start_kernel函数就是把这个机器的众多零部件组装在一起形成这个机器，让他具有可以工作的基本条件。


rest_init()

- 这个函数之前内核的基本组装已经完成。
- 剩下的一些工作就比较重要了，放在了一个单独的函数中，叫rest_init。
- rest_init()中调用kernel_thread()函数启动了2个内核线程，分别是：kernel_init 和 kthreadd

- 进程0：cpu_idle进程0其实就是刚才讲过的idle进程，叫空闲进程，也就是死循环。
- 进程1：kernel_init 函数就是进程1，这个进程被称为  init进程。
- 进程2：kthreadd 函数就是进程2，这个进程是linux内核的守护进程。这个进程是用来保证linux内核自己本身能正常工作的。
 

    init/main.c 
    asmlinkage __visible void __init start_kernel(void)
    {
    	char *command_line;
    	char *after_dashes;
    
    	set_task_stack_end_magic(&init_task);
    	smp_setup_processor_id();
    	debug_objects_early_init();
    
    	cgroup_init_early();
    
    	local_irq_disable();
    	early_boot_irqs_disabled = true;
    
    	/*
    	 * Interrupts are still disabled. Do necessary setups, then
    	 * enable them.
    	 */
    	boot_cpu_init();
    	page_address_init();
    	pr_notice("%s", linux_banner);
    	setup_arch(&command_line);
    	/*
    	 * Set up the the initial canary and entropy after arch
    	 * and after adding latent and command line entropy.
    	 */
    	add_latent_entropy();
    	add_device_randomness(command_line, strlen(command_line));
    	boot_init_stack_canary();
    	mm_init_cpumask(&init_mm);
    	setup_command_line(command_line);
    	setup_nr_cpu_ids();
    	setup_per_cpu_areas();
    	smp_prepare_boot_cpu();	/* arch-specific boot-cpu hooks */
    	boot_cpu_hotplug_init();
    
    	build_all_zonelists(NULL);
    	page_alloc_init();
    
    	pr_notice("Kernel command line: %s\n", boot_command_line);
    	/* parameters may set static keys */
    	jump_label_init();
    	parse_early_param();
    	after_dashes = parse_args("Booting kernel",
    				  static_command_line, __start___param,
    				  __stop___param - __start___param,
    				  -1, -1, NULL, &unknown_bootoption);
    	if (!IS_ERR_OR_NULL(after_dashes))
    		parse_args("Setting init args", after_dashes, NULL, 0, -1, -1,
    			   NULL, set_init_arg);
    
    	/*
    	 * These use large bootmem allocations and must precede
    	 * kmem_cache_init()
    	 */
    	setup_log_buf(0);
    	pidhash_init();
    	vfs_caches_init_early();
    	sort_main_extable();
    	trap_init();
    	mm_init();
    
    	ftrace_init();
    
    	/* trace_printk can be enabled here */
    	early_trace_init();
    
    	/*
    	 * Set up the scheduler prior starting any interrupts (such as the
    	 * timer interrupt). Full topology setup happens at smp_init()
    	 * time - but meanwhile we still have a functioning scheduler.
    	 */
    	sched_init();
    	/*
    	 * Disable preemption - early bootup scheduling is extremely
    	 * fragile until we cpu_idle() for the first time.
    	 */
    	preempt_disable();
    	if (WARN(!irqs_disabled(),
    		 "Interrupts were enabled *very* early, fixing it\n"))
    		local_irq_disable();
    	radix_tree_init();
    
    	/*
    	 * Allow workqueue creation and work item queueing/cancelling
    	 * early.  Work item execution depends on kthreads and starts after
    	 * workqueue_init().
    	 */
    	workqueue_init_early();
    
    	rcu_init();
    
    	/* Trace events are available after this */
    	trace_init();
    
    	context_tracking_init();
    	/* init some links before init_ISA_irqs() */
    	early_irq_init();
    	init_IRQ();
    	tick_init();
    	rcu_init_nohz();
    	init_timers();
    	hrtimers_init();
    	softirq_init();
    	timekeeping_init();
    	time_init();
    	sched_clock_postinit();
    	printk_safe_init();
    	perf_event_init();
    	profile_init();
    	call_function_init();
    	WARN(!irqs_disabled(), "Interrupts were enabled early\n");
    	early_boot_irqs_disabled = false;
    	local_irq_enable();
    
    	kmem_cache_init_late();
    
    	/*
    	 * HACK ALERT! This is early. We're enabling the console before
    	 * we've done PCI setups etc, and console_init() must be aware of
    	 * this. But we do want output early, in case something goes wrong.
    	 */
    	console_init();
    	if (panic_later)
    		panic("Too many boot %s vars at `%s'", panic_later,
    		  panic_param);
    
    	lockdep_info();
    
    	/*
    	 * Need to run this when irqs are enabled, because it wants
    	 * to self-test [hard/soft]-irqs on/off lock inversion bugs
    	 * too:
    	 */
    	locking_selftest();
    
    	/*
    	 * This needs to be called before any devices perform DMA
    	 * operations that might use the SWIOTLB bounce buffers. It will
    	 * mark the bounce buffers as decrypted so that their usage will
    	 * not cause "plain-text" data to be decrypted when accessed.
    	 */
    	mem_encrypt_init();
    
    ...
    	kmemleak_init();
    	debug_objects_mem_init();
    	setup_per_cpu_pageset();
    	numa_policy_init();
    	if (late_time_init)
    		late_time_init();
    	calibrate_delay();
    	pidmap_init();
    	anon_vma_init();
    	acpi_early_init();
    ....
    	thread_stack_cache_init();
    	cred_init();
    	fork_init();
    	proc_caches_init();
    	buffer_init();
    	key_init();
    	security_init();
    	dbg_late_init();
    	vfs_caches_init();
    	pagecache_init();
    	signals_init();
    	proc_root_init();
    	nsfs_init();
    	cpuset_init();
    	cgroup_init();
    	taskstats_init_early();
    	delayacct_init();
    
    	check_bugs();
    
    	acpi_subsystem_init();
    	arch_post_acpi_subsys_init();
    	sfi_init_late();
    
    	if (efi_enabled(EFI_RUNTIME_SERVICES)) {
    		efi_free_boot_services();
    	}
    
    	/* Do the rest non-__init'ed, we're now alive */
    	rest_init();
    
    	prevent_tail_call_optimization();
    }



    