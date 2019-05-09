# gdb 使用

## print打印格式

    print/x  //十六进制
    print/f  //打印浮点数
    print *name@len

## break 设置断点

    b file：line  //文件名：行号

## next 下一步，不进入函数

    n

## step 单步调试，进入函数， finish 跳出函数
    
    s
    finish

## until 跳出循环
    
    until line //跳到指定行号


### info threads 查看当前进程的线程信息
    
    info threads


