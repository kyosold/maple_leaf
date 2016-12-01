ml_log
=======

Intro
-----
[ml_log] 是封装使用syslog写日志的函数库，支持设置日志等级(debug -> emerg)

-----
日志等级说明: 设置log_level后，小于等于该等级的日志都可以被打印到日志中。
```bash
    debug    8
    info     7
    notice   6
    warning  5
    error    4
    crit     3
    alert    2
    emerg    1
````


Usage
------------
```bash
    // 引用头文件
    #include "ml_log.h"

    // 打开maillog日志，设置程序名为log_name
    ml_log("log_name", LOG_PID|LOG_NDELAY, LOG_MAIL);

    // 设置日志ID为:tB24U1FL025441
    snprintf(ml_log_sid, sizeof(ml_log_sid), "tB24U1FL025441");

    // 设置日志等级: info
    ml_log_level = info;

    // 写日志
    ml_log_info("info log:%s", "hello, world");    # info
    ml_log_debug("debug log:%s", "hello, world");  # debug
    ml_log_error("error log:%s", "hello, world");  # error
````

编译与运行
------------
```bash
cp /usr/local/maple_leaf/share/maple_leaf/ml_log/sample.c ./sample.c

gcc -g -o sample sample.c -I /usr/local/maple_leaf/include/ -L /usr/local/maple_leaf/lib64/maple_leaf/ml_log/ -lml_log
````

#### 动态库引入

```bash
echo "/usr/local/maple_leaf/lib64/maple_leaf/ml_log/" >> /etc/ld.so.conf.d/maple_leaf.conf
/sbin/ldconfig
````
