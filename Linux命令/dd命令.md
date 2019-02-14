# dd命令
用指定大小的块拷贝一个文件，并在拷贝的同时进行指定的转换。


## 命令格式

```
dd   [option] 

```

### 选项





- if=file：输入文件名，缺省为标准输入
- of=file：输出文件名，缺省为标准输出
- ibs=bytes：一次读入 bytes 个字节（即一个块大小为 bytes 个字节）
- obs=bytes：一次写 bytes 个字节（即一个块大小为 bytes 个字节）
- bs=bytes：同时设置读写块的大小为 bytes ，可代替 ibs 和 obs
- cbs=bytes：一次转换 bytes 个字节，即转换缓冲区大小
- skip=blocks：从输入文件开头跳过 blocks 个块后再开始复制
- seek=blocks：从输出文件开头跳过 blocks 个块后再开始复制。（通常只有当输出文件是磁盘或磁带时才有效）
- count=blocks：仅拷贝 blocks 个块，块大小等于 ibs 指定的字节数
- conv=ASCII：把EBCDIC码转换为ASCIl码。 
- conv=ebcdic：把ASCIl码转换为EBCDIC码。 
- conv=ibm：把ASCIl码转换为alternate EBCDIC码。
- conv=block：把变动位转换成固定字符。 
- conv=ublock：把固定位转换成变动位。 
- conv=ucase：把字母由小写转换为大写。 
- conv=lcase：把字母由大写转换为小写。 
- conv=notrunc：不截短输出文件。 
- conv=swab：交换每一对输入字节。 
- conv=noerror：出错时不停止处理。 
- conv=sync：把每个输入记录的大小都调到ibs的大小（用NUL填充）。



### dd实例



```
dd if=/dev/zero of=update_pkg bs=512 count=8
```
从/dev/zero中拷贝512*8大小的内容到update_pkg中
，/dev/zero其实是一个特殊的设置，读它，相当于读取无线的空字符串，上面的命令相update当于设置update_pkg文件的前512*8个字节为空字符串，即初始化该缓冲区



```
dd if=secondary.64 of=update_pkg conv=notrunc
```
拷贝文件secondary.64的内容到update_pkg中，不截短输出文件


```
dd if=signature.64 of=update_pkg conv=notrunc seek=8 
```
拷贝文件signature.64的内容到update_pkg中的8*bs处，不截短输出文件


```
d if=update_pkg of=image.cwe bs=512 skip=13
```
从signature.64的bs*skip出开始拷贝内容到update_pkg中