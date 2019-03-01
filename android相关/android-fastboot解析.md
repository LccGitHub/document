# android的fastboot解析

## 介绍
fastboot是android的一种刷机方式，是使用usb为物理媒介，是bootloader阶段的一个命令，在bootloader阶段输入fastboot命令，可以进入fastboot模式，进行刷机，是C/S结构，主要主机加载文件到开发板，开发板相当于usb从设备，自己的PC机相当于usb主设备



### 进入fastboot模式的原理
1. android可以通过android reboot bootloader命令进入fastboot模式，
代码调用关系如下：
>     android_reboot
>         android_reboot_with_callback
>             ANDROID_RB_RESTART2:
>             syscall(__NR_reboot, LINUX_REBOOT_MAGIC1,LINUX_REBOOT_MAGIC2,LINUX_REBOOT_CMD_RESTART2, arg);
>                 __SYSCALL(__NR_reboot, sys_reboot) // kernel代码
>                  SYSCALL_DEFINE4  //kernel/kernel/sys.c
>                 

2. 按着Ctrl+C重启，根据提示输入fastboot命令


### bootloader中的fastboot
代码目录

    app/aboot/fastboot.c
    fastboot_init、
        创建单独的线程thread_create("fastboot", fastboot_handler, 0, DEFAULT_PRIORITY, 4096
        fastboot_handler中维护一个for(;;)循环
        event_wait(&usb_online)
        fastboot_command_loop()
            fastboot_okay //回复
            cmd_download // 下载

#### fastboot_init完成的工作
- usb_if（usb controller interface）初始化
- usb_if绑定
- fastboot线程启动

##### usb_if初始化完成以下工作
- 初始化了两个全局变量 download_base 和 download_size, 这块空间是 fastboot 刷入系统时的缓冲区
- 获取序列号并赋值给 surf_udc_device
- 初始化 usb_if 中的各控制函数，比如注册fastboot_notify为usb数据的通知函数，当usb包发送到板子时，这个函数的终端就会被触发，fastboot_notify 函数的作用是发送 usb_online 的信号，凡事接收这个信号的函数就会被调用。

##### usb_if绑定
usb_if 初始化完成后，需要设置通信的渠道，和响应命令的方法
创建了两个事件， usb_online 和 txn_done, usb_online 是响应 usb 上线的事件，然后等待处理命令，txn_done 则是在请求 usb 操作时等待返回的信号，由 req_complete 函数发送此信号。

使用 usb 控制函数给出的接口创建以下 3 个全局变量：

    static struct udc_endpoint inin 变量是在 usb_write 对应的函数中使用，作为 usb 入口端点。
    static struct udc_endpoint outout 变量是在 usb_read 对应的函数中使用，作为 usb 出口端点。
    static struct udc_request *reqreq 作为请求 usb 数据操作，相当于一个 usb 数据包。
将 fastboot_gadget 注册到 usb 中， fastboot_gadget 的 notify 函数是整个指令处理流程的入口点。

##### fastboot线程启动
主要的功能就是启动一个线程等待 fastboot 的指令传入，并且启动 udc。

	fastboot_register("getvar:", cmd_getvar);
	fastboot_register("download:", cmd_download);
	fastboot_publish("version", "0.5");

	thr = thread_create("fastboot", fastboot_handler, 0, DEFAULT_PRIORITY, 4096);
	if (!thr)
	{
		goto fail_alloc_in;
	}
	thread_resume(thr);

	usb_if.udc_start();

	return 0;

- 新注册了以下两条指令 getvar: 和 download:, 以及一条数据 version 
- 创建并启动 fastboot 线程，线程的功能就是等待 usb_online 事件，然后解析 fastboot 指令

    static int fastboot_handler(void *arg)
    {
    	for (;;) {
    		event_wait(&usb_online);
    		fastboot_command_loop();
    	}
    	return 0;
    }


- 开启udc指令解析
astboot 指令解析的过程是在 fastboot_command_loop 函数中完成的


    static void fastboot_command_loop(void)
    {
    	struct fastboot_cmd *cmd;
    	int r;
    
    	dprintf(INFO,"fastboot: processing commands\n");
    
    	uint8_t *buffer = (uint8_t *)memalign(CACHE_LINE, ROUNDUP(4096, CACHE_LINE));
    	if (!buffer)
    	{
    		dprintf(CRITICAL, "Could not allocate memory for fastboot buffer\n.");
    		ASSERT(0);
    	}
    again:
    	while (fastboot_state != STATE_ERROR) {
    
    		/* Read buffer must be cleared first. If buffer is not cleared,
    		 * the original data in buf trailing the received command is
    		 * interpreted as part of the command.
    		 */
    		memset(buffer, 0, MAX_RSP_SIZE);
    		arch_clean_invalidate_cache_range((addr_t) buffer, MAX_RSP_SIZE);
    
    		r = usb_if.usb_read(buffer, MAX_RSP_SIZE);
    		if (r < 0) break;
    		buffer[r] = 0;
    		dprintf(INFO,"fastboot: %s\n", buffer);
    
    
    		fastboot_state = STATE_COMMAND;
    
    		for (cmd = cmdlist; cmd; cmd = cmd->next) {
    			if (memcmp(buffer, cmd->prefix, cmd->prefix_len))
    				continue;
    			cmd->handle((const char*) buffer + cmd->prefix_len,
    				(void*) download_base, download_size);
    			if (fastboot_state == STATE_COMMAND)
    				fastboot_fail("unknown reason");
    
    			goto again;
    		}
    
    		fastboot_fail("unknown command");
    
    	}
    	fastboot_state = STATE_OFFLINE;
    	dprintf(INFO,"fastboot: oops!\n");
    	free(buffer);
    }

申请并清零缓冲区，然后使用 usb_read 接口获取 usb 数据。
遍历 cmdlist, 比对 指令 调用对应指令的处理函数。





