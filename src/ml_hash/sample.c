
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "ml_hash.h"

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("%s [sha1|sha512|md5|crc32] [-f|-s] [string|path]\n", argv[0]);
        return 1;
    }

    char *alog = argv[1];
    char *type = argv[2];
    char *str = argv[3];

    // sha1
    int ret = 0;

    if (strcasecmp(alog, "SHA1") == 0) {
        char sha1str[41];
        if (type[0] == '-' && type[1] == 'f') {
            ret = ml_sha1_file(str, 0, sha1str, sizeof(sha1str));
        } else {
            ret = ml_sha1(str, strlen(str), 0, sha1str, sizeof(sha1str));
        }
        printf("%s hash:%s %s\n", alog, sha1str, (ret == 1) ? "fail" : "succ");

    } else if (strcasecmp(alog, "SHA512") == 0) {
        char sha512str[129];
        if (type[0] == '-' && type[1] == 'f') {
            ret = ml_sha512_file(str, 0, sha512str, sizeof(sha512str));
        } else {
            ret = ml_sha512(str, strlen(str), 0, sha512str, sizeof(sha512str));
        }
        printf("%s hash:%s %s\n", alog, sha512str, (ret == 1) ? "fail" : "succ");

    } else if (strcasecmp(alog, "MD5") == 0) {
        char md5str[33];
        if (type[0] == '-' && type[1] == 'f') {
            ret = ml_md5_file(str, 0, md5str, sizeof(md5str));
        } else {
            ret = ml_md5(str, strlen(str), 0, md5str, sizeof(md5str));
        }
        printf("%s hash:%s %s\n", alog, md5str, (ret == 1) ? "fail" : "succ");

    } else if (strcasecmp(alog, "CRC32") == 0) {
        char crc32str[4];
        if (type[0] == '-' && type[1] == 'f') {
            ret = ml_crc32_file(str, crc32str, sizeof(crc32str));
        } else {
            ret = ml_crc32(str, strlen(str), crc32str, sizeof(crc32str));
        }
        printf("%s hash:%s %s\n", alog, crc32str, (ret == 1) ? "fail" : "succ");
    }

    return 0;
}

