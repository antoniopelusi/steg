#include <png.h>

void embed_message(png_bytep *row_pointers, int width, int height, unsigned char *message, int *map, long size, long msg_len)
{
    int bit_count = 0;

    for (int i = 0; i < size && bit_count / 8 < msg_len; i++)
    {
        int linear_pos = map[i];
        int y = linear_pos / (width * 3);
        int x = linear_pos % (width * 3);

        if (y >= 0 && y < height && x >= 0 && x < width * 3)
        {
            png_bytep row = row_pointers[y];

            int bit_to_hide = (message[bit_count / 8] >> (bit_count % 8)) & 1;

            row[x] = (row[x] & ~1) | bit_to_hide;
            bit_count++;
        }
    }
}

void extract_message(png_bytep *row_pointers, int width, int height, unsigned char *output, int *map, long size)
{
    int bit_count = 0;
    int char_index = 0;
    unsigned char current_char = 0;

    for (int i = 0; i < size && char_index < size - 1; i++)
    {
        int linear_pos = map[i];
        int y = linear_pos / (width * 3);
        int x = linear_pos % (width * 3);

        if (y >= 0 && y < height && x >= 0 && x < width * 3)
        {
            png_bytep row = row_pointers[y];

            current_char |= (row[x] & 1) << (bit_count % 8);
            bit_count++;
            if (bit_count % 8 == 0)
            {
                output[char_index++] = current_char;
                current_char = 0;
            }
        }
    }
}