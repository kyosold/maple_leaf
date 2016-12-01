#include <syslog.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <stdint.h>

#include "ml_hashmap.h"


static uint32_t primes[] =
{
    3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 
    107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919,
    1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419,
    10103, 12143, 14591, 17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523,
    108631, 130363, 156437, 187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897,
    1162687, 1395263, 1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369
};


/**
 * hashmap_hash - hash a string
 * hashcode_index -- RShash
 * hashcode_create -- BKDRhash
 */
inline static uint32_t hashcode_index(char *key, int len, uint32_t size)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    char *str = key;

    while (len-- > 0) {
        hash = hash * a + (*str++);
        a *= b;
    }

    return (uint32_t )(hash & 0x7FFFFFFF) % size;
}

inline static uint32_t hashcode_create(char *key, int len)
{
    uint32_t seed = 131;
    uint32_t hash = 0;
    char *str = key;

    while (len-- > 0)
        hash = hash * seed + (*str++);

    return (hash & 0x7FFFFFFF);
}

// hashmap_link - insert element into map
void hashmap_link(ml_hashmap_t *map, ml_hashmap_entry_t *elm)
{
    ml_hashmap_entry_t **etr = map->data + hashcode_index((elm)->key, (elm)->key_len , map->size);
    if (((elm)->next = *etr) != NULL)
        (*etr)->prev = elm;
    *etr = elm;
    map->used++;
}

//  hashmap_size - allocate and initialize hash map
static int hashmap_size(ml_hashmap_t *map, unsigned size)
{
    ml_hashmap_entry_t **h;

    map->data = h = (ml_hashmap_entry_t **) calloc(size, sizeof(ml_hashmap_entry_t *));
    if(!h) {
        return -1;
    }
    map->size = size;
    map->used = 0;

    while (size-- > 0)
        *h++ = 0;

    return 0;
}

// hashmap_grow - extend existing map
static int hashmap_grow(ml_hashmap_t *map)
{
    ml_hashmap_entry_t *ht;
    ml_hashmap_entry_t *next;
    unsigned old_size = map->size;
    ml_hashmap_entry_t **h = map->data;
    ml_hashmap_entry_t **old_entries = h;
    
    if(hashmap_size(map, primes[++map->idx]) == -1) {
        return -1;
    }
    
    while (old_size-- > 0) {
        for (ht = *h++; ht; ht = next) { 
            next = ht->next;
            hashmap_link(map, ht);
        }   
    }       
            
    if (old_entries) {
        free((char *) old_entries);
        old_entries = NULL;
    }
        
    return 0;
}

// hashmap_locate - lookup entry 
ml_hashmap_entry_t *hashmap_locate(ml_hashmap_t *map, char *key, int key_len)
{
    ml_hashmap_entry_t *ht;
    uint32_t idx = hashcode_index(key, key_len, map->size);
    uint32_t hc = hashcode_create(key, key_len);

    if (map) {
        for (ht = map->data[idx]; ht; ht = ht->next) {
            if (key_len == ht->key_len && hc == ht->hash_code && (memcmp(key, ht->key, ht->key_len) == 0))
                return (ht);
        }
    }

    return (0);
}





/**
 * ml_hashmap_create - create initial hash map
 * 创建与初始化hash map
 *
 * @param   size  该函数返回按指针大小分配的字典对象，如果你不知道需要存储到字典的条目，可以给: size=0;
 *
 * @return  成功:指向创建的map 失败:NULL 
 */
ml_hashmap_t *ml_hashmap_create(int size)
{
    ml_hashmap_t *map = (ml_hashmap_t *)calloc(1, sizeof(ml_hashmap_t));
    if (map == NULL) {
        //printf("calloc fail\n");
        return NULL;
    }

    uint8_t idx = 0;

    for(; idx < sizeof(primes) / sizeof(uint32_t); idx++) {
        if(size < primes[idx]) {
            break;
        }
    }

    if(idx >= sizeof(primes) /  sizeof(uint32_t))
        return NULL;

    map->idx = idx;

    return map;
}


/**
 * ml_hashmap_insert - enter (key, value) pair
 * 添加条目到map中, 该函数可以添加相同的key到map中，
 * 但是find时只会取到一个，但是遍历时会查看到，所以
 * 强烈建议在insert前先做find。
 *
 * @param   map     被添加到的map
 * @param   key     添加的key
 * @param   key_len key的字符串长度
 * @param   value   添加的key的值 (该值内存需要手动分配)
 *
 * @return  成功返回新生成的条目，该条目被内部分配内存，不要手动free它。失败返回NULL
 *
 * @notice  **使用先应该先使用find做key查询，如果你确定可以insert多个相同的key的话可以忽略**
 */
ml_hashmap_entry_t *ml_hashmap_insert(ml_hashmap_t *map, char *key, uint32_t key_len, void *value)
{
    ml_hashmap_entry_t *ht = NULL;

    if ((map->used >= map->size) && hashmap_grow(map)==-1) {
        //printf("hashmap_grow error:%m");
        return NULL;
    }

    ht = (ml_hashmap_entry_t *)calloc(1, sizeof(ml_hashmap_entry_t) + key_len + 1);
    if(!ht) {
        //printf("malloc hashmap entry error:%m");
        return NULL;
    }

    // don't need free key, it just free ht.
    ht->key = (char *)(ht + 1);
    memcpy(ht->key, key, key_len);
    ht->key_len = key_len;
    ht->value = value;
    ht->hash_code = hashcode_create(key, key_len);
    hashmap_link(map, ht);

    //printf("key:%s, val:%s, klen:%d\n", key, value, key_len);

    return (ht);
}

