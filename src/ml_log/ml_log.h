#ifndef __ML_LOG_H__
#define __ML_LOG_H__

#include "syslog.h"

extern int  ml_log_level;
extern char ml_log_sid[1024];


#define debug   8
#define info    7   
#define notice  6
#define warning 5
#define error   4
#define crit    3
#define alert   2
#define emerg   1


#define ml_log_emerg(fmt, ...) {   \
    if(ml_log_level>=emerg){     \
        if (*ml_log_sid == '\0') { \
            syslog(LOG_EMERG, "[EMERG] %s "fmt, __func__, ##__VA_ARGS__); \
        } else { \
            syslog(LOG_EMERG, "[EMERG] %s %s "fmt, __func__, ml_log_sid, ##__VA_ARGS__); \
        } \
    } \
}

#define ml_log_alert(fmt, ...) { \
    if(ml_log_level>=alert){ \
        if (*ml_log_sid == '\0') { \
            syslog(LOG_ALERT, "[ALERT] %s "fmt, __func__, ##__VA_ARGS__); \
        } else { \
            syslog(LOG_ALERT, "[ALERT] %s %s "fmt, __func__, ml_log_sid, ##__VA_ARGS__); \
        } \
    } \
}

#define ml_log_crit(fmt, ...) { \
    if(ml_log_level>=crit){ \
        if (*ml_log_sid == '\0') { \
            syslog(LOG_CRIT, "[CRIT] %s "fmt, __func__, ##__VA_ARGS__); \
        } else { \
            syslog(LOG_CRIT, "[CRIT] %s %s "fmt, __func__, ml_log_sid, ##__VA_ARGS__); \
        } \
    } \
}

#define ml_log_error(fmt, ...) { \
    if(ml_log_level>=error){ \
        if (*ml_log_sid == '\0') { \
            syslog(LOG_ERR, "[ERROR] %s "fmt, __func__, ##__VA_ARGS__); \
        } else { \
            syslog(LOG_ERR, "[ERROR] %s %s "fmt, __func__, ml_log_sid, ##__VA_ARGS__); \
        } \
    } \
}

#define ml_log_warning(fmt, ...) { \
    if(ml_log_level>=warning){ \
        if (*ml_log_sid == '\0') { \
            syslog(LOG_WARNING, "[WARNING] %s "fmt, __func__, ##__VA_ARGS__); \
        } else { \
            syslog(LOG_WARNING, "[WARNING] %s %s "fmt, __func__, ml_log_sid, ##__VA_ARGS__); \
        } \
    } \
}

#define ml_log_notice(fmt, ...) { \
    if(ml_log_level>=notice){ \
        if (*ml_log_sid == '\0') { \
            syslog(LOG_NOTICE, "[NOTICE] %s "fmt, __func__, ##__VA_ARGS__); \
        } else { \
            syslog(LOG_NOTICE, "[NOTICE] %s %s "fmt, __func__, ml_log_sid, ##__VA_ARGS__); \
        } \
    } \
}

#define ml_log_info(fmt, ...) { \
    if(ml_log_level>=info){ \
        if (*ml_log_sid == '\0') { \
            syslog(LOG_INFO, "[INFO] %s "fmt, __func__, ##__VA_ARGS__); \
        } else { \
            syslog(LOG_INFO, "[INFO] %s %s "fmt, __func__, ml_log_sid, ##__VA_ARGS__); \
        } \
    } \
}

#define ml_log_debug(fmt, ...) { \
    if(ml_log_level>=debug){ \
        if (*ml_log_sid == '\0') { \
            syslog(LOG_DEBUG, "[DEBUG] %s "fmt, __func__, ##__VA_ARGS__); \
        } else { \
            syslog(LOG_DEBUG, "[DEBUG] %s %s "fmt, __func__, ml_log_sid, ##__VA_ARGS__); \
        } \
    } \
}

void ml_log(const char *ident, int option, int facility);


#endif
