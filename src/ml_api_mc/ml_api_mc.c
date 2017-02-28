
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

#include <libmemcached/memcached.h>

#include "ml_api_mc.h"


/**
 *  设置key->value到MC中
 *
 *  @param mc_ip      mc 地址
 *  @param mc_port    mc 端口
 *  @param mc_timeout mc 超时时间
 *  @param mc_key     key
 *  @param mc_value   value
 *
 *  @return 0:succ  1:notfound 2:connect fail 3:其它错误
 */
int ml_api_mc_set(char *mc_host, int mc_port, int mc_timeout, char *mc_key, void *data, size_t d_size, time_t expiration)
{
    size_t nval     = 0;
    uint32_t flag   = 0;
    char *result    = NULL;
    int ret         = ML_API_MC_RET_CONN_FAIL;

    memcached_st        *memc = memcached_create(NULL);
    memcached_return    mrc;
    memcached_server_st *mc_servers;

    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_NO_BLOCK, 1);
    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_CONNECT_TIMEOUT, mc_timeout);

    mc_servers= memcached_server_list_append(NULL, mc_host, mc_port, &mrc);
    if (MEMCACHED_SUCCESS == mrc) {

        mrc= memcached_server_push(memc, mc_servers);
        memcached_server_list_free(mc_servers);
        if (MEMCACHED_SUCCESS == mrc) {
            mrc = memcached_set(memc, mc_key, strlen(mc_key), data, d_size, expiration, (uint32_t)flag); 
            if (MEMCACHED_SUCCESS == mrc) {
                ret = ML_API_MC_RET_SUCC;
            } else if (MEMCACHED_NOTFOUND == mrc){
                ret = ML_API_MC_RET_NOTFOUND;
            } else if (MEMCACHED_CONNECTION_FAILURE == mrc) {
                ret = ML_API_MC_RET_CONN_FAIL;
            } else {
                ret = ML_API_MC_RET_FAIL;
            } 
        } else {
            ret = ML_API_MC_RET_FAIL;
        }

        memcached_free(memc);
        return ret;
    }

    memcached_free(memc);

    return ret;
}

/**
 *  从mc中删除一个key
 *
 *  @param mc_ip      mc 地址
 *  @param mc_port    mc 端口
 *  @param mc_timeout mc 超时时间
 *  @param mc_key     需要被删除的key
 *
 *  @return 0:succ 1:key not found 2:fail
 */
int ml_api_mc_delete(char *mc_host, int mc_port, int mc_timeout, char *mc_key)
{
    size_t nval     = 0;
    uint32_t flag   = 0;
    char *result    = NULL;
    int ret         = ML_API_MC_RET_CONN_FAIL;

    memcached_st        *memc = memcached_create(NULL);
    memcached_return    mrc;
    memcached_server_st *mc_servers;

    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_NO_BLOCK, 1);
    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_CONNECT_TIMEOUT, mc_timeout);

    mc_servers= memcached_server_list_append(NULL, mc_host, mc_port, &mrc);  
    if (MEMCACHED_SUCCESS == mrc) {
        mrc= memcached_server_push(memc, mc_servers);
        memcached_server_list_free(mc_servers);
        if (MEMCACHED_SUCCESS == mrc) {
            mrc = memcached_delete(memc, mc_key, strlen(mc_key), 0);
            if (MEMCACHED_SUCCESS == mrc) {
                ret = ML_API_MC_RET_SUCC;
            } else if (MEMCACHED_NOTFOUND == mrc) {
                ret = ML_API_MC_RET_NOTFOUND;
            } else {
                ret = ML_API_MC_RET_FAIL;
            }

        } else {
            ret = ML_API_MC_RET_FAIL;
        }

        memcached_free(memc);
        return ret;
    }

    memcached_free(memc);
    return ret;
}


/**
 *  从mc中获取key的值
 *
 *  @param mc_ip         mc 地址
 *  @param mc_port       mc 端口
 *  @param mc_timeout    mc 超时时间
 *  @param mc_key        需要获取值的key
 *  @param mc_value      获取的结果
 *  @param mc_value_size 获取结果的buffer长度
 *  @param flag          获取结果的flag (0:成功, 1:notfound, 2:connect fail, 3:其它错误)
 *
 *  @return NULL:失败
 */
void *ml_api_mc_get(char *mc_host, int mc_port, int mc_timeout, char *mc_key, int *ret)
{
    size_t nval     = 0;
    uint32_t flag   = 0;
    void *result    = NULL;
    *ret            = ML_API_MC_RET_CONN_FAIL;

    memcached_st        *memc = memcached_create(NULL);
    memcached_return    mrc;
    memcached_server_st *mc_servers;

    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_NO_BLOCK, 1);
    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_CONNECT_TIMEOUT, mc_timeout);

    mc_servers= memcached_server_list_append(NULL, mc_host, mc_port, &mrc);
    if (MEMCACHED_SUCCESS == mrc) {
        mrc= memcached_server_push(memc, mc_servers);
        memcached_server_list_free(mc_servers);
        if (MEMCACHED_SUCCESS == mrc) {
            result = memcached_get(memc, mc_key, strlen(mc_key), (size_t *)&nval, &flag, &mrc);
            if (MEMCACHED_SUCCESS == mrc) {
                *ret = ML_API_MC_RET_SUCC;
            } else if (MEMCACHED_NOTFOUND == mrc) {
                *ret = ML_API_MC_RET_NOTFOUND;
            } else if (MEMCACHED_CONNECTION_FAILURE == mrc) {
                *ret = ML_API_MC_RET_CONN_FAIL;
            } else {
                *ret = ML_API_MC_RET_FAIL;
            }
        } else {
            *ret = ML_API_MC_RET_FAIL;
        }

        memcached_free(memc);
        return result;
    }
    
    memcached_free(memc);
    return result;
}



#ifdef APIMC_TEST

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


#endif


