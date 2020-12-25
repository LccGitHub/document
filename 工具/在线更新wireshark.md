ubuntu在线升级wirshark 方法

    sudo apt-add-repository ppa:wireshark-dev/stable
    sudo apt-get update
    sudo apt-get install wireshark


    sudo dpkg-reconfigure wireshark-common

中间会出现设置界面，选择<是>即可

    wireshark --version
    
    
 参考链接： https://blog.csdn.net/bryanting/article/details/53327575   
