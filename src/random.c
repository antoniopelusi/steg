#include <stdlib.h>

unsigned int random_range(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int *map, int size, long seed)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = random_range(0, i);
        swap(&map[i], &map[j]);
    }
}

void generate_key(unsigned char *key, int length, long seed)
{
    for (int i = 0; i < length; i++)
    {
        key[i] = random_range(0, 255);
    }
}