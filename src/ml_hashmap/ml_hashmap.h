#ifndef __ML_HASHMAP_H__
#define __ML_HASHMAP_H__

#include <stdint.h>


/* Structure of one hash table entry. */
typedef struct ml_hashmap_entry_st ml_hashmap_entry_t;

struct ml_hashmap_entry_st 
{
    char                *key;           /* lookup key */
    uint32_t            key_len;
    uint32_t            hash_code;      /* hash code */
    char                *value;         /* associated value */
    ml_hashmap_entry_t  *next;          /* colliding entry */
    ml_hashmap_entry_t  *prev;          /* colliding entry */
};

/* Structure of one hash table. */
typedef struct ml_hashmap_st
{
    uint32_t            size;           /* length of entries array */
    uint16_t            used;           /* number of entries in table */
    uint8_t             idx;            /* primes id */
    ml_hashmap_entry_t  **data;         /* entries array, auto-resized */
} ml_hashmap_t;



/**
 * ml_hashmap_create - create initial hash map
 * 创建与初始化hash map, map后面使用时如果不够会自动扩展，不需要担心。
 *
 * @param   size  该函数返回按指针大小分配的字典对象，如果你不知道需要存储到字典的条目，可以给: size=0;
 *
 * @return  成功:指向创建的map 失败:NULL 
 */
ml_hashmap_t *ml_hashmap_create(int);



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
ml_hashmap_entry_t *ml_hashmap_insert(ml_hashmap_t *map, char *key, uint32_t key_len, void *value);



/**
 * ml_hashmap_find - lookup value
 *
 * @return  找到返回value, 没找到返回NULL
 */
void *ml_hashmap_find(ml_hashmap_t *map, char *key, int key_len);



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
int ml_hashmap_delete(ml_hashmap_t *map, char *key, int key_len);



/**
 * ml_hashmap_free - destroy hash map 
 * 清理hash map
 *
 * @param   map     被清理的hash map
 */
void ml_hashmap_free(ml_hashmap_t *map);



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
void ml_hashmap_walk(ml_hashmap_t *map, void (*action) (ml_hashmap_entry_t *, char *), char *ptr);



/**
 * ml_hashmap_list - list all map members
 * 列表map中所有的entry, 列表map中所有的entry
 *
 * @param   map     被递归遍历的hash map
 *
 * @return  返回map中的entry数组列表，失败返回NULL
 */
ml_hashmap_entry_t **ml_hashmap_list(ml_hashmap_t *map);




#endif
