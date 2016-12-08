#ifndef __ML_MFILE_H__
#define __ML_MFILE_H__

#include "queue.h"


#define DEFAULT_DATA_BLOCK_SIZE  8888
typedef void *USER_ALLOCER(size_t);
typedef void USER_FREER(void *); 


typedef struct data_block
{
    int data_len;
    char *data;
    int current_write_count;
    int current_read_count;
    TAILQ_ENTRY(data_block) entries;
} DATA_BLOCK;

TAILQ_HEAD(mfile_head, data_block);


/* mfile's handler */
typedef struct mfile
{
    int total_size;
    unsigned int new_header_size;
    struct mfile_head head; /* queue head */
    int block_num; /* data block number */
    DATA_BLOCK *current_write_p;
    DATA_BLOCK *current_read_p;
    int is_full; /* 0: not full, 1:full */
    int is_empty; /* already readed */
    int DATA_BLOCK_SIZE;
    int MAX_BLOCK_NUMBER;
    char ccache;
    USER_ALLOCER *alloc_fun;
    USER_FREER *free_fun;
} MFILE;


/**
 * ml_mopen()
 *
 * @data_block_size:  block size
 * Upon successful completion mopen() return a MFILE pointer.
 * Otherwise, NULL is returned
 */
MFILE *ml_mopen(int data_block_size, USER_ALLOCER *af, USER_FREER *fe);

/**
 * ml_mclose()
 *
 * @handler: handler of savadata
 */
void ml_mclose(MFILE *handler);

/**
 * ml_mwrite()
 *
 * @handler: handler of savadata
 * @data: the data you want save
 * @len: length of data
 *
 * Upon successful completion mwrite() return 1.
 * Otherwise, -1 is returned
 */
int ml_mwrite(MFILE *handler, const char *data, int len);

/**
 * ml_mwrite_head()
 *
 * @handler: handler of savadata
 * @data: the data you want save
 * @len: length of data
 *
 * Upon successful completion mwrite() return 1.
 * Otherwise, -1 is returned
 */
int ml_mwrite_head(MFILE *handler, const char *data, int len);

/**
 * ml_mread()
 *
 * @handler: handler of savadata
 * @data: the data you want read
 * @len: length of data buffer
 *
 * Upon successful completion mread() return size that you readed.
 * in the end, -1 is returned
 */
int ml_mread(MFILE *handler, char *data, int len);


void ml_mseek(MFILE *handler);
void ml_mseek_pos(MFILE *handler, int pos);

/**
 * ml_mgetc()
 *
 * @handler: handler of savadata
 *
 * Upon successful completion mgetc() return char that you readed.
 * in the end, 0 is returned
 */
char ml_mgetc(MFILE *handler);

/**
 * ml_mread_line()
 *
 * @handler: handler of savadata
 * @buf: the data you want read
 * @n: length of data buffer
 *
 * Upon successful completion mread_line() return size that you readed.
 * in the end, 0 is returned
 */
int ml_mread_line(MFILE *handler, char *buf, int n);

/**
 * ml_mwrite_file()
 *
 * @handler: handler of savadata
 *
 * Upon successful completion mwrite_file() the number of bytes
 * which were written is returned.
 * Otherwise, -1 is returned
 */
int ml_mwrite_file(MFILE *handler, int fd);

/**
 * ml_msize()
 * @handler: handler of savadata
 *
 * Upon successful completion msize() the number of bytes
 * which were written is returned.
 * Otherwise, -1 is returned
 */
int ml_msize(MFILE *handler);

unsigned int ml_mfile_new_header_size( MFILE *handler );

int ml_mfile_copy(MFILE* dest, MFILE* src, unsigned int start, unsigned int end);


#endif
