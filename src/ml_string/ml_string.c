
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

