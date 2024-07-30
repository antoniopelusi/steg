#include <png.h>
#include <string.h>

#include <png.h>
#include <string.h>

void embed_message(png_bytep *row_pointers, int width, int height, const char *message, int *map, long size) {
    int msg_len = strlen(message) + 1;
    int bit_count = 0;
    
    for (int i = 0; i < size && bit_count / 8 < msg_len; i++) {
        int linear_pos = map[i];
        int y = linear_pos / (width * 4);
        int x = linear_pos % (width * 4);

        if (y >= 0 && y < height && x >= 0 && x < width * 4) {
            png_bytep row = row_pointers[y];
            row[x] = (row[x] & ~1) | ((message[bit_count / 8] >> (bit_count % 8)) & 1);
            bit_count++;
        }
    }
}

void extract_message(png_bytep *row_pointers, int width, int height, char *output, int max_length, int *map, long size) {
    int bit_count = 0;
    int char_index = 0;
    unsigned char current_char = 0;

    for (int i = 0; i < size && char_index < max_length - 1; i++) {
        int linear_pos = map[i];
        int y = linear_pos / (width * 4);
        int x = linear_pos % (width * 4);

        if (y >= 0 && y < height && x >= 0 && x < width * 4) {
            png_bytep row = row_pointers[y];
            current_char |= (row[x] & 1) << (bit_count % 8);
            bit_count++;
            if (bit_count % 8 == 0) {
                if (current_char == '\0') {
                    output[char_index] = '\0';
                    return;
                }
                output[char_index++] = current_char;
                current_char = 0;
            }
        }
    }
    output[char_index] = '\0';
}
