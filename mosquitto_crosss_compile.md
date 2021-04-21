## mosquitto 交叉编译以及测试

 ### 编译依赖工具
 
    sudo apt-get install -y xsltproc
    sudo apt-get install xmlto

### 编译

    export PATH=$PATH:/opt/ql_crosstools/ql-ag550qcn-le20-gcc820-v1-toolchain/gcc/usr/bin/arm-oe-linux/
    export CC=arm-oe-linux-gcc
    export CXX=arm-oe-linux-g++
    export AR=arm-oe-linux-ar
    export LD=arm-oe-linux-ld

    export CFLAGS='-march=armv7-a -marm -mfpu=neon -mfloat-abi=hard --sysroot=/home/xxx/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots -I. -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/include -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include/ql_lib_utils -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include/ql-sdk  -Wall -Wundef -finline-functions -finline-limit=64'
    export CXXFLAGS='-march=armv7-a -marm -mfpu=neon -mfloat-abi=hard --sysroot=/home/xxx/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots -I. -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/include -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include/ql_lib_utils -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include/ql-sdk  -Wall -Wundef -finline-functions -finline-limit=64'

    export LDFLAGS='-march=armv7-a -marm -mfpu=neon -mfloat-abi=hard --sysroot=/home/xxx/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots -I. -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/include -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include/ql_lib_utils -I/home/lichengcheng/workspace_gitlab/kaido3.0/ag550/ql-ol-sdk/ql-ol-extsdk/ql-sysroots/usr/include/ql-sdk  -Wall -Wundef -finline-functions -finline-limit=64'

    export DESTDIR=./out

    make

    make install
    

### 测试

#### 1. 订阅消息 
    mosquitto_sub -h mq.iauto.com -p 8883 -t server/tcu/123456789 --cafile ./mqttcertificate/ca_certificate.pem --cert ./mqttcertificate/client_certificate.pem --key ./mqttcertificate/client_key.pem --tls-version tlsv1.2 -d --insecure -u guest -P gy683hj36o
    
#### 1.1 订阅成功的日志
    
    Client mosqsub|428-xxxx sending CONNECT
    Client mosqsub|428-xxxx received CONNACK
    Client mosqsub|428-xxxx sending SUBSCRIBE (Mid: 1, Topic: server/tcu/123456789, QoS: 0)
    Client mosqsub|428-xxxx received SUBACK
    Subscribed (mid: 1): 0
    Client mosqsub|428-xxxx sending PINGREQ
    Client mosqsub|428-xxxx received PINGRESP
    Client mosqsub|428-xxxx received PUBLISH (d0, q0, r0, m0, 'server/tcu/123456789', ... (8 bytes))
    i am lcc
    Client mosqsub|428-xxxx sending PINGREQ
    Client mosqsub|428-xxxx received PINGRES


#### 2. 发布消息

    mosquitto_pub -h mq.iauto.com -p 8883 -t server/tcu/123456789 --cafile ./mqttcertificate/ca_certificate.pem --cert ./mqttcertificate/client_certificate.pem --key ./mqttcertificate/client_key.pem --tls-version tlsv1.2 -d --insecure -u guest -P gy683hj36o -m "i am tester"
    
    
#### 2.1 发布消息    

    Client mosqpub|574-xxxx sending CONNECT
    Client mosqpub|574-xxxx received CONNACK
    Client mosqpub|574-xxxx sending PUBLISH (d0, q0, r0, m1, 'server/tcu/123456789', ... (8 bytes))
    Client mosqpub|574-xxxx sending DISCONNECT
