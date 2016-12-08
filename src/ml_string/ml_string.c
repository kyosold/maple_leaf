
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "ml_string.h"



// ------ _Memory Alloc ------
#define ALIGNMENT   16      // XXX: assuming that this alignment is enough
#define SPACE       4096    // must be multiple of ALIGNMENT

typedef union {
    char irrelevant[ALIGNMENT];
    double d;
} aligned;

static aligned realspace[SPACE / ALIGNMENT];
#define space ((char *)realspace)
static unsigned int avail = SPACE;      // multiple of ALIGNMENT; 0<=avail<=SPACE

char *_alloc(unsigned int n)
{
    char *x;
    n = ALIGNMENT + n - (n & (ALIGNMENT - 1));  // XXX: could overflow
    if (n <= avail) {
        avail -= n;
        return space + avail;
    }
    x = (char *)malloc(n);

    return x;
}

void _alloc_free(char *x)
{
    if (x >= space) {
        if (x < space + SPACE) {
            return;     // XXX: assuming that pointers are flat
        }
    }
    free(x);
    x = NULL;
}

// @return 0:succ 1:fail
int _alloc_re(char **x, unsigned int m, unsigned int n)
{
    char *y = _alloc(n);
    if (y == NULL) {
        return 1;
    }
    memcpy(y, *x, m);
    _alloc_free(*x);
    *x = y;

    return 0;
}



/**
 *  判断 sa 中s内容是否以 s 起始
 *
 *  @param sa 被比较变量
 *  @param s  比较变量
 *
 *  @return 0:不是已s起始   1:是
 */
int ml_str_starts(ml_str_ctx *sa, char *s)
{
    int len = strlen(s);
    return ((sa->len >= len) && (strncmp(sa->s, s, len) == 0));
}


// ------ Ready Check Memory ------
/**
 *  检查 sa 的s内存空间是否足够放下 n 个字节，如果没有则扩大;
 *  如果 sa 是空的，则初始化申请一个新的
 *
 *  @param sa 被检查的 sa
 *  @param n  需要的空间长度
 *
 *  @return 0:成功 其它:失败
 */
int ml_str_ready(ml_str_ctx *sa, unsigned int n)
{
    unsigned int i;
    if (sa->s != NULL) {
        i = sa->size;
        if (n > i) {
            sa->size = 30 + n + (n >> 3);
            if (!_alloc_re(&sa->s, i * sizeof(char), sa->size * sizeof(char))) {
                return 0;
            }
            sa->size = i;
            return 1;
        }
        return 0;
    }
    sa->len = 0;
    return !(sa->s = (char *)_alloc((sa->size = n) * sizeof(char)));
}


/**
 *  检查 sa 中s剩余的空间是否足够放下 n 个字节，没有则扩大
 *
 *  @param sa 被检查的 sa
 *  @param n  需要的空间长度
 *
 *  @return 0:成功 其它:失败
 */
int ml_str_readyplus(ml_str_ctx *sa, unsigned int n)
{
    unsigned int i;
    if (sa->s != NULL) {
        i = sa->size;
        n += sa->len;
        if (n > i) {
            sa->size = 30 + n + (n >> 3);
            if (!_alloc_re(&sa->s, i * sizeof(char), sa->size * sizeof(char))) {
                return 0;
            }
            sa->size = i;
            return 1;
        }
        return 0;
    }
    sa->len = 0;
    return !(sa->s = (char *)_alloc((sa->size = n) * sizeof(char)));
}



