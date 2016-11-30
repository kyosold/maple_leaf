#ifndef __ML_HASH_H__
#define __ML_HASH_H__


#include <stdint.h>


static inline void ml_hash_bin2hex(char *out, const unsigned char *in, int in_len)
{
    static const char hexits[17] = "0123456789abcdef";
    int i;

    for(i = 0; i < in_len; i++) {
        out[i * 2]       = hexits[in[i] >> 4];
        out[(i * 2) + 1] = hexits[in[i] &  0x0F];
    }
}


// SHA1
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
 * @return          0:succ  1:fail
 */
int ml_sha1(char *in_data, size_t in_data_len, unsigned int raw_output, char *out_data, size_t out_data_size);
int ml_sha1_file(char *file_name, unsigned int raw_output, char *out_data, size_t out_data_size);

// SHA512
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
 * @return          0:succ  1:fail
 */
int ml_sha512(char *in_data, size_t in_data_len, unsigned int raw_output, char *out_data, size_t out_data_size);
int ml_sha512_file(char *file_name, unsigned int raw_output, char *out_data, size_t out_data_size);

// MD5
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
 * @return          0:succ  1:fail
 */
int ml_md5(char *in_data, size_t in_data_len, unsigned int raw_output, char *out_data, size_t out_data_size);
int ml_md5_file(char *file_name, unsigned int raw_output, char *out_data, size_t out_data_size);


// CRC32
/*
 * Calculate the sha1 hash of a string
 * @in_data         The input string. 
 * @in_data_len     Length of string
 * @out_data        The output string.
 * @out_data_size   output buffer size (>=9)
 *
 * @return          0:succ  1:fail
 */
int ml_crc32(char *in_data, size_t in_data_len, char *out_data, size_t out_data_size);
int ml_crc32_file(char *file_name, char *out_data, size_t out_data_size);


#endif
