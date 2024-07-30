#include <png.h>

#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

void embed_message(png_bytep *row_pointers, int width, int height, const char *message, int *map, long size);

void extract_message(png_bytep *row_pointers, int width, int height, char *output, int max_length, int *map, long size);

#endif