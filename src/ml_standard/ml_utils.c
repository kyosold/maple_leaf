#include <stdio.h>
#include <stdlib.h>


static char hexconvtab[] = "0123456789abcdef";

char* ml_bin2hex(const unsigned char *indata, const size_t indata_len)
{
    char *result = (char*) malloc(indata_len * 2 + 1);
    size_t i, j;

    for (i = j = 0; i < indata_len; i++) {
        result[j++] = hexconvtab[indata[i] >> 4];
        result[j++] = hexconvtab[indata[i] & 15];
    }
    result[j] = '\0';
    return result;
}

char *ml_hex2bin(const unsigned char *indata, const size_t indata_len)
{
    size_t target_length = indata_len >> 1;
    char *str = (char *) malloc(target_length);
    unsigned char *ret = str;
    size_t i, j;

    for (i = j = 0; i < target_length; i++) {
        unsigned char c = indata[j++];
        unsigned char d;

        if (c >= '0' && c <= '9') {
            d = (c - '0') << 4;
        } else if (c >= 'a' && c <= 'f') {
            d = (c - 'a' + 10) << 4;
        } else if (c >= 'A' && c <= 'F') {
            d = (c - 'A' + 10) << 4;
        } else {
            free(str);
            return NULL;
        }
        c = indata[j++];
        if (c >= '0' && c <= '9') {
            d |= c - '0';
        } else if (c >= 'a' && c <= 'f') {
            d |= c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            d |= c - 'A' + 10;
        } else {
            free(str);
            return NULL;
        }
        ret[i] = d;
    }
    ret[i] = '\0';

    return str;
}


