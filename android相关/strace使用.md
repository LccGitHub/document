# strace工具使用

## NITZ与NTP概念

用法：  
> usage:   
> strace [-CdffhiqrtttTvVwxxy] [-I n] [-e expr]...  
>   [-a column] [-o file] [-s strsize] [-P path]...  
>   -p pid... / [-D] [-E var=val]... [-u username] PROG [ARGS]    
>    or: strace -c[dfw] [-I n] [-e expr]... [-O overhead] [-S sortby]  
>   -p pid... / [-D] [-E var=val]... [-u username] PROG [ARGS]  


## 例子

    strace_64 -T -t -y -f netmgrd &

