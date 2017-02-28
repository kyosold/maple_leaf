#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml_api_mc.h"

int main(int argc, char **argv)
{
    char *mc_server = argv[1];
    char *mc_port = argv[2];
    char *mc_timeout = argv[3];

    // set mc
    char *key = "name";
    char *value = "kyosold@qq.com";

    int succ = ml_api_mc_set(mc_server, atoi(mc_port), atoi(mc_timeout), key, value, strlen(value), 0); 
    if (succ == ML_API_MC_RET_SUCC) {
        printf("set mc succ: [%s] => [%s]\n", key, value);
    } else {
        printf("set mc fail");
    }   

    // get mc
    int ret = 0;
    char *pvalue = (char *)ml_api_mc_get(mc_server, atoi(mc_port), atoi(mc_timeout), key, &ret);
    if (pvalue) {
        printf("get mc succ: [%s] => [%s]\n", key, pvalue);

        free(pvalue);
        pvalue = NULL;
    } else {
        printf("get mc fail, ret[%d]\n", ret);
    }

    // delete mc
    succ = ml_api_mc_delete(mc_server, atoi(mc_port), atoi(mc_timeout), key);
    if (succ == 0) {
        printf("delete mc succ:%s\n", key);
    } else {
        printf("delete mc fail:%s\n", key);
    }

    return 0;
}
