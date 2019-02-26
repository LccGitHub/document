# android的启动时序

## 分为三个模块
- aboot： bootloader
- kernel：zImag启动
- system


#### sbl1.mbn
会打印如下log

    Format: Log Type - Time(microsec) - Message - Optional Info
    Log Type: B - Since Boot(Power On Reset),  D - Delta,  S - Statistic
    S - QC_IMAGE_VERSION_STRING=BOOT.BF.3.1.2-00084
    S - IMAGE_VARIANT_STRING=LAATANAZA
    S - OEM_IMAGE_VERSION_STRING=SH-SW417P
    S - Boot Config, 0x000002e1
    B -  1216 - PBL, Start
    B -  3723 - bootable_media_detect_entry, Start
    B -  4397 - bootable_media_detect_success, Start
    B -  4401 - elf_loader_entry, Start
    B -  7854 - auth_hash_seg_entry, Start
    B -  8076 - auth_hash_seg_exit, Start
    B - 54877 - elf_segs_hash_verify_entry, Start
    B - 98301 - PBL, End
    B - 89578 - SBL1, Start
    B -138378 - pm_device_init, Start
    B -155428 - PM_SET_VAL:Skip
    D - 15768 - pm_device_init, Delta
    B -156434 - boot_config_data_table_init, Start
    D -174917 - boot_config_data_table_init, Delta - (420 Bytes)
    B -334890 - CDT version:3,Platform ID:8,Major ID:1,Minor ID:0,Subtype:0
    B -341051 - sbl1_ddr_set_params, Start
    B -344894 - Pre_DDR_clock_init, Start
    D -   213 - Pre_DDR_clock_init, Delta
    D - 0 - sbl1_ddr_set_params, Delta
    B -357612 - pm_driver_init, Start
    D -  4575 - pm_driver_init, Delta
    B -363956 - cpr_init, Start
    D -   122 - cpr_init, Delta
    B -368440 - cpr_cx_mx_apc_vol_update, Start
    D -91 - cpr_cx_mx_apc_vol_update, Delta
    B -383141 - sbl1_qhsusb_al_do_fast_enum, Start
    D -30 - sbl1_qhsusb_al_do_fast_enum, Delta
    B -386282 - clock_init, Start
    D -   152 - clock_init, Delta
    B -392077 - boot_flash_init, Start
    D - 37393 - boot_flash_init, Delta
    B -433496 - Image Load, Start
    B -433527 - [QUEC_SECBOOT]Image Type = 1
    B -440145 - [QUEC_SECBOOT]Image Auth Enable Sate = 1
    B -447770 - [QUEC_SECBOOT]Image Auth Result Sate = 0
    D - 66826 - QSEE Image Loaded, Delta - (491164 Bytes)
    D -   213 - boot_pm_post_tz_device_init, Delta
    B -504744 - sbl1_efs_handle_cookies, Start
    D - 0 - sbl1_efs_handle_cookies, Delta
    B -512034 - Devcfg Partition does not exist
    B -516304 - Image Load, Start
    D -30 - SEC Image Loaded, Delta - (0 Bytes)
    B -523990 - Image Load, Start
    B -526887 - [QUEC_SECBOOT]Image Type = 1
    B -533902 - [QUEC_SECBOOT]Image Auth Enable Sate = 1
    B -541527 - [QUEC_SECBOOT]Image Auth Result Sate = 0
    D - 32909 - RPM Image Loaded, Delta - (153504 Bytes)
    B -556960 - Image Load, Start
    B -558607 - [QUEC_SECBOOT]Image Type = 1
    B -564006 - [QUEC_SECBOOT]Image Auth Enable Sate = 1
    B -567757 - [QUEC_SECBOOT]Image Auth Result Sate = 0
    D - 53375 - APPSBL Image Loaded, Delta - (383548 Bytes)
    B -610396 - QSEE Execution, Start
    D -   183 - QSEE Execution, Delta
    B -616130 - SBL1, End
    D -528840 - SBL1, Delta
    S - Throughput, 3000 KB/s  (1028636 Bytes,  286847 us)
    S - DDR Frequency, 240 MHz

#### aboot过程
##### 上电后，硬件会从固定的地址加载bootloader到RAM，然后跳转到bootloader的入口函数开始执行，入口函数是：
>./arch/arm/crt0.S

crt0.S是汇编语言
在下面语句处会跳转到kmain函数中
>	bl		kmain



##### kmain的代码位于：
> ./kernel/main.c

主要完成如下工作：

- 调用thread_init_early初始化线程系统
- 调用arch_early_init中判断如果存在mmu就初始化，设置异常向量基地址，使能中断相关寄存器
- 在platform_early_init中完成初始化硬件时钟、手机的主板等操作.
- target_early_init中完成初始化uart端口的操作，这个函数的实现在bootable\bootloader\lk\target\{cpu型号}\init.c
- 首先输出调试信息"welcome to lk\n\n"，在bootable/bootloader/lk/include/debug.h中将INFO定义为了类似kernel中使用的debug level，同时定义了dprintf
- SPEW同样是在bootable/bootloader/lk/include/debug.h中定义的debug level，函数call_constructors完成相关构造函数的初始化
- 调用函数heap_init完成内核堆栈的初始化，用与kmalloc等函数的内存分配
- __stack_chk_guard_setup()其实是个宏，定义在bootable/bootloader/lk/include/debug.h中,返回一个生成的随机数，最终保存在全局变量__stack_chk_guard中。
- 在thread_init函数中初始化定时器
- 初始化延迟过程调用（delay procedure call）
- 调用timer_init初始化内核定时器
- 如果没有定义ENABLE_NANDWRITE，就创建出一个名为bootstrap2的线程，然后运行这个线程。退出临界区，开中断。全局变量critical_section_count在定义时取值为1，在exit_critical_section中会将critical_section_count先减1，如果减一后为0就使能中断。最后调用thread_become_idle将本线程切换到idle状态
- 如果定义了ENABLE_NANDWRITE，在timer_init之后将执行bootstrap_nandwrite。我们接下来先以没有定义ENABLE_NANDWRITE来进行分析


##### bootstrap2
完成以下工作：
- arch_init：如果定义了WITH_LIB_BIO和WITH_LIB_FS，就分别执行bio_init和fs_init。函数platform_init的实现也跟cpu关联，但基本都是输出调试信息
- target_init：

##### apps_init
在bootstrap2线程中最后执行apps_init,完成一些应用功能的初始化

实现代码
> app/app.c

aboot_init实现代码
> app/aboot/aboot.c
aboot_init主要完成如下工作：

- 根据target_is_emmc_boot()判断是否是从emmc存储设备上启动，然后分别获取对应存储设备的页大小和页掩码
- 取得设备的device_info信息，保存到device变量中，结构体中包含的信息有：是否禁用fastboot，是否验证boot.img等
- 调用target_display_init初始化lcd驱动，显示手机开机后的第一副图片。splash一般代表在系统启动阶段显示器用图形而非文本现实
- 调用target_serialno获取emmc或者flash芯片的产品序列号，最后在启动kernel时通过cmdline中的androidboot.serialno参数传给内核。
- 调用memset清除屏幕
- 判断关机原因，如果是用户强制重启手机，这时在重启后跳转到normal_boot继续执行
- 判断音量上下键是否同时按下，之后如果进入下载模式失败，就设置fastboot模式标志boot_into_fastboot = true
- 如果不是通过usb+上下键进入下载模式，判断如果home键和音量上键同时按下，设置recovery模式标志boot_into_recovery = 1， 如果back键和音量下键同时按下，设置fastboot模式标志。
- 如果没有按键驱动，设置boot_into_fastboot为true
- 根据硬件是否存在pon寄存器，调用check_hard_reboot_mode或者check_reboot_mode获取重启模式reboot_mode，设置相应的开机模式标志。以前使用的是共享内存记录重启模式，最新转为使用pmic的pon寄存器记录重启模式
- 在normal_boot:下，首先判断如果不是fastboot模式，然后通过target_is_emmc_boot判断是否从emmc或者ufs启动，如果从emmc或者ufs启动，先执行emmc_recovery_init，emmc_recovery_init的实现主要在函数_emmc_recovery_init中，_emmc_recovery_init的定义在bootable/bootloader/lk//app/aboot/recovery.c中，主要工作为读取misc分区中的bcb，判断bcb的command域是否为boot-recovery，如果是update-radio还会检查radio的更新状态。 回到aboot_init中用target_use_signed_kernel判断是否使用了签名的kernel，最后执行boot_linux_from_mmc， 在boot_linux_from_mmc中将从emmc/ufs加载boot.img，选择dts，设置cmdline，跳转到kernel。如果从nand flash启动，调用boot_linux_from_flash去启动内核。
- 之后的代码是fasboot模式或者正常启动失败的情况下才会执行到的，首先调用aboot_fastboot_register_commands注册fastboot支持的命令，在partition_dump中打印分区表信息， 执行fastboot_init初始化并启动fastboot，在display_fastboot_menu_thread中为fastboot提供了一个简易图形显示



kmain->aboot_init->boot_linux->跳转到kernel启动代码




#### kernel启动代码

参考链接[https://www.freebuf.com/news/135084.html](https://www.freebuf.com/news/135084.html)
main.c中
kernel_init->try_to_run_init_process("/sbin/init")

#### 用户进程init启动
    



