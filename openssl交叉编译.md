
下载链接： https://www.openssl.org/source/old/1.1.0/

解压文件： tar cvf openssl-1.1.0.tar.gz

    dbef70de4a1a4bdd78ab7c6547e5211d  openssl-1.1.0.tar.gz


    export PATH=$PATH:~/workspace/xxx/prebuilt/toolchain/aarch64-xx-linux/bin    
    export CC=aarch64-fsl-linux-gcc    
    export CXX=aarch64-fsl-linux-g++    
    export AR=aarch64-fsl-linux-ar    
    export LD=aarch64-fsl-linux-ld   
    ./config no-asm shared no-afalgeng  --prefix=/home/xx/workspace3/openssl-1.1.0/out/   
    gedit Makefile  //注释掉-m64的内容 ，一共有两处   
    make -j8     
    make install    
