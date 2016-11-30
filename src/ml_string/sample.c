#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "ml_string.h"

int main(int argc, char **argv)
{
    ml_str_ctx str = {0};
    int ret = 0;
    
    ret = ml_str_copys(&str, "Greeting: ");
    printf("Check [ml_str_copys]:[%d]%s\n", ret, str.s);

    ret = ml_str_cats(&str, argv[1]);
    printf("Check [ml_str_cats]:[%d]%s\n", ret, str.s);

    printf("%s\n", str.s);

    ml_str_free(&str);

    return 0;
}

