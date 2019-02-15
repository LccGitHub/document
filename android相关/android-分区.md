# android的分区

## 主要名词
modem （NON-HLOS.bin） 基带文件（手机信号有关）

sbl1 （sbl1.mbn） 二次引导，和boot配合完成启动

dbi （sdi.mbn） 跟基带有关

rpm （rpm.mbn） 资源电源管理

aboot （emmc_appsboot.mbn） bootloader引导文件，fastboot模式文件

fsc （没有对应文件）

ssd （没有对应文件）

DDR （没有对应文件）

boot （boot.img） 内核文件，启动加载

recovery （recovery.img） recovery模式加载的文件

splash （splash.img） 开机画面文件

mrd （没有对应文件） 未知，进入系统后，挂载为oem文件夹

tz （tz.mbn） 启动相关

pad （没有对应文件）



