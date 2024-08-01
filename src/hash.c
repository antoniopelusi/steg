#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define SEED_LEN 8

int sha1_to_digits(char *password) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    char hash_digits[SHA_DIGEST_LENGTH + 1];
    char truncated_digits[SEED_LEN + 1];
    int seed;
    
    SHA1((unsigned char*)password, strlen(password), hash);
    
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        hash_digits[i] = (hash[i] % 10) + '0';
    }
    hash_digits[SHA_DIGEST_LENGTH] = '\0';
    
    strncpy(truncated_digits, hash_digits, 8);
    truncated_digits[8] = '\0';
    return(strtol(truncated_digits, NULL, 10));
}