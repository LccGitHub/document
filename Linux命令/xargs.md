# xargs

xargs是给其他命令传递参数的过滤器，是组合多个命令的工具








### xargs实例


#### 组合命令

与find组合
查找当前录下的目录并且转为绝对路径

```
find -type d | xargs realpath
```
结果如下

```
/home/xxxx/yyy/frameworks/services/telephony
/home/xxxx/yyy/frameworks/services/telephony/test
/home/xxxx/yyy/frameworks/services/telephony/telephony
/home/xxxx/yyy/frameworks/services/telephony/src
/home/xxxx/yyy/frameworks/services/telephony/src/Tracker
/home/xxxx/yyy/frameworks/services/telephony/src/Connection
/home/xxxx/yyy/frameworks/services/telephony/src/Phone

```



