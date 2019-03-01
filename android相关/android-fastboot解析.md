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

当收到fastboot flash命令的时候
会调用到cmd_flash(const char *arg, void *data, unsigned sz)，如果是flash升级则调用cmd_flash_nand，再调用flash_write->_flash_write_page->dmov_exec_cmdptr

