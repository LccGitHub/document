# android分区挂载

## 配置文件
fstab.${ro.hardware}

比如
fstab.qcom

    
    # Android fstab file.
    # <src	<mnt_point	<type	<mnt_flags and options <fs_mgr_flags>

    # The filesystem that contains the filesystem checker binary (typically /system) cannot
    # specify MF_CHECK, and must come before any filesystems that do specify MF_CHECK

    /dev/ubi0_  /system ubifs   rw   slotselect,wait
    /dev/block/mmcblk0p1/var  ext4  noatime,nosuid,nodev  wait,check
    /dev/block/mmcblk0p1/data  ext4  noatime,nosuid,nodev  wait,check


    
options分析

 - rw :以只读方式挂载文件系统
 - ro ：以读写模式挂载文件系统
 - nodev ：不解析文件系统上的块特殊设备
 - nosuid ：禁止suid操作和设定sgid位
 - noatime ：不更新文件系统上inode访问记录，可以提升性能


## mount方式

在init.rc中设置

    on fs
    ....    
    mount_all /fstab.qcom

