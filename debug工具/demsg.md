# demsg工具

dmesg 是一种可以操作内核日志缓冲区的工具，它支持设置内核 log 等级，内核 log 缓冲区大小等功能，通常用于查看开机时内核启动的log



```
Usage:
dmesg [-cn][-s <缓冲区大小>]

Options:
 -c 　显示信息后，清除ring buffer中的内容。
-s<缓冲区大小> 　预设置为8196，刚好等于ring buffer的大小。
-n 　设置记录信息的层级。
```
