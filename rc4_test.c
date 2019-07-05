
#include <stdio.h>
#include <string.h>

#include "rc4.c"

int main()
{
    char *plaintext = "This is my message";
    char *key = "thisisatestkey";

    unsigned char *ciphertext = malloc(sizeof(int) * strlen(plaintext));

    RC4(key, plaintext, ciphertext);

    for (size_t i = 0, len = strlen(plaintext); i < len; i++)
        printf("%02hhX", ciphertext[i]);

    return 0;
}