# mobaXTerm 

下载网址： https://mobaxterm.mobatek.net/download-home-edition.html

## 遇到adb command not found 问题

1. 设置mobaXterm使用windows的环境变量

    Settings->Terminal 选中Use Windows PATH

2. 将adb的所在的路径添加到环境变量中

    vim /etc/profile 打开文件  
    增加如下语句  
    export PATH=$PATH:/drives/c/Users/lichengcheng/ADB_Fastboot_tools/ADB_Fastboot_tools
    
    source /etc/profile  更新环境变量
   





    


