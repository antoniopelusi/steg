#include <png.h>

#ifndef IMAGE_H
#define IMAGE_H

void write_png(char *filename, png_structp png_ptr, png_infop info_ptr, png_bytep *row_pointers, int width, int height);

void read_png(char *filename, png_structp *png_ptr, png_infop *info_ptr, png_bytep **row_pointers, int *width, int *height);

#endif