# mkbootfs 以及 minigzip， mkbootimg 介绍

## ramdisk
ram disk虚拟内存盘，将ram模拟成硬盘来使用的文件系统，掉电后，内容就会丢失，在android中主要用于存放android启动后第一个用户进程init可执行文件和init.*.rc等相关启动脚本以及sbin目录下的adbd工具

## mkbootfs用法

mkbootfs (android make ramdisk tools）制作ramdisk的工具


mkbootfs root | minigzip > out/ramdisk.img



## mkbootimg用法
    usage: mkbootimg
       --kernel <filename>  kernel文件路径
       --ramdisk <filename> ramdisk文件路径
       [ --second <2ndbootloader-filename> ]
       [ --cmdline <kernel-commandline> ] cmdline命令
       [ --board <boardname> ]
       [ --base <address> ] 基地址
       [ --pagesize <pagesize> ] 页的大小
       [ --ramdisk_offset <ramdisk_offset> ]
       [ --dt <filename> ]
       [ --tags-addr <address> ]
       -o|--output <filename> 输出文件名

### example
    mkbootimg  --kernel out/zImage --ramdisk out/ramdisk.img --dt out/dt.img --cmdline "init = /init rw console=ttyHSL0,115200,n8 androidboot.console=ttyHSL0 androidboot.hardware=qcom ehci-hcd.park=3 msm_rtb.filter=0x37 lpm_levels.sleep_disabled=1 security=selinux selinux=1 androidboot.selinux=permissive earlycon=msm_hsl_uart,0x78b0000 blkdevparts=mmcblk0:4096M(userdata1),3000M(var)" --base 0x80000000 --pagesize 4096 --tags-addr 0x81e00000 --output out/boot.img.unsign