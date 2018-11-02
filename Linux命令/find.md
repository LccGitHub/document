# find
find用于在文件树种查找文件，并作出相应的处理

## 命令格式

```
　find pathname  -options [-print  -exec  -ok]
```

### options 命令参数

```
-name 按照文件名查找文件
-type 查找某一类型的文件，例如
       b：块设备文件
       d：目录文件
       c：字符设备文件
       p：管道文件
       l：符号链接文件
       f：普通文件
-perm 按照文件权限查找文件

```

