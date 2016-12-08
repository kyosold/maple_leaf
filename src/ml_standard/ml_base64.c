#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* {{{ base64 tables */
static const char base64_table[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', '\0'
};

static const char base64_pad = '=';

static const short base64_reverse_table[256] = {
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -1, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 62, -2, -2, -2, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -2, -2, -2, -2, -2, -2,
    -2,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -2, -2, -2, -2, -2,
    -2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2
};
/* }}} */


char *ml_base64_encode_alloc(const unsigned char *str, size_t length)
{
    const unsigned char *current = str;
    unsigned char *p;
    char *result;
    size_t result_size = ((length + 2) / 3) * 4 * sizeof(char) + 1;

    result = (char *)malloc(result_size);
    if (result == NULL) {
        return NULL;
    }
    p = (char *)result;

    while (length > 2) { /* keep going until we have less than 24 bits */
        *p++ = base64_table[current[0] >> 2];
        *p++ = base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
        *p++ = base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
        *p++ = base64_table[current[2] & 0x3f];

        current += 3;
        length -= 3; /* we just handle 3 octets of data */
    }

    /* now deal with the tail end of things */
    if (length != 0) {
        *p++ = base64_table[current[0] >> 2];
        if (length > 1) {
            *p++ = base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
            *p++ = base64_table[(current[1] & 0x0f) << 2];
            *p++ = base64_pad;
        } else {
            *p++ = base64_table[(current[0] & 0x03) << 4];
            *p++ = base64_pad;
            *p++ = base64_pad;
        }
    }
    *p = '\0';

    //result_len = (char *)(p - (unsigned char *)result);

    return result;
}



char *ml_base64_decode_ex(const unsigned char *str, size_t length, int strict)
{
    const unsigned char *current = str;
    int ch, i = 0, j = 0, k;
    /* this sucks for threaded environments */
    char *result;
    size_t result_size = length + 1;

    result = (char *)malloc(length);

    /* run through the whole string, converting as we go */
    while ((ch = *current++) != '\0' && length-- > 0) {
        if (ch == base64_pad) {
            if (*current != '=' && ((i % 4) == 1 || (strict && length > 0))) {
                if ((i % 4) != 1) {
                    while (isspace(*(++current))) {
                        continue;
                    }
                    if (*current == '\0') {
                        continue;
                    }
                }
                free(result);
                return NULL;
            }
            continue;
        }

        ch = base64_reverse_table[ch];
        if ((!strict && ch < 0) || ch == -1) { /* a space or some other separator character, we simply skip over */
            continue;
        } else if (ch == -2) {
            free(result);
            return NULL;
        }

        switch(i % 4) {
        case 0:
            result[j] = ch << 2;
            break;
        case 1:
            result[j++] |= ch >> 4;
            result[j] = (ch & 0x0f) << 4;
            break;
        case 2:
            result[j++] |= ch >>2;
            result[j] = (ch & 0x03) << 6;
            break;
        case 3:
            result[j++] |= ch;
            break;
        }
        i++;
    }

    k = j;
    /* mop things up if we ended on a boundary */
    if (ch == base64_pad) {
        switch(i % 4) {
        case 1:
            free(result);
            return NULL;
        case 2:
            k++;
        case 3:
            result[k] = 0;
        }
    }
    //ZSTR_LEN(result) = j;
    int result_len = j;
    result[result_len] = '\0';

    return result;
}


char *ml_base64_decode_alloc(const unsigned char *str, size_t length)
{
    return ml_base64_decode_ex(str, length, 0);
}





/*int main(int argc, char **argv)
{
    char    *type = argv[1];
    char    *str = argv[2];
    char    *bstr = NULL;

    if (strcasecmp(type, "enc") == 0) {
        bstr = ml_base64_encode((unsigned char *)str, strlen(str));
    } else {
        bstr = ml_base64_decode((unsigned char *)str, strlen(str));
    }
    printf("[%d]%s\n", strlen(bstr), bstr);

    if (bstr) {
        free(bstr);
        bstr = NULL;
    }

    return 0;
}*/

