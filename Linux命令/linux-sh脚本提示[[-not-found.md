# Linux shell脚本执行提示错误[[: not found


### 场景

    #! /bin/bash
    if [ $# -lt 1 ];then
    echo "need parameter"
    exit
    fi
    
    
    if [[ $# = 2 && $2 = "clean" ]];then
    echo "clean"
    fi

### 原因是sh指向的脚本指向不同
    $ ll /bin/sh
    lrwxrwxrwx 1 root root 4  1月 28 14:16 /bin/sh -> dash*

bash 与bash语法差别，导致该问题的出现

### bash与dash区别与联系

dash是bash的裁剪版，Dash Shell 比 Bash Shell 小的多，符合POSIX标准。 


#### bash与dash的语法区别

链接：[https://www.jianshu.com/p/762d4cccee7e](https://www.jianshu.com/p/762d4cccee7e)

    1.定义函数
    bash: function在bash中为关键字
    dash: dash中没有function这个关键字
    2.select var in list; do command; done
    bash:支持
    dash:不支持, 替代方法:采用while+read+case来实现
    3. echo {0..10}
    bash:支持{n..m}展开
    dash:不支持，替代方法, 采用seq外部命令
    4. here string
    bash:支持here string
    dash:不支持, 替代方法:可采用here documents
    5. >&word重定向标准输出和标准错误
    bash: 当word为非数字时，>&word变成重定向标准错误和标准输出到文件word
    dash: >&word, word不支持非数字, 替代方法: >word 2>&1; 常见用法 >/dev/null 2>&1
    6. 数组
    bash: 支持数组, bash4支持关联数组
    dash: 不支持数组，替代方法, 采用变量名+序号来实现类似的效果
    7. 子字符串扩展
    bash: 支持${parameter:offset:length},${parameter:offset}
    dash: 不支持， 替代方法:采用expr或cut外部命令代替
    8. 大小写转换
    bash: 支持${parameter^pattern},${parameter^^pattern},${parameter,pattern},${parameter,,pattern}
    dash: 不支持，替代方法:采用tr/sed/awk等外部命令转换
    9. 进程替换<(command), >(command)
    bash: 支持进程替换
    dash: 不支持, 替代方法, 通过临时文件中转
    10. [ string1 = string2 ] 和 [ string1 == string2 ]
    bash: 支持两者
    dash: 只支持=
    11. [[ 加强版test
    bash: 支持[[ ]], 可实现正则匹配等强大功能
    dash: 不支持[[ ]], 替代方法，采用外部命令
    12. for (( expr1 ; expr2 ; expr3 )) ; do list ; done
    bash: 支持C语言格式的for循环
    dash: 不支持该格式的for, 替代方法，用while+$((expression))实现
    13. let命令和((expression))
    bash: 有内置命令let, 也支持((expression))方式
    dash: 不支持，替代方法，采用$((expression))或者外部命令做计算
    14. $((expression))
    bash: 支持id++,id--,++id,--id这样到表达式
    dash: 不支持++,--, 替代方法:id+=1,id-=1, id=id+1,id=id-1
    


