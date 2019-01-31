# android的make系统

## 主要涉及文件
build/cor/main.mk
build/cor/Makefile
Makefile

## 关系

Makefile->build/cor/main.mk->build/cor/Makefile


### main.mk
主要定义了make 后面的命令，如下：

- make sdkimage
- make bootimage
- make systeimage
- make moudle showcommands


### build/cor/Makefile
主要定义了一些具体的实现，编译目标的依赖等，比如
1. 如何生成boot.img, 需要依赖哪些模块
2. 如何生成ramdisk.img,依赖文件
3. 如何生成userdata.img,需要哪些依赖



### 其他.mk文件

#### config.mk
定义了一些基本配置，比如

1. 编译选项
2. 基本工具的宏
3. Android.mk中用到的变量，CLEAR_VARS,BUILD_EXECUTABLED等