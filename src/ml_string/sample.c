#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "ml_string.h"

int main(int argc, char **argv)
{
    ml_str_ctx str = {0};
    int ret = 0;
    
    ret = ml_str_copys(&str, " Greeting: ");
    printf("Check [ml_str_copys]:[%d]%s\n", ret, str.s);

    ret = ml_str_cats(&str, argv[1]);
    printf("Check [ml_str_cats]:[%d]%s\n", ret, str.s);

    //printf("%s\n", str.s);

    ml_str_ctx str2 = {0};
    ml_str_ready(&str2, str.len + 1);
    ret = ml_str_trim(str.s, NULL, 0, 1, str2.s, str2.size);
    printf("Check [ml_str_trim]:[%d][%d]%s  # cut left space\n", ret, str2.len, str2.s);

    ml_str_ctx str3 = {0};
    ml_str_ready(&str3, str.len + 1);
    ret = ml_str_trim(str2.s, "@qq.com", 7, 2, str3.s, str3.size);
    printf("Check [ml_str_trim]:[%d][%d]%s  # cut right @qq.com\n", ret, str3.len, str3.s);

    ml_str_free(&str);
    ml_str_free(&str2);
    ml_str_free(&str3);

    // test utf8 family
    printf("\nCheck [ml_utf8...]\n");
    char *in = "hello, 你好,谢谢";
    unsigned int n = 9;
    char out[20] = {0};
    char *p_dest = NULL;

    p_dest = ml_utf8_strncpy(out, ml_utf8_ltrim(in), n);
    if (*p_dest != '\0' && *out != '\0') {
        printf("in: [%d]%s\n", ml_utf8_strlen(in), in);
        printf("out:[%d]%s\n", ml_utf8_strlen(out), out);
    }


    return 0;
}

