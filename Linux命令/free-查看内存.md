# free 查看内存大小
显示物理内存和交换空间的总，空闲和已用量。

## 用法
    usage: free [-bkmgt]

### 选项


1. -bkmgt	Output units (default is bytes)
2. -h	Human readable


#### 实例



    root@nutshell:/ # free -h                                                                                                                                                              
                     total    used        free      shared     buffers
    Mem:             151M        107M         45M        180K        336K
    -/+ buffers/cache:           106M         45M
    Swap:               0           0           0

    root@nutshell:/ #