/**
 * ml_hashmap_find - lookup value
 * 获取指定key的值, 获取指定key的值，如果有多个key相同，返回最新的
 *
 * @param   map     被查询的hash map
 * @param   key     指定需要获取值的key
 * @param   key_len key的字符串长度
 *
 * @return  找到返回value, 没找到返回NULL
 */
void *ml_hashmap_find(ml_hashmap_t *map, char *key, int key_len)
{
    ml_hashmap_entry_t *ht;
    uint32_t idx = hashcode_index(key, key_len , map->size);
    uint32_t hc = hashcode_create(key, key_len);

    if (map) {
        for (ht = map->data[idx]; ht; ht = ht->next) {
            if (key_len == ht->key_len && hc == ht->hash_code
                && (memcmp(key, ht->key, ht->key_len) == 0))
                return (ht->value);
        }
    }

    return NULL;
}

/**
 * ml_hashmap_delete - delete one entry
 * 从map中删除一个entry, 该函数会自动free掉value的内存，之前手动分配的内存不用理了。
 *
 * @param   map     被操作的hash map
 * @param   key     指定需要删除条目的key
 * @param   key_len key的字符串长度
 *
 * @return  0:成功 其它:失败
 *
 * @notice  **该函数会自动free掉value的内存，之前手动分配的内存不用理了**
 */
int ml_hashmap_delete(ml_hashmap_t *map, char *key, int key_len)
{
    if (map != NULL) {
        ml_hashmap_entry_t **h = map->data + hashcode_index(key, key_len, map->size);
        ml_hashmap_entry_t *ht = *h;
        uint32_t hc = hashcode_create(key, key_len);

        for (; ht; ht = ht->next) {
            if (key_len == ht->key_len
                && hc == ht->hash_code
                && !memcmp(key, ht->key, ht->key_len)) 
            {
                if (ht->next)
                    ht->next->prev = ht->prev;

                if (ht->prev)
                    ht->prev->next = ht->next;
                else
                    *h = ht->next;

                map->used--;

                // free ht item
                if (ht->value != NULL) {
                    free(ht->value);
                    ht->value = NULL;
                }

                if (ht != NULL) {
                    free(ht);
                    ht = NULL;
                }


                return 0;

            }
        }
    }

    return 1;
}


/**
 * ml_hashmap_free - destroy hash map 
 * 清理hash map
 *
 * @param   map     被清理的hash map
 */
void ml_hashmap_free(ml_hashmap_t *map)
{
    if (map != NULL) {
        unsigned i = map->size;
        ml_hashmap_entry_t *ht;
        ml_hashmap_entry_t *next;
        ml_hashmap_entry_t **h = map->data;

        while (i-- > 0) {
            for (ht = *h++; ht; ht = next) {
                next = ht->next;

                if (ht->value) {
                    free(ht->value);
                    ht->value = NULL;
                }
                if (ht) {
                    free(ht);
                    ht = NULL;
                }
            }
        }

        if (map->data) {
            free(map->data);
            map->data = NULL;
        }
        free(map);
        map = NULL;
    }
}



/**
 * ml_hashmap_walk - iterate over hash map 
 * 递归遍历hash map中的entry, 递归遍历hash map中的entry,每个entry调用一个回调函数
 *
 * @param   map     被递归遍历的hash map
 * @param   action  回调函数，返回map中每个entry
 *  @param   entry  map中的每个entry
 *  @param   ptr    作用是标记调用hashmap_walk时的ID
 * @param   ptr     用于在回调函数中标记会话的ID
 *
 */
void ml_hashmap_walk(ml_hashmap_t *map, void (*action) (ml_hashmap_entry_t *, char *), char *ptr)
{
    if (map) {
        unsigned i = map->size;
        ml_hashmap_entry_t **h = map->data;
        ml_hashmap_entry_t *ht;

        while (i-- > 0)
            for (ht = *h++; ht; ht = ht->next)
                (*action) (ht, ptr);
    }
}



/**
 * ml_hashmap_list - list all map members
 * 列表map中所有的entry, 列表map中所有的entry
 *
 * @param   map     被递归遍历的hash map
 *
 * @return  返回map中的entry数组列表，失败返回NULL
 */
ml_hashmap_entry_t **ml_hashmap_list(ml_hashmap_t *map)
{
    ml_hashmap_entry_t **list;
    ml_hashmap_entry_t *member;
    int     count = 0;
    int     i;

    if (map != 0) {
        list = (ml_hashmap_entry_t **) calloc((map->used + 1), sizeof(*list));
        if(!list) {
            //printf("calloc error:%m");
            return NULL;
        }

        for (i = 0; i < map->size; i++)
            for (member = map->data[i]; member != 0; member = member->next)
                list[count++] = member;
    } else {
        list = (ml_hashmap_entry_t **) calloc(1, sizeof(*list));
        if(!list) {
            //printf("calloc error:%m");
            return NULL;
        }
    }

    list[count] = 0;

    return (list);
}