// ------ String Copy ------
/**
 *  从 s 中拷贝前 n 个字节到 sa 中。
 *  如 sa 空间不足则自动扩展空间后,再拷贝
 *
 *  @param sa 被拷贝的sa
 *  @param s  从s中拷贝
 *  @param n  拷贝前n个字节
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_copyb(ml_str_ctx *sa, char *s, unsigned int n)
{
    if (ml_str_ready(sa, n + 1) != 0) {
        return 1;
    }

    memcpy(sa->s, s, n);
    sa->len = n;
    sa->s[n] = '\0';        // offensive programming

    return 0;
}

/**
 *  拷贝字符串s到sa中。
 *  仅拷贝s中以\0之前的字符到sa
 *
 *  @param sa 被拷贝的sa
 *  @param s  从s中拷贝
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_copys(ml_str_ctx *sa, char *s)
{
    return ml_str_copyb(sa, s, strlen(s));
}

/**
 *  拷贝 sa_src 中的s 到 sa_dest 中的s
 *
 *  @param sa_dest 目标sa
 *  @param sa_src  源sa
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_copy(ml_str_ctx *sa_dest, ml_str_ctx *sa_src)
{
    return ml_str_copyb(sa_dest, sa_src->s, sa_src->len);
}


// ------ String Cat ------
/**
 *  追加字符串s前n个字符到sa中
 *
 *  @param sa 被添加字符的sa
 *  @param s  源字符串s
 *  @param n  追回前n个字符
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_catb(ml_str_ctx *sa, char *s, unsigned int n)
{
    if (!sa->s) {
        return ml_str_copyb(sa, s, n);
    }
    if (ml_str_readyplus(sa, n + 1) != 0) {
        return 1;
    }

    memcpy(sa->s + sa->len, s, n);
    sa->len += n;
    sa->s[sa->len] = '\0';      // offensive programming

    return 0;
}

/**
 *  追加 s 到 sa 中，s必须是带有'\0'
 *
 *  @param sa 被追加 sa
 *  @param s  必须带有'\0'
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_cats(ml_str_ctx *sa, char *s)
{
    return ml_str_catb(sa, s, strlen(s));
}

/**
 *  追加 sa_src 到 sa_dest 中
 *
 *  @param sa_dest 目标sa
 *  @param sa_src  源sa
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_cat(ml_str_ctx *sa_dest, ml_str_ctx *sa_src)
{
    return ml_str_catb(sa_dest, sa_src->s, sa_src->len);
}


// ------ Free ------
/**
 *  清理回收 sa 内存
 *
 * @param sa 被回收的sa
 *
 * @return 无
 */
void ml_str_free(ml_str_ctx *sa)
{
    if (sa && sa->s) {
        _alloc_free(sa->s);
        sa->s = 0;
        sa->len = 0;
        sa->size = 0;
    }
}


// ------ Standard ------
/* {{{ php_charmask
 * Fills a 256-byte bytemask with input. You can specify a range like 'a..z',
 * it needs to be incrementing.
 * Returns: FAILURE/SUCCESS whether the input was correct (i.e. no range errors)
 */
static inline int ml_charmask(unsigned char *input, size_t len, char *mask)
{
    unsigned char *end;
    unsigned char c;
    int result = 0;

    memset(mask, 0, 256);
    for (end = input+len; input < end; input++) {
        c=*input;
        if ((input+3 < end) && input[1] == '.' && input[2] == '.'
                && input[3] >= c) {
            memset(mask+c, 1, input[3] - c + 1);
            input+=3;
        } else if ((input+1 < end) && input[0] == '.' && input[1] == '.') {
            /* Error, try to be as helpful as possible:
               (a range ending/starting with '.' won't be captured here) */
            if (end-len >= input) { /* there was no 'left' char */
                printf("Invalid '..'-range, no character to the left of '..'");
                result = 1;
                continue;
            }
            if (input+2 >= end) { /* there is no 'right' char */
                printf("Invalid '..'-range, no character to the right of '..'");
                result = 1;
                continue;
            }
            if (input[-1] > input[2]) { /* wrong order */
                printf("Invalid '..'-range, '..'-range needs to be incrementing");
                result = 1;
                continue;
            }
            /* FIXME: better error (a..b..c is the only left possibility?) */
            printf("Invalid '..'-range");
            result = 1;
            continue;
        } else {
            mask[c]=1;
        }
    }
    return result;
}
/* }}} */



/**
 * ml_str_trim
 * Strip whitespace (or other characters) from the beginning and end of a string
 *
 * @str         The string that will be trimmed.
 * @what        indicates which chars are to be trimmed. NULL->default (' \t\n\r\v\0')
 * @mode        mode 1: trim left
 *              mode 2 : trim right
 *              mode 3 : trim left and right
 * @out         The trimmed string
 * @out_size    the size of trimmed string  
 *
 * @return  0:succ  1:fail
 */
