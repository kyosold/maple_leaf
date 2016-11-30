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



