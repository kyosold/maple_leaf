#ifndef __ML_API_MC_H_
#define __ML_API_MC_H_


#define ML_API_MC_RET_SUCC      0
#define ML_API_MC_RET_NOTFOUND  1
#define ML_API_MC_RET_CONN_FAIL 2
#define ML_API_MC_RET_FAIL      3



int ml_api_mc_set(char *mc_host, int mc_port, int mc_timeout, char *mc_key, void *data, size_t d_size, time_t expiration);

int ml_api_mc_delete(char *mc_host, int mc_port, int mc_timeout, char *mc_key);

void *ml_api_mc_get(char *mc_host, int mc_port, int mc_timeout, char *mc_key, int *ret);


#endif
