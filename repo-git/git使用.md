
## repo forall -c
 Command (and arguments) to execute

1. repo sync //保证当前代码为远程最新代码，没有未修改的代码
2. repo forall -c "git checkout -b RV_180723"   //给所有仓库创建RV_180723分支
3. repo forall -c "git push RV_180723：RV_180723" //把新建的分支提交到远程

4. repo sync //同步代码，可以显示新的分支
5. repo start --all RV_180723 //所有仓库切到RV_180723分支





## 拷贝本地仓库的内容到远程创建远程仓库

1. git init //创建本地仓库
2. git add/git commit 写代码-commit-fix-commit等操作
3. 等待已经开发完基本机能此时可以把整个代码目录拷贝到远程的仓库，方法如下：
- 在本地执行 :scp -r  copytest/ xxx@192.168.28.14:~//workspace/xxx/platform/frameworks/services/   //拷贝本地目录 到远程目录
- 在已经拷贝的远程仓库执行:xxx@xxx:~/workspace/xxx/platform/frameworks/services/copytest$ git checkout -b minixxx  //创建minixxx分支与远程分支一致
 - 在已经拷贝的远程仓库执行:xxx@xxx:~/workspace/xxx/platform/frameworks/services/copytest$ git config core.bare true
 - 在xxx@xxx:~/workspace/xxx/platform/manifest/default.xml添加一下内容
       <project path="frameworks/services/copytest" name="platform/frameworks/services/copytest" groups="pdk" />
 - 提交该次修改
     xxx@xxx:~/workspace/xxx/platform/manifests$ git commit -m "copytest service" 
4. 在本地重新同步代码
   repo sync


## 在远程创建仓库
1. git init
2. git commit -m
3. git checkout -b 可选
4. git config core.bare true
5. 修改manifest下面的default.xml
5. 提交本次修改




”git init –bare”方法创建一个所谓的裸仓库，之所以叫裸仓库是因为这个仓库只保存git历史提交的版本信息，而不允许用户在上面进行各种git操作




## linux与windons代码末尾符设置



```
~$ git config --global core.autocrlf input
~$ git config --global core.safecrlf true
~$ git config --global color.ui true
```
