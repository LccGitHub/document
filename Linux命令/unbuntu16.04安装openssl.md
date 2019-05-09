## openssl安装

平台： ubuntu16.04  
下载网址： https://www.openssl.org/source/  
解压命令： tar -xzf 	openssl-1.1.1b.tar.gz   

### 编译

    $ cd openssl-1.1.1b
    $ ./config
    $ make
    $ make install

### 使用时出现编译问题
    openssl: error while loading shared libraries: libssl.so.1.1: cannot open shared object file: No such file or directory

解决方法：


    $ ln -s /usr/local/lib/libssl.so.1.1 /usr/lib/libssl.so.1.1  
    $ ln -s /usr/local/lib/libcrypto.so.1.1 /usr/lib/libcrypto.so.1.1