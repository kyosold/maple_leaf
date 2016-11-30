#ifndef __ML_STRING_H__
#define __ML_STRING_H__


typedef struct {
    char    *s; 
    int     len;    // s已使用的空间大小
    int     size;   // s的空间大小
} ml_str_ctx;


/**
 *  判断 sa 的s是否以 s 起始
 *
 *  @param sa 被比较变量
 *  @param s  比较变量
 *
 *  @return 0:不是已s起始   1:是
 */
int ml_str_starts(ml_str_ctx *sa, char *s);


// ------ Ready Check Memory ------
/**
 *  检查 sa 的s空间是否足够放下 n 个字节，如果没有则扩大;
 *  如果 sa 是空的，则初始化申请一个新的
 *
 *  @param sa 被检查的 sa
 *  @param n  需要的空间长度
 *
 *  @return 0:成功 其它:失败
 */
int ml_str_ready(ml_str_ctx *sa, unsigned int n);

/**
 *  检查 sa 中s剩余的空间是否足够放下 n 个字节，没有则扩大
 *
 *  @param sa 被检查的 sa
 *  @param n  需要的空间长度
 *
 *  @return 0:成功 其它:失败
 */
int ml_str_readyplus(ml_str_ctx *sa, unsigned int n);


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
int ml_str_copyb(ml_str_ctx *sa, char *s, unsigned int n);

/**
 *  拷贝字符串s到sa中。
 *  仅拷贝s中以\0之前的字符到sa
 *
 *  @param sa 被拷贝的sa
 *  @param s  从s中拷贝
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_copys(ml_str_ctx *sa, char *s);

/**
 *  拷贝 sa_src 中的s 到 sa_dest 中的s
 *
 *  @param sa_dest 目标sa
 *  @param sa_src  源sa
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_copy(ml_str_ctx *sa_dest, ml_str_ctx *sa_src);


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
int ml_str_catb(ml_str_ctx *sa, char *s, unsigned int n);

/**
 *  追加 s 到 sa 中，s必须是带有'\0'
 *
 *  @param sa 被追加 sa
 *  @param s  必须带有'\0'
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_cats(ml_str_ctx *sa, char *s);

/**
 *  追加 sa_src 到 sa_dest 中
 *
 *  @param sa_dest 目标sa
 *  @param sa_src  源sa
 *
 *  @return 0:成功 其它:失败 
 */
int ml_str_cat(ml_str_ctx *sa_dest, ml_str_ctx *sa_src);

/**
 *  清理回收 sa 内存
 *
 * @param sa 被回收的sa
 *
 * @return 无
 */
void ml_str_free(ml_str_ctx *sa);

#endif
