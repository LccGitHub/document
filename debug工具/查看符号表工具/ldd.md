# ldd 显示所依赖的共享库列表

ldd命令用于打印程序或者库文件所依赖的共享库列表。
## 语法

```
ldd(选项)(参数)
```

## 选项

```
--version：打印指令版本号；
-v：详细信息模式，打印所有相关信息；
-u：打印未使用的直接依赖；
-d：执行重定位和报告任何丢失的对象；
-r：执行数据对象和函数的重定位，并且报告任何丢失的对象和函数；
--help：显示帮助信息。
```

例子


```
ldd -v /lib64/ld-linux-x86-64.so.2

	statically linked
```


```
ldd  a.out 
	linux-vdso.so.1 =>  (0x00007fff847a1000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f080ef3e000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f080ec38000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f080ea22000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f080e658000)
	/lib64/ld-linux-x86-64.so.2 (0x0000555cbb2b5000)

```



