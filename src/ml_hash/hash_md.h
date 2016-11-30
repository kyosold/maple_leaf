#ifndef __HASH_MD_H__
#define __HASH_MD_H__

#include <stdint.h>



/* MD5 context. */
typedef struct {
    uint32_t state[4];               /* state (ABCD) */
    uint32_t count[2];               /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];   /* input buffer */
} ml_md5_ctx;

void make_digest(char *md5str, unsigned char *digest);
void ml_md5_init(ml_md5_ctx *);
void ml_md5_update(ml_md5_ctx *, const unsigned char *, unsigned int);
void ml_md5_final(unsigned char[16], ml_md5_ctx *);


/* MD4 context */
typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    unsigned char buffer[64];
} ml_md4_ctx;

void ml_md4_init(ml_md4_ctx *);
void ml_md4_update(ml_md4_ctx *context, const unsigned char *, unsigned int);
void ml_md4_final(unsigned char[16], ml_md4_ctx *);

/* MD2 context */
typedef struct {
    unsigned char state[48];
    unsigned char checksum[16];
    unsigned char buffer[16];
    char in_buffer;
} ml_md2_ctx;

void ml_md2_init(ml_md2_ctx *context);
void ml_md2_update(ml_md2_ctx *context, const unsigned char *, unsigned int);
void ml_md2_final(unsigned char[16], ml_md2_ctx *);



#endif
