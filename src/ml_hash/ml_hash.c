#include <stdio.h>
#include <string.h>
#include "hash_sha.h"
#include "hash_md.h"
#include "hash_crc32.h"


/*
 * Calculate the sha1 hash of a string
 * @in_data         The input string. 
 * @in_data_len     Length of string
 * @raw_output      If the optional raw_output is set to 1, 
 *                  then the sha1 digest is instead returned 
 *                  in raw binary format with a length of 20,
 *                  otherwise the returned value is a 40-character 
 *                  hexadecimal number.
 * @out_data        The output string.
 * @out_data_size   output buffer size (>=41)
 *
 * @return 0:succ 1:fail
 */
int ml_sha1(char *in_data, size_t in_data_len, unsigned int raw_output, char *out_data, size_t out_data_size)
{
    // sha1
    char            sha1str[41];
    ml_sha1_ctx     context;
    unsigned char   digest[20];

    sha1str[0] = '\0';
    ml_sha1_init(&context);
    ml_sha1_update(&context, in_data, in_data_len);
    ml_sha1_final(digest, &context);
    if (raw_output) {
        if (out_data_size < 20) {
            return 1;
        }
        memcpy(out_data, digest, 20);
    } else {
        if (out_data_size < 41) {
            return 1;
        }
        make_sha1_digest(sha1str, digest);
        memcpy(out_data, sha1str, sizeof(sha1str));
    }

    return 0;
}


/*
 * @return 0:succ   other:fail
 *                  1: open file name fail
 *                  2: fread file fail
 */
int ml_sha1_file(char *file_name, unsigned int raw_output, char *out_data, size_t out_data_size)
{
    char            sha1str[41];
    unsigned char   buf[1024];
    unsigned char   digest[20];
    ml_sha1_ctx     context;
    int             nr;
    
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL) {
        // open file name fail
        return 1;
    }
    
    sha1str[0] = '\0';
    ml_sha1_init(&context);

    while (1) {
        nr = fread(buf, 1, sizeof(buf), fp);
        if (nr == 0) {
            if (ferror(fp)) {
                return 2;
            }
            break;
        } 

        ml_sha1_update(&context, buf, nr);
    }

    ml_sha1_final(digest, &context);

    fclose(fp);

    if (nr < 0) {
        return 2;
    }

    if (raw_output) {
        if (out_data_size < 20) {
            return 1;
        }
        memcpy(out_data, digest, 20);
    } else {
        if (out_data_size < 41) {
            return 1;
        }
        make_sha1_digest(sha1str, digest);
        memcpy(out_data, sha1str, sizeof(sha1str));
    }

    return 0;
}


/*
 * Calculate the sha512 hash of a string
 * @in_data         The input string. 
 * @in_data_len     Length of string
 * @raw_output      If the optional raw_output is set to 1, 
 *                  then the sha1 digest is instead returned 
 *                  in raw binary format with a length of 20,
 *                  otherwise the returned value is a 40-character 
 *                  hexadecimal number.
 * @out_data        The output string.
 * @out_data_size   output buffer size (>=129)
 *
 * @return 0:succ 1:fail
 */
int ml_sha512(char *in_data, size_t in_data_len, unsigned int raw_output, char *out_data, size_t out_data_size)
{
    // sha512
    char            sha512str[129];
    ml_sha512_ctx     context;
    unsigned char   digest[64];

    sha512str[0] = '\0';
    ml_sha512_init(&context);
    ml_sha512_update(&context, in_data, in_data_len);
    ml_sha512_final(digest, &context);
    if (raw_output) {
        if (out_data_size < 64) {
            return 1;
        }
        memcpy(out_data, digest, 64);
    } else {
        if (out_data_size < 129) {
            return 1;
        }
        make_sha512_digest(sha512str, digest);
        memcpy(out_data, sha512str, sizeof(sha512str));
    }

    return 0;
}


int ml_sha512_file(char *file_name, unsigned int raw_output, char *out_data, size_t out_data_size)
{
    char            sha512str[129];
    unsigned char   buf[1024];
    unsigned char   digest[64];
    ml_sha512_ctx     context;
    int             nr;
    
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL) {
        // open file name fail
        return 1;
    }
    
    sha512str[0] = '\0';
    ml_sha512_init(&context);

    while (1) {
        nr = fread(buf, 1, sizeof(buf), fp);
        if (nr == 0) {
            if (ferror(fp)) {
                return 2;
            }
            break;
        } 

        ml_sha512_update(&context, buf, nr);
    }

    ml_sha512_final(digest, &context);

    fclose(fp);

    if (nr < 0) {
        return 2;
    }

    if (raw_output) {
        if (out_data_size < 64) {
            return 1;
        }
        memcpy(out_data, digest, 64);
    } else {
        if (out_data_size < 129) {
            return 1;
        }
        make_sha512_digest(sha512str, digest);
        memcpy(out_data, sha512str, sizeof(sha512str));
    }

    return 0;
}


/*
 * Calculate the md5 hash of a string
 * @in_data         The input string. 
 * @in_data_len     Length of string
 * @raw_output      If the optional raw_output is set to 1, 
 *                  then the sha1 digest is instead returned 
 *                  in raw binary format with a length of 20,
 *                  otherwise the returned value is a 40-character 
 *                  hexadecimal number.
 * @out_data        The output string.
 * @out_data_size   output buffer size (>=33)
 *
 * @return 0:succ 1:fail
 */
