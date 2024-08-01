#ifndef RANDOM_H
#define RANDOM_H

void shuffle(int *map, int size, int seed);

void generate_key(unsigned char *key, int length);

void stream_cipher(char *input, char *output, unsigned char *key, int length);

#endif