#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ml_standard.h"

const char tstr[] = "OK, if we're playing cute dog pix, here's a couple of best buds. BTW we worked at Time at the same time. Keep up the good work";

int main(int argc, char **argv)
{
    
    char    *bstr = NULL;

    // TEST base64
    printf("=== TEST base64 ===\n");
    bstr = ml_base64_encode(tstr, strlen(tstr));
    printf("base64 encode:[%d]%s\n", strlen(bstr), bstr);

    bstr = ml_base64_decode(bstr, strlen(bstr));
    printf("base64 decode:[%d]%s\n", strlen(bstr), bstr);
    
    if (bstr) {
        free(bstr);
        bstr = NULL;
    }   

    // TEST bin2hex
    printf("\n=== TEST bin2hex ===\n");
    char binstr[] = "11111001";
    bstr = ml_bin2hex(binstr, strlen(binstr));
    printf("bin2hex:%s\n", bstr);
    free(bstr);

    // TEST hex2bin
    printf("\n=== TEST hex2bin ===\n");
    char str[] = "6578616d706c65206865782064617461";
    bstr = ml_hex2bin(str, strlen(str));
    printf("hex2bin:%s\n", bstr);

    free(bstr);

    return 0;
}
