# VoLTE 与VoIP

## 定义

### VoLTE(voice on LTE)
是一个面向手机和数据终端的高速无线通信标准。它基于IP多媒体子系统（IMS）网络，在LTE上使用为控制层面（Control plane）和语音服务的媒体层面（Media plane）特制的配置文件（由GSM协会在PRD IR.92中定义）[1]，这使语音服务（控制和媒体层面）作为数据流在LTE数据承载网络中传输，而不再需维护和依赖传统的电路交换语音网络。VoLTE的语音和数据容量超过3G UMTS三倍以上，超过2G GSM六倍以上。因为VoLTE数据包信头比未优化的VoIP/LTE更小，它也更有效地利用了带宽，只能基于4G网络


### VoIP(voice on IP)
是一种语音通话技术，经由网际协议（IP）来达成语音通话与多媒体会议，也就是经由互联网来进行通信。其他非正式的名称有IP电话（IP telephony）、互联网电话（Internet telephony）、宽带电话（broadband telephony）以及宽带电话服务（broadband phone service）应用类似facetime，网络电话软件app


#### 两者区别
1. VoLTE是基于IMS(IP 多媒体子系统)的语音业务，而不是基于传统的IP网络(Internet),是基于运营商的4G网络之上，需要支持的手机型号，也需要到营业厅专门办理该业务
2. VoIP是将语音通过某种压缩技术成为ip数据包，通过传统的ip网络从发送方送到接收方，当作为ip数据包传输的时候与其他的网络流量或者视频流没有区别，因此可能存在延迟，导致通话质量不佳
3. VoLTE只能基于4G网络，需要安装支持LTE的SIM卡，VoIP既可以在3G也可以在4G网络上
4. VoLTE的通话质量更好，VoIP既可以在3G也可以在4G网络上



