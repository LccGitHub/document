## 解压缩之zip unzip

### 压缩命令

### 格式
    
    $ zip --help
    Copyright (c) 1990-2008 Info-ZIP - Type 'zip "-L"' for software license.
    Zip 3.0 (July 5th 2008). Usage:
    zip [-options] [-b path] [-t mmddyyyy] [-n suffixes] [zipfile list] [-xi list]
      The default action is to add or replace zipfile entries from list, which
      can include the special name - to compress standard input.
      If zipfile and list are omitted, zip compresses stdin to stdout.
      -f   freshen: only changed files  -u   update: only changed or new files
      -d   delete entries in zipfile-m   move into zipfile (delete OS files)
      -r   recurse into directories -j   junk (don't record) directory names
      -0   store only   -l   convert LF to CR LF (-ll CR LF to LF)
      -1   compress faster  -9   compress better
      -q   quiet operation  -v   verbose operation/print version info
      -c   add one-line comments-z   add zipfile comment
      -@   read names from stdin-o   make zipfile as old as latest entry
      -x   exclude the following names  -i   include only the following names
      -F   fix zipfile (-FF try harder) -D   do not add directory entries
      -A   adjust self-extracting exe   -J   junk zipfile prefix (unzipsfx)
      -T   test zipfile integrity   -X   eXclude eXtra file attributes
      -y   store symbolic links as the link instead of the referenced file
      -e   encrypt  -n   don't compress these suffixes
      -h2  show more help
      
    $

### 常用选项
- -q ：安静模式，不显示中间过程
- -r:循环遍历子目录
- -y:保存软件连接，而不是直接拷贝文件，只能在linux使用，windows上不可以
- -P:压缩密码


### 例子

压缩当前路径下的sdk目录，压缩的生成文件名为sdk.zip,压缩密码是123456
    zip -qry -P "123456" sdk.zip sdk


## 解压缩命令

### 格式
    Usage: unzip [-Z] [-opts[modifiers]] file[.zip] [list] [-x xlist] [-d exdir]


#### 例子
安静的用123456密码解压sdk.zip文件，默认会加压到当前目录的sdk目录
    unzip -q -P "123456" sdk.zip