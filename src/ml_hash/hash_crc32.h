#ifndef __HASH_CRC32_H__
#define __HASH_CRC32_H__

#include <stdint.h>



/* CRC32 context. */
typedef struct {
    uint32_t state;
} ml_crc32_ctx;

void ml_crc32_init(ml_crc32_ctx *context);
void ml_crc32_update(ml_crc32_ctx *context, const unsigned char *input, size_t len);
void ml_crc32_bupdate(ml_crc32_ctx *context, const unsigned char *input, size_t len);
void ml_crc32_final(unsigned char digest[4], ml_crc32_ctx *context);

void make_crc32_digest(char *crc32str, unsigned char *digest);



#endif
