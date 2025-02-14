#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "utils.h"

#define WRITE_TAG "-w"
#define READ_TAG "-r"

void write_png(const char *filename, png_structp png_ptr, png_infop info_ptr, png_bytep *row_pointers, int width, int height)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        print_error(WRITE_TAG);
        return;
    }

    png_structp write_png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!write_png_ptr)
    {
        print_error(WRITE_TAG);
        fclose(fp);
        return;
    }

    png_infop write_info_ptr = png_create_info_struct(write_png_ptr);
    if (!write_info_ptr)
    {
        print_error(WRITE_TAG);
        png_destroy_write_struct(&write_png_ptr, NULL);
        fclose(fp);
        return;
    }

    if (setjmp(png_jmpbuf(write_png_ptr)))
    {
        print_error(WRITE_TAG);
        png_destroy_write_struct(&write_png_ptr, &write_info_ptr);
        fclose(fp);
        return;
    }

    png_init_io(write_png_ptr, fp);

    png_set_IHDR(
        write_png_ptr,
        write_info_ptr,
        width, height,
        8,
        PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(write_png_ptr, write_info_ptr);
    png_write_image(write_png_ptr, row_pointers);
    png_write_end(write_png_ptr, NULL);

    for (int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);
    png_destroy_write_struct(&write_png_ptr, &write_info_ptr);
}

void read_png(const char *filename, png_structp *png_ptr, png_infop *info_ptr, png_bytep **row_pointers, int *width, int *height)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        print_error(READ_TAG);
        return;
    }

    *png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!*png_ptr)
    {
        print_error(READ_TAG);
        fclose(fp);
        return;
    }

    *info_ptr = png_create_info_struct(*png_ptr);
    if (!*info_ptr) {
        print_error(READ_TAG);
        png_destroy_read_struct(png_ptr, NULL, NULL);
        fclose(fp);
        return;
    }

    if (setjmp(png_jmpbuf(*png_ptr)))
    {
        print_error(READ_TAG);
        png_destroy_read_struct(png_ptr, info_ptr, NULL);
        fclose(fp);
        return;
    }

    png_init_io(*png_ptr, fp);
    png_read_info(*png_ptr, *info_ptr);

    *width = png_get_image_width(*png_ptr, *info_ptr);
    *height = png_get_image_height(*png_ptr, *info_ptr);
    png_byte color_type = png_get_color_type(*png_ptr, *info_ptr);

    if (color_type == PNG_COLOR_TYPE_RGBA || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
    	print_error(READ_TAG);
    	png_destroy_read_struct(png_ptr, info_ptr, NULL);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(*png_ptr);
    }

    if (color_type == PNG_COLOR_TYPE_GRAY)
    {
        png_set_gray_to_rgb(*png_ptr);
    }

    png_read_update_info(*png_ptr, *info_ptr);

    *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * (*height));
    for (int y = 0; y < *height; y++)
    {
        (*row_pointers)[y] = (png_byte*)malloc(png_get_rowbytes(*png_ptr, *info_ptr));
    }

    png_read_image(*png_ptr, *row_pointers);

    fclose(fp);
}
