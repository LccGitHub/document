# update_engine移植
移植android里面的update-engine到linux系统的嵌入式平台

### 下载android的update-engine源码

android的git源码地址

https://android.googlesource.com/

拉取代码

    git clone https://android.googlesource.com/platform/system/update_engine
    
## 修改点

1. 修改引用的头文件



2. 增加依赖库

update_engine->libbrillo-stream,libbrillo,libchrome->

libandroid.so

libbrillo-stream
libchrome.so

libevent.so
libmodpb64.a

valgrind.h

update_engine->libupdate_engine


    libandroid \
        libbinderwrapper \
        

1. undefined reference to `typeinfo for xxx’。typeinfo

原因如下:

    虚函数未实现
    混用了no-RTTI代码和RTTI代码


        
        
编译问题

    undefined reference to symbol '_ZN7android4base10LogMessage6streamEv'

    $ c++filt _ZN7android4base10LogMessage6streamEv
    android::base::LogMessage::stream()
    
    
## 编译依赖

### 库依赖库如下：

    新增加
    libbrillo-stream.so  // /external/libbrillo
    libbrillo.so // /external/libbrillo
    libbrillo-binder.so // externals/libbrillo
    
    新增加
    libchrome.so  // /external/libchrome
    
    
    新增加
    libandroid.so // /frameworks/base/native/android/
    
    新增加
    libbinderwrapper.so // system/core/libbinderwrapper
    
    
    

    libcurl.so // externals/libcurl
    libprotobuf-lite.so // externals/protobuf
    libcrypto.so // external/boringssl/
    libssl.so // external/boringssl/
    
    
    libbionic.so // system/core/libbionic
    libcutils.so // system/core/libcutils
    libutils.so // system/core/libutils
    libbase.so // system/core/base
    libbinder.so // system/core/binder/
    
    
    libhardware.so // hardware/libhardware


    libstdc++.so.6 // 系统c++库
    libc.so.6  // 系统c库
    
### libandroid依赖
需要在android git 官网下载frameworks/base仓库切到7.12分支，做如下变更：

1. 修改Android.mk为nutshell.mk
2. 在nutshell.mk中删除目前update_engine不需要编译的模块

查看我们编译出来的libandroid的库如下：

    libnetd_client.so // 需要修改system/netd的文件，一编译通过
    
### libchrome.so 依赖
需要在android git 官网下载frameworks/base仓库切到7.12分支，做如下变更：
1. 修改Android.mk为nutshell.mk
2. 修改一些LOG为DLOG

查看我们编译出来的libandroid的库如下：
    libevent.so  // externals/libevent



## 需要提交修改的仓库如下：

    frameworks/base/native/android  //官网下载
    system/netd  //从aeri项目一直而来
    system/core/libbinderwrapper // 从官网core/libbinderwrapper下载
    externals/libchrome // 官网下载
    externals/libevent // 官网下载
    external/libbrillo
    externals/modp_b64
    hardware/libhardware
    