int ml_md5(char *in_data, size_t in_data_len, unsigned int raw_output, char *out_data, size_t out_data_size)
{
    char            md5str[33];
    ml_md5_ctx      context;
    unsigned char   digest[16];

    md5str[0] = '\0';
    ml_md5_init(&context);
    ml_md5_update(&context, in_data, in_data_len);
    ml_md5_final(digest, &context);

    if (raw_output) {
        if (out_data_size < 16) {
            return 1;
        }
        memcpy(out_data, digest, 16);
    } else {
        if (out_data_size < 33) {
            return 1;
        }
        make_digest(md5str, digest);
        memcpy(out_data, md5str, sizeof(md5str));
    }

    return 0;
}


int ml_md5_file(char *file_name, unsigned int raw_output, char *out_data, size_t out_data_size)
{
    char            md5str[33];
    unsigned char   buf[1024];
    unsigned char   digest[16];
    ml_md5_ctx     context;
    int             nr;
    
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL) {
        // open file name fail
        return 1;
    }
    
    md5str[0] = '\0';
    ml_md5_init(&context);

    while (1) {
        nr = fread(buf, 1, sizeof(buf), fp);
        if (nr == 0) {
            if (ferror(fp)) {
                return 2;
            }
            break;
        } 

        ml_md5_update(&context, buf, nr);
    }

    ml_md5_final(digest, &context);

    fclose(fp);

    if (nr < 0) {
        return 2;
    }

    if (raw_output) {
        if (out_data_size < 16) {
            return 1;
        }
        memcpy(out_data, digest, 16);
    } else {
        if (out_data_size < 33) {
            return 1;
        }
        make_digest(md5str, digest);
        memcpy(out_data, md5str, sizeof(md5str));
    }

    return 0;
}


int ml_crc32(char *in_data, size_t in_data_len, char *out_data, size_t out_data_size)
{
    char            crc32str[9];
    ml_crc32_ctx      context;
    unsigned char   digest[4];

    crc32str[0] = '\0';
    ml_crc32_init(&context);
    ml_crc32_bupdate(&context, in_data, in_data_len);
    ml_crc32_bfinal(digest, &context);

    make_crc32_digest(crc32str, digest);
    memcpy(out_data, crc32str, sizeof(crc32str));
    return 0;

}

int ml_crc32_file(char *file_name, char *out_data, size_t out_data_size)
{
    char            crc32str[9];
    unsigned char   buf[1024];
    unsigned char   digest[4];
    ml_crc32_ctx     context;
    int             nr;
    
    FILE *fp = fopen(file_name, "rb");
    if (fp == NULL) {
        // open file name fail
        return 1;
    }
    
    crc32str[0] = '\0';
    ml_crc32_init(&context);

    while (1) {
        nr = fread(buf, 1, sizeof(buf), fp);
        if (nr == 0) {
            if (ferror(fp)) {
                return 2;
            }
            break;
        } 

        ml_crc32_bupdate(&context, buf, nr);
    }

    ml_crc32_bfinal(digest, &context);

    fclose(fp);

    if (nr < 0) {
        return 2;
    }

    make_crc32_digest(crc32str, digest);
    memcpy(out_data, crc32str, sizeof(crc32str));

    return 0;
    /*if (raw_output) {
        if (out_data_size < 16) {
            return 1;
        }
        memcpy(out_data, digest, 16);
    } else {
        if (out_data_size < 33) {
            return 1;
        }
        make_digest(md5str, digest);
        memcpy(out_data, md5str, sizeof(md5str));
    }

    return 0;*/
}



// A Simple Hash
unsigned int ml_simple_hash(char *str)
{
    register unsigned int hash;
    register unsigned char *p; 

    for (hash = 0, p = (unsigned char *)str; *p; p++) {
        hash = 31 * hash + *p; 
    }   

    return (hash & 0x7FFFFFFF);
}

// SDBM Hash
unsigned int ml_sdbm_hash(char *str)
{
    unsigned int hash = 0;

    while (*str) {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

// RS Hash
unsigned int ml_rs_hash(char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str) {
        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash & 0x7FFFFFFF);
}

// JS Hash
unsigned int ml_js_hash(char *str)
{
    unsigned int hash = 1315423911;

    while (*str) {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash
unsigned int ml_pjw_hash(char *str)
{
    unsigned int bits_in_unsigned_int   = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int three_quarters         = (unsigned int)((bits_in_unsigned_int * 3) / 4);
    unsigned int one_eighth             = (unsigned int)(three_quarters / 8);
    unsigned int high_bits              = (unsigned int)(0xFFFFFFFF) << (bits_in_unsigned_int - one_eighth);
    unsigned int hash                   = 0;
    unsigned int test                   = 0;

    while (*str) {
        hash = (hash << one_eighth) + (*str++);
        if ((test = hash & high_bits) != 0) {
            hash = ((hash ^ (test >> three_quarters)) & (~high_bits));
        }
    }

    return (hash & 0x7FFFFFFF);
}

// ELF Hash
unsigned int ml_elf_hash(char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;

    while (*str) {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }

    return (hash & 0x7FFFFFFF);
}

// BKDR Hash
unsigned int ml_bkdr_hash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str) {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// DJB Hash
unsigned int ml_djb_hash(char *str)
{
    unsigned int hash = 5381;

    while (*str) {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF);
}

// AP Hash
unsigned int ml_ap_hash(char *str)
{
    unsigned int hash = 0;
    int i;

    for (i=0; *str; i++) {
        if ((i & 1) == 0) {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        } else {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF);
}


