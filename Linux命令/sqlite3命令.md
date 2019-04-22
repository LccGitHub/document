# sqlite3常用命令


## 查看表的信息
    .schema   查询创建表的信息
    .tables   查询当前表列表
    .show     显示当前设置的值


### 查询信息


    select 字段(以”,”隔开) from 表名 where 条件;  选择查询
    select 字段 from table1 order by 字段(desc或asc)  ;(降序或升序)
    select count(*) from table1;  总数
    select sum(field1) from table1; 求和
    select avg(field1) from table1; 平均
    select max(field1) from table1; 最大
    select min(field1) from table1; 最小



#### 修改

    update 表名 set 字段=’修改后的内容’ where 条件;   更新
    insert  into 表名 values(, , ,) ;    插入
    Alter table 表名 add column 字段 数据类型;   增加一个列



