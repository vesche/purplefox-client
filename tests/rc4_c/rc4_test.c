#include <stdio.h>
#include <string.h>
#include "rc4.c"

int
main()
{
    unsigned char *user_key = "yellowsubmarine";
    struct rc4_key *key;

    unsigned char *message = "thisismymessage";
    unsigned char *out;

    // encrypt
    memset(user_key, 0, sizeof(user_key));
    prepare_key(user_key, sizeof(user_key), &key);
    memcpy(out, message, sizeof(message));
    rc4(out, sizeof(message), &key);

    // decrypt

    printf("original: %s", message);
    printf("encrypt: %s", out);

    return 0;
}