#ifndef __HASH_SHA_H__
#define __HASH_SHA_H__

#include <stdint.h>

#define L64 INT64_C

/* SHA1 context. */
typedef struct {
    uint32_t state[5];       /* state (ABCD) */
    uint32_t count[2];       /* number of bits, modulo 2^64 */
    unsigned char buffer[64];   /* input buffer */
} ml_sha1_ctx;

void ml_sha1_init(ml_sha1_ctx * context);
void ml_sha1_update(ml_sha1_ctx * context, const unsigned char *input, unsigned int inputLen);
void ml_sha1_final(unsigned char digest[20], ml_sha1_ctx *context);

/* SHA224 context. */
typedef struct {
    uint32_t state[8];       /* state */
    uint32_t count[2];       /* number of bits, modulo 2^64 */
    unsigned char buffer[64];   /* input buffer */
} ml_sha224_ctx;

void ml_sha224_init(ml_sha224_ctx *); 
void ml_sha224_update(ml_sha224_ctx *, const unsigned char *, unsigned int);
void ml_sha224_final(unsigned char[28], ml_sha224_ctx *); 

/* SHA256 context. */
typedef struct {
    uint32_t state[8];       /* state */
    uint32_t count[2];       /* number of bits, modulo 2^64 */
    unsigned char buffer[64];   /* input buffer */
} ml_sha256_ctx;

void ml_sha256_init(ml_sha256_ctx *); 
void ml_sha256_update(ml_sha256_ctx *, const unsigned char *, unsigned int);
void ml_sha256_final(unsigned char[32], ml_sha256_ctx *); 

/* SHA384 context */
typedef struct {
    uint64_t state[8];   /* state */
    uint64_t count[2];   /* number of bits, modulo 2^128 */
    unsigned char buffer[128];  /* input buffer */
} ml_sha384_ctx;

void ml_sha384_init(ml_sha384_ctx *);
void ml_sha384_update(ml_sha384_ctx *, const unsigned char *, unsigned int);
void ml_sha384_final(unsigned char[48], ml_sha384_ctx *);

/* SHA512 context */
typedef struct {
    uint64_t state[8];   /* state */
    uint64_t count[2];   /* number of bits, modulo 2^128 */
    unsigned char buffer[128];  /* input buffer */
} ml_sha512_ctx;

void ml_sha512_init(ml_sha512_ctx *);
void ml_sha512_update(ml_sha512_ctx *, const unsigned char *, unsigned int);
void ml_sha512_final(unsigned char[64], ml_sha512_ctx *);



#endif
