
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// #include "rc4.c"

#include "rc4_bak.c"

char *strstrip(char *s)
{
        size_t size;
        char *end;

        size = strlen(s);

        if (!size)
                return s;

        end = s + size - 1;
        while (end >= s && isspace(*end))
                end--;
        *(end + 1) = '\0';

        while (*s && isspace(*s))
                s++;

        return s;
}

int main()
{
    char *plaintext = "This is my message";

    char *key = "yellowsubmarine";

    unsigned char *ciphertext = malloc(sizeof(int) * strlen(plaintext));

    for (size_t i = 0, len = strlen(plaintext); i < len; i++) {
        printf("%02hhX", plaintext[i]);
        //printf("%c", plaintext[i]);
    }
    printf("\n");

    // encrypt
    RC4(key, plaintext, ciphertext);
    for (size_t i = 0, len = strlen(plaintext); i < len; i++) {
        printf("%02hhX", ciphertext[i]);
        //printf("%c", ciphertext[i]);
    }
    printf("\n");

    // decrypt
    unsigned char *test;
    RC4(key, ciphertext, test);
    test = strstrip(test);

    for (size_t i = 0, len = strlen(test); i < len; i++) {
        printf("%02hhX", test[i]);
        //printf("%c", test[i]);
    }

    return 0;
}