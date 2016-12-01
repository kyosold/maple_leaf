#include <stdio.h>
#include <string.h>
#include "ml_log.h"

int ml_log_level = info;
char ml_log_sid[1024] = {0};

void ml_log(const char *ident, int option, int facility)
{
    openlog(ident, option, facility);
}
