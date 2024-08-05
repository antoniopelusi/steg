#ifndef CIPHER_H
#define CIPHER_H

long encrypt(unsigned char *input, unsigned char *output, unsigned char *key, long size_byte);

void decrypt(unsigned char *input, unsigned char *output, unsigned char *key, long size_byte);

#endif