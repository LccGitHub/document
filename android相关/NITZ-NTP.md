# NITZ NTP

## NITZ与NTP概念

NITZ:NetworkIdentityandTimeZone(网络标识和时区),是一种用于自动配置本地的时间和日期的机制,需要运营商支持,可从运营商获取时间和时区具体信息
，测试发现移动和电信在网络注册成功时会上报NITZ消息事件，联通不可以。

NTP:NetworkTimeProtocol(网络时间协议),用来同步网络中各个计算机的时间的协议。在手机中,更新主要依赖于GPRS和wifi,即通过网络的方式去获取时间

## 二者关系

- NITZ的优先级要高于NTP的优先级,当NITZ更新系统时间后,NTP即使触发更新条件,也会检查NITZ更新时间距今是否超过864000000毫秒(10天,config_ntpPollingInterval),若不满10天,则重设Alarm并取消此次NTP更新请求。

-  NITZ主要依赖于运营商上报,NTP则主要依赖于网络环境,NITZ通过被动接收获取时间,NTP通过访问NtpServer获取网络时间,最后都是通过调用SystemClock.setCurrentTimeMillis更新手机时间。 
-  NITZ是可以获取时区信息的，NTP获取的时间是没有时区的