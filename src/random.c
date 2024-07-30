#define A 1664525
#define C 1013904223
#define M 4294967296

unsigned int lcg(int *seed)
{
    *seed = (A * (*seed) + C) % M;
    return *seed;
}

unsigned int random_range(int *seed, int min, int max)
{
    return min + (lcg(seed) % (max - min + 1));
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int *map, int size, int *seed)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = random_range(seed, 0, i);
        swap(&map[i], &map[j]);
    }
}

