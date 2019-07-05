#ifdef TEST_VECTORS
/*
 * Test vectors from K. Kaukonen and R. Thayer (SSH) Internet Draft
 * for Arcfour algorithm
 */

/* Test vectors from [CRYPTLIB] */

static const uint8  pt1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8 key1[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
static const uint8  ct1[8] = {0x74, 0x94, 0xc2, 0xe7, 0x10, 0x4b, 0x08, 0x79};

/* Test vectors from [COMMERCE] */

static const uint8  pt2[5] =  {0xdc, 0xee, 0x4c, 0xf9, 0x2c};
static const uint8 key2[5] =  {0x61, 0x8a, 0x63, 0xd2, 0xfb};
static const uint8  ct2[5] =  {0xf1, 0x38, 0x29, 0xc9, 0xde};

/* Test vectors from [SSH ARCFOUR] */

static const uint8 pt3[309] ={
    0x52, 0x75, 0x69, 0x73, 0x6c, 0x69, 0x6e, 0x6e, 0x75, 0x6e, 0x20, 0x6c,
    0x61, 0x75, 0x6c, 0x75, 0x20, 0x6b, 0x6f, 0x72, 0x76, 0x69, 0x73, 0x73,
    0x73, 0x61, 0x6e, 0x69, 0x2c, 0x20, 0x74, 0xe4, 0x68, 0x6b, 0xe4, 0x70,
    0xe4, 0x69, 0x64, 0x65, 0x6e, 0x20, 0x70, 0xe4, 0xe4, 0x6c, 0x6c, 0xe4,
    0x20, 0x74, 0xe4, 0x79, 0x73, 0x69, 0x6b, 0x75, 0x75, 0x2e, 0x20, 0x4b,
    0x65, 0x73, 0xe4, 0x79, 0xf6, 0x6e, 0x20, 0x6f, 0x6e, 0x20, 0x6f, 0x6e,
    0x6e, 0x69, 0x20, 0x6f, 0x6d, 0x61, 0x6e, 0x61, 0x6e, 0x69, 0x2c, 0x20,
    0x6b, 0x61, 0x73, 0x6b, 0x69, 0x73, 0x61, 0x76, 0x75, 0x75, 0x6e, 0x20,
    0x6c, 0x61, 0x61, 0x6b, 0x73, 0x6f, 0x74, 0x20, 0x76, 0x65, 0x72, 0x68,
    0x6f, 0x75, 0x75, 0x2e, 0x20, 0x45, 0x6e, 0x20, 0x6d, 0x61, 0x20, 0x69,
    0x6c, 0x6f, 0x69, 0x74, 0x73, 0x65, 0x2c, 0x20, 0x73, 0x75, 0x72, 0x65,
    0x20, 0x68, 0x75, 0x6f, 0x6b, 0x61, 0x61, 0x2c, 0x20, 0x6d, 0x75, 0x74,
    0x74, 0x61, 0x20, 0x6d, 0x65, 0x74, 0x73, 0xe4, 0x6e, 0x20, 0x74, 0x75,
    0x6d, 0x6d, 0x75, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x6c, 0x6c, 0x65, 0x20,
    0x74, 0x75, 0x6f, 0x6b, 0x61, 0x61, 0x2e, 0x20, 0x50, 0x75, 0x75, 0x6e,
    0x74, 0x6f, 0x20, 0x70, 0x69, 0x6c, 0x76, 0x65, 0x6e, 0x2c, 0x20, 0x6d,
    0x69, 0x20, 0x68, 0x75, 0x6b, 0x6b, 0x75, 0x75, 0x2c, 0x20, 0x73, 0x69,
    0x69, 0x6e, 0x74, 0x6f, 0x20, 0x76, 0x61, 0x72, 0x61, 0x6e, 0x20, 0x74,
    0x75, 0x75, 0x6c, 0x69, 0x73, 0x65, 0x6e, 0x2c, 0x20, 0x6d, 0x69, 0x20,
    0x6e, 0x75, 0x6b, 0x6b, 0x75, 0x75, 0x2e, 0x20, 0x54, 0x75, 0x6f, 0x6b,
    0x73, 0x75, 0x74, 0x20, 0x76, 0x61, 0x6e, 0x61, 0x6d, 0x6f, 0x6e, 0x20,
    0x6a, 0x61, 0x20, 0x76, 0x61, 0x72, 0x6a, 0x6f, 0x74, 0x20, 0x76, 0x65,
    0x65, 0x6e, 0x2c, 0x20, 0x6e, 0x69, 0x69, 0x73, 0x74, 0xe4, 0x20, 0x73,
    0x79, 0x64, 0xe4, 0x6d, 0x65, 0x6e, 0x69, 0x20, 0x6c, 0x61, 0x75, 0x6c,
    0x75, 0x6e, 0x20, 0x74, 0x65, 0x65, 0x6e, 0x2e, 0x20, 0x2d, 0x20, 0x45,
    0x69, 0x6e, 0x6f, 0x20, 0x4c, 0x65, 0x69, 0x6e, 0x6f};

static const uint8 key3[16] = {
    0x29, 0x04, 0x19, 0x72, 0xfb, 0x42, 0xba, 0x5f,
    0xc7, 0x12, 0x77, 0x12, 0xf1, 0x38, 0x29, 0xc9};

static const uint8 ct3[309] = {
    0x35, 0x81, 0x86, 0x99, 0x90, 0x01, 0xe6, 0xb5, 0xda, 0xf0, 0x5e, 0xce,
    0xeb, 0x7e, 0xee, 0x21, 0xe0, 0x68, 0x9c, 0x1f, 0x00, 0xee, 0xa8, 0x1f,
    0x7d, 0xd2, 0xca, 0xae, 0xe1, 0xd2, 0x76, 0x3e, 0x68, 0xaf, 0x0e, 0xad,
    0x33, 0xd6, 0x6c, 0x26, 0x8b, 0xc9, 0x46, 0xc4, 0x84, 0xfb, 0xe9, 0x4c,
    0x5f, 0x5e, 0x0b, 0x86, 0xa5, 0x92, 0x79, 0xe4, 0xf8, 0x24, 0xe7, 0xa6,
    0x40, 0xbd, 0x22, 0x32, 0x10, 0xb0, 0xa6, 0x11, 0x60, 0xb7, 0xbc, 0xe9,
    0x86, 0xea, 0x65, 0x68, 0x80, 0x03, 0x59, 0x6b, 0x63, 0x0a, 0x6b, 0x90,
    0xf8, 0xe0, 0xca, 0xf6, 0x91, 0x2a, 0x98, 0xeb, 0x87, 0x21, 0x76, 0xe8,
    0x3c, 0x20, 0x2c, 0xaa, 0x64, 0x16, 0x6d, 0x2c, 0xce, 0x57, 0xff, 0x1b,
    0xca, 0x57, 0xb2, 0x13, 0xf0, 0xed, 0x1a, 0xa7, 0x2f, 0xb8, 0xea, 0x52,
    0xb0, 0xbe, 0x01, 0xcd, 0x1e, 0x41, 0x28, 0x67, 0x72, 0x0b, 0x32, 0x6e,
    0xb3, 0x89, 0xd0, 0x11, 0xbd, 0x70, 0xd8, 0xaf, 0x03, 0x5f, 0xb0, 0xd8,
    0x58, 0x9d, 0xbc, 0xe3, 0xc6, 0x66, 0xf5, 0xea, 0x8d, 0x4c, 0x79, 0x54,
    0xc5, 0x0c, 0x3f, 0x34, 0x0b, 0x04, 0x67, 0xf8, 0x1b, 0x42, 0x59, 0x61,
    0xc1, 0x18, 0x43, 0x07, 0x4d, 0xf6, 0x20, 0xf2, 0x08, 0x40, 0x4b, 0x39,
    0x4c, 0xf9, 0xd3, 0x7f, 0xf5, 0x4b, 0x5f, 0x1a, 0xd8, 0xf6, 0xea, 0x7d,
    0xa3, 0xc5, 0x61, 0xdf, 0xa7, 0x28, 0x1f, 0x96, 0x44, 0x63, 0xd2, 0xcc,
    0x35, 0xa4, 0xd1, 0xb0, 0x34, 0x90, 0xde, 0xc5, 0x1b, 0x07, 0x11, 0xfb,
    0xd6, 0xf5, 0x5f, 0x79, 0x23, 0x4d, 0x5b, 0x7c, 0x76, 0x66, 0x22, 0xa6,
    0x6d, 0xe9, 0x2b, 0xe9, 0x96, 0x46, 0x1d, 0x5e, 0x4d, 0xc8, 0x78, 0xef,
    0x9b, 0xca, 0x03, 0x05, 0x21, 0xe8, 0x35, 0x1e, 0x4b, 0xae, 0xd2, 0xfd,
    0x04, 0xf9, 0x46, 0x73, 0x68, 0xc4, 0xad, 0x6a, 0xc1, 0x86, 0xd0, 0x82,
    0x45, 0xb2, 0x63, 0xa2, 0x66, 0x6d, 0x1f, 0x6c, 0x54, 0x20, 0xf1, 0x59,
    0x9d, 0xfd, 0x9f, 0x43, 0x89, 0x21, 0xc2, 0xf5, 0xa4, 0x63, 0x93, 0x8c,
    0xe0, 0x98, 0x22, 0x65, 0xee, 0xf7, 0x01, 0x79, 0xbc, 0x55, 0x3f, 0x33,
    0x9e, 0xb1, 0xa4, 0xc1, 0xaf, 0x5f, 0x6a, 0x54, 0x7f};

#include <stdio.h>
#include <stdlib.h>

void test(const uint8 *pt, const uint8 *ct, uint32 msg_len,
          const uint8 *key, uint32 key_len)
{
    rc4_ctx ctx;
    uint8 dst[512];

    rc4_ks(&ctx, key, key_len);
    rc4_encrypt(&ctx, pt, dst, msg_len);

    if (memcmp(dst, ct, msg_len)) {
        fprintf(stderr, "Test failed.\n");
        exit(EXIT_FAILURE);
    }

    rc4_decrypt(&ctx, dst, dst, msg_len);

    if (memcmp(dst, pt, msg_len)) {
        fprintf(stderr, "Test failed.\n");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    printf("RC4 Validation test\n\n");

    test(pt1, ct1, sizeof(pt1), key1, sizeof(key1));
    printf("Test vector 1: OK\n");

    test(pt2, ct2, sizeof(pt2), key2, sizeof(key2));
    printf("Test vector 2: OK\n");

    test(pt3, ct3, sizeof(pt3), key3, sizeof(key3));
    printf("Test vector 3: OK\n");

    printf("\nAll tests passed.\n");

    return 0;
}

#endif /* TEST_VECTORS */
