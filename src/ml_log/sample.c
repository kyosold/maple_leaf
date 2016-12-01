#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "ml_log/ml_log.h"

int main(int argc, char **argv)
{
    // 打开maillog日志，设置程序名为log_name
    ml_log("log_name", LOG_PID|LOG_NDELAY, LOG_MAIL);

    // 设置日志ID为:tB24U1FL025441
    snprintf(ml_log_sid, sizeof(ml_log_sid), "tB24U1FL025441");

    // 设置日志等级: info
    ml_log_level = info;

    // 写日志
    ml_log_info("info log:%s", "hello, world");    // info
    ml_log_debug("debug log:%s", "hello, world");  // debug
    ml_log_error("error log:%s", "hello, world");  // error

    return 0;
}