int ml_str_trim(char *str, char *what, size_t what_len, int mode, char *out, size_t out_size)
{
    const char *c   = str;
    size_t len      = strlen(str);
    register size_t i;
    size_t trimmed  = 0;
    char mask[256];

    if (what) {
        if (what_len == 1) {
            char p = *what;
            if (mode & 1) { 
                for (i = 0; i < len; i++) {
                    if (c[i] == p) { 
                        trimmed++;
                    } else {
                        break;
                    }    
                }    
                len -= trimmed;
                c += trimmed;
            }
            if (mode & 2) { 
                if (len > 0) { 
                    i = len - 1; 
                    do { 
                        if (c[i] == p) { 
                            len--;
                        } else {
                            break;
                        }    
                    } while (i-- != 0);
                }    
            }
        } else {
            ml_charmask((unsigned char*)what, what_len, mask);

            if (mode & 1) {
                for (i = 0; i < len; i++) {
                    if (mask[(unsigned char)c[i]]) {
                        trimmed++;
                    } else {
                        break;
                    }
                }
                len -= trimmed;
                c += trimmed;
            }
            if (mode & 2) {
                if (len > 0) {
                    i = len - 1;
                    do {
                        if (mask[(unsigned char)c[i]]) {
                            len--;
                        } else {
                            break;
                        }
                    } while (i-- != 0);
                }
            }
        }
    } else {
        if (mode & 1) { 
            for (i = 0; i < len; i++) {
                if ((unsigned char)c[i] <= ' ' &&
                    (c[i] == ' ' || c[i] == '\n' || c[i] == '\r' || c[i] == '\t' || c[i] == '\v' || c[i] == '\0')) {        
                    trimmed++;
                } else {
                    break;
                }   
            }   
            len -= trimmed;
            c += trimmed;
        }
        if (mode & 2) {
            if (len > 0) {
                i = len - 1;
                do {
                    if ((unsigned char)c[i] <= ' ' &&
                        (c[i] == ' ' || c[i] == '\n' || c[i] == '\r' || c[i] == '\t' || c[i] == '\v' || c[i] == '\0')) {
                        len--;
                    } else {
                        break;
                    }
                } while (i-- != 0);
            }
        }
    }

    if (out_size < (len + 1)) {
        return 1;
    }

    if (strlen(str) == len) {
        memcpy(out, str, len);
        out[len] = '\0';
    } else {
        memcpy(out, c, len);
        out[len] = '\0';
    }

    return 0;
}


// ------ UTF8 string family ------
static unsigned int ml_utf8_check(const char c)
{
    if ( (c&0x80) == 0 ) {  /* ascii */
        return 1;
    } else if ( (c&0xe0) == 0xc0 ) {
        return 2;
    } else if ( (c&0xf0) == 0xe0 ) {
        return 3;
    } else if ( (c&0xf8) == 0xf0 ) {
        return 4;
    } else if ( (c&0xfc) == 0xf8 ) {
        return 5;
    } else if ( (c&0xfe) == 0xfc ) {
        return 6;
    } else {
        return 0;
    }
}

/**
 * ml_utf8_strlen
 * Get string length
 *
 * @str         The string that will be get length.
 *
 * @return  0:fail  1:length of the string
 */
unsigned int ml_utf8_strlen(const char *str)
{
    if ( NULL == str ) {
        return 0;
    }

    unsigned int ulen = 0;
    unsigned int slen = strlen(str);

    unsigned int i;
    unsigned int tmp;
    for ( i=0; i<slen; /* NULL */ ) {
        tmp = ml_utf8_check( str[i] );
        if ( tmp > 0 && (i+=tmp) <= slen ) {
            ++ulen;
        } else {
            break;
        }
    }

    return ulen;
}


/**
 * ml_utf8_strncpy
 * copies the string pointed to by src, including the '\r', '\n', '\t', 
 * to the buffer pointed to by dest and at most n bytes of src are copied
 *
 * @return  a pointer to the destination string dest
 */
char *ml_utf8_strncpy(char *dest, const char *src, unsigned int max)
{
    if ( NULL == dest || NULL == src || 0 == max ) {
        return dest;
    }

    unsigned int slen = strlen(src);

    char *p = dest;
    unsigned int flag = 1;
    unsigned int tmp;
    unsigned int i;
    unsigned int n; 
    for ( i=0,n=0; i<slen && n<max; /* NULL */ ) {
        if ( src[i] == '\r' || src[i] == '\n' || src[i] == '\t' ) {
            ++i;
            continue;
        }

        if ( src[i] == ' ' ) {
            if ( flag == 0 ) {
                *p++ = src[i];
                n++;
                flag = 1;
            }
            ++i;
            continue;
        }

        tmp = ml_utf8_check( src[i] );
        if ( tmp > 0 && (i+tmp) <= slen ) {
            memcpy( p, src+i, tmp );
            p += tmp;
            i += tmp;
            n++;
            flag = 0;
        } else {
            break;
        }
    }

    *p = '\0';

    return dest;
}


/**
 * ml_utf8_ltrim
 * Strip whitespace (or other characters) from the beginning of a string
 *
 * @return  point to a new string, which Strip whitespace from the begining of a string 
 */
char *ml_utf8_ltrim( char *str )
{
    char utf8_space[] = { -29, -128, -128, 0 }; /* chinese_space, :) */

    while ( *str ) {
        if ( ' ' == *str ) {
            str += 1;
        } else if ( 0 == strncmp(str, utf8_space, 3) ) {
            str += 3;
        } else {
            break;
        }
    }

    return str;
}


