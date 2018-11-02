# readelf





## 显示所需要动态库的信息
readelf -d lib.so


```
readelf -d lib.so

 0x00000001 (NEEDED)                     Shared library: [libcutils.so]
 0x00000001 (NEEDED)                     Shared library: [libc++.so]
```


## 查看ELF文件的动态符号以及哈希表


```
readelf -sD lib.so

 345 405: 0004836c    32 FUNC    GLOBAL DEFAULT  14 nanosleep
 524 152: 0003d419    88 FUNC    GLOBAL DEFAULT  14 printf
```

