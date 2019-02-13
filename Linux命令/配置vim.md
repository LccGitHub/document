
参考链接如下：

[https://blog.csdn.net/shy19910509/article/details/80701126](https://blog.csdn.net/shy19910509/article/details/80701126)

## help变为中文

1. 安装方法:

在下面的网站下载中文帮助的文件包:

    $wget http://nchc.dl.sourceforge.net/sourceforge/vimcdoc/vimcdoc-1.5.0.tar.gz
    
    解包后进入文件夹，使用以下命令安装：
    $sudo ./vimcdoc.sh -i

启动vim，输入:help，看看帮助文档是否已经便成中文了

2. 注意：

vim中文文档不会覆盖原英文文档，安装后vim默认使用中文文档。若想使用英文文档，可在vim中执行以下命令：

     `set helplang=en`

同理，使用以下命令可重新使用中文文档：

     `set helplang=cn`

帮助文件的文本是utf-8编码的, 如果想用vim直接查看, 需要在~/.vimrc中设置:
   `set encoding=utf-8`


### 修改.vimrc文件

修改如下文件
$ vim .vimrc

#### 语法高亮
增加如下语句

    syntax enable
    syntax on


#### 选择配色
    colorscheme desert
