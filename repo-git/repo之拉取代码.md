# repo之拉取代码


## 下载和安装repo

```
git clone https://gerrit.googlesource.com/git-repo

```

将git-repo目录下的repo脚本放到系统目录下，方便使用
```
cd git-repo
sudo cp repo /usr/bin 
sudo chmod a+x  /usr/bin/repo 
```
删掉本地git-repo仓库

```
rm -rf git-repo
```


## 下载远程代码

创建工程目录

```
mkdir projectname 
cd projectname 
```
 清单库的初始化
 
```
repo init -u ssh://192.xxx.8.74:29418/Src/XX/platform/manifest -b branchname
```
执行cat .repo/manifest.xml 能输出清单文件

按照清单获取工程代码
```
repo sync
```

开始在本地主分支上工作

```
repo start branchname --all
```






