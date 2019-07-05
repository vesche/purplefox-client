
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "rc4.c"
#include "rc4.h"

int main()
{
    rc4_ctx ctx;
    uint8 dst[512];

    char *key = "thisisatestkey";
    uint32 key_len = strlen(key);

    char *pt = "This is my message!";
    uint32 msg_len = strlen(pt);

    rc4_ks(&ctx, key, key_len);

    rc4_encrypt(&ctx, pt, dst, msg_len);
    for (int i=0; i<512; i++)
        printf("%d", dst[i]);
    
    printf("\n");

    uint8 new_dst[512];
    rc4_decrypt(&ctx, dst, new_dst, msg_len);
    for (int i=0; i<512; i++) {
        //printf("%X", dst[i]);
        //printf("%c", (char) dst[i]);
        char tmp = '0' + new_dst[i];
        printf("%c", tmp);
    }

    return 0;
}