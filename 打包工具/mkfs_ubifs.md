# mkfs.ubifs 以及 ubinize 介绍

[https://blog.csdn.net/gg3980812/article/details/18090667](https://blog.csdn.net/gg3980812/article/details/18090667 "UBIFS filesystem")

## mkfs.ubifs用法
> usage: mkfs.ubifs [OPTIONS] target
> Make a UBIFS file system image from an existing directory tree

### Options
- -r, -d, --root=DIR   build file system from directory DIR
- -m, --min-io-size=SIZE   minimum I/O unit size最小输入输出单元
- -e, --leb-size=SIZE  logical erase block size逻辑可擦除块的大小
- -c, --max-leb-cnt=COUNT  maximum logical erase block count，最多逻辑可擦除数据，
- -o, --output=FILEoutput to FILE，输出文件名
- -j, --jrn-size=SIZE  journal size
- -R, --reserved=SIZE  how much space should be reserved for the super-user
- -x, --compr=TYPE compression type "lzo", "favor_lzo", "zlib" or
-  "none" (default: "lzo")
- -X, --favor-percent  may only be used with favor LZO compression and defines
-  how many percent better zlib should compress to make
-  mkfs.ubifs use zlib instead of LZO (default 20%)
- -f, --fanout=NUM fanout NUM (default: 8)
- -k, --keyhash=TYPE   key hash type "r5" or "test" (default: "r5")
- -p, --orph-lebs=COUNTcount of erase blocks for orphans (default: 1)
- -D, --devtable=FILE  use device table FILE
- -U, --squash-uidssquash owners making all files owned by root
- -F, --fixstats   fix file permissions & owners (android)， 修改文件权限为owners
- -l, --log-lebs=COUNT count of erase blocks for the log (used only for
-  debugging)
- -v, --verboseverbose operation
- -V, --versiondisplay version information
- -g, --debug=LEVELdisplay debug information (0 none, 1 statistics,
-  2 files, 3 more details)
- -h, --help   display this help text

> Note, SIZE is specified in bytes, but it may also be specified in Kilobytes,
> Megabytes, and Gigabytes if a KiB, MiB, or GiB suffix is used.

### example
    > mkfs.ubifs  -r system -o out/system.ubifs -m 4096 -e 253952 -c 4292 -F
    
命令含义如下:

1. 将system文件夹制作成UBIFS文件系统镜像
2. 输出的镜像文件名为out/system.ubifs
3. -m制定了最小I/O操作大小，等于NAND FLASH一个page的大小
4. -e指定逻辑擦除块的大小
5. -c指定最大逻辑块号

##  ubinize用法
用于产生UBI镜像，可用于直接再NAND FLASH烧写的文件格式

    Usage: ubinize [-o filename] [-h] [-V] [--output=<filename>] [--help]
    		[--version] ini-file

#### Options
- -o, --output=<file name>     output file name，输出文件
- -p, --peb-size=<bytes>       size of the physical eraseblock of the flash
this UBI image is created for in bytes, kilobytes (KiB), or megabytes (MiB)
(mandatory parameter)，物理可擦除块大小
- -m, --min-io-size=<bytes>    minimum input/output unit size of the flash
in bytes，最小输入输出大小，一般为页大小
- -s, --sub-page-size=<bytes>  minimum input/output unit used for UBI headers, e.g. sub-page size in case of NAND flash (equivalent to the minimum input/output unit size by default)，子页大小，一般与-m相同
- -O, --vid-hdr-offset=<num>   offset if the VID header from start of the
physical eraseblock (default is the next minimum I/O unit or sub-page after the EC header)
- -e, --erase-counter=<num>    the erase counter value to put to EC headers
(default is 0)
- -x, --ubi-ver=<num>          UBI version number to put to EC headers
(default is 1)
- -v, --verbose                be verbose
- -h, --help                   print help message
- -V, --version                print program version

### example

    ubinize -o out/system.img -m 4096 -p 256KiB -s 4096 build/tools/ubinize.ini

命令含义如下：

1. 输出的镜像文件名为system.img
2. -m指定最小输入输出操作大小，一般为页的大小
3. -p指定物理可擦除块的大小
4. -s指定子页的大小
5. ubinize.ini指定了制作ubinize的配置文件

ubinize.ini 内容如下

    [sysfs_volume]
    mode=ubi
    image=./out/system.ubifs
    vol_id=0
    vol_type=dynamic
    vol_name=system
    vol_size=78832KiB


可以直接将生成的system.img用fastboot命令烧到system对应的分区