# android crashreport


## 32位系统
    crashreporter

## 64位系统
    crashreport


在main.cpp中添加如下内容：

    #include "debugger/crash_handler.h"

    crash_handler_register();
    __system_properties_init();


## 墓碑文件路径  
    /var/system/grave/