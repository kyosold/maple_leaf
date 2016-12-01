#include <stdio.h>
#include <string.h>

#include "ml_hashmap/ml_hashmap.h"


void hash_test_func(ml_hashmap_t *hmp)
{
	char *val = NULL;
    char key[1024] = {0};
    char buf[1024] = {0};
    int j=0;
    int i=0;
    
    for(; i< 9; i++) {
		j = 0xffffff - i;
        sprintf(key, "key_%x", j);
		sprintf(buf, "val_%x", j);
        
        val = strdup(buf);
        ml_hashmap_insert(hmp, key, strlen(key), val);
	}

	for(i=0; i< 9; i++) {
        j = 0xffffff - i;
        sprintf(buf, "key_%x", j);
        
        printf("find key:%s, val:%s\n", buf, ml_hashmap_find(hmp, buf, strlen(buf)));
        
    }
}

int main(int argc, char **argv)
{
	ml_hashmap_t *map = NULL;
    
    map = ml_hashmap_create(102400);
    if(map == NULL) {
        printf("create hashmap error:%m");
        return -1;
    }
    
    
    hash_test_func(map);
    
    
    ml_hashmap_free(map);
    
    return 0;	
}
