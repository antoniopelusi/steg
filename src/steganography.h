#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <png.h>

void embed_message(png_bytep *row_pointers, int width, int height, unsigned char *message, int *map, long size, long msg_len);

void extract_message(png_bytep *row_pointers, int width, int height, unsigned char *output, int *map, long size);

#endif