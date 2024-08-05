#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "utils.h"
#include "image.h"
#include "random.h"
#include "steganography.h"
#include "hash.h"
#include "cipher.h"

#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[m"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"

void write(int argc, char **argv)
{
	char *flag = argv[1];
	char *input_image = argv[2];
	long seed = sha1_to_digits(argv[3]);
	char *input_text = argv[4];

	char *output_image = "output.png";

    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep *row_pointers = NULL;
    int width, height;

    read_png(input_image, &png_ptr, &info_ptr, &row_pointers, &width, &height);

	long size_bit = ((width * height) * 3);
	long size_byte = size_bit / 8;
	
	int map[size_bit];
	
	init_array(map, size_bit);
	
    shuffle(map, size_bit, seed);

	unsigned char message[size_byte];
	
	read_text(input_text, message, sizeof(message));
		
	unsigned char encrypted_message[size_byte];

	unsigned char key[size_byte];
	    
    generate_key(key, size_byte, seed);
    
	long msg_len = encrypt(message, encrypted_message, key, size_byte);
	
	embed_message(row_pointers, width, height, encrypted_message, map, size_bit, msg_len);

	write_png(output_image, png_ptr, info_ptr, row_pointers, width, height);

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	

	print_success(flag, input_image, input_text, output_image, NULL);
}

void read(int argc, char **argv)
{
	char *flag = argv[1];
	char *input_image = argv[2];
	long seed = sha1_to_digits(argv[3]);

	char *output_text = "output.txt";
	
    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep *row_pointers = NULL;
    int width, height;

    read_png(input_image, &png_ptr, &info_ptr, &row_pointers, &width, &height);

	long size_bit = ((width * height) * 3);
	long size_byte = size_bit / 8;
	
	int map[size_bit];

	init_array(map, size_bit);

    shuffle(map, size_bit, seed);

    unsigned char extracted_message[size_byte];

    extract_message(row_pointers, width, height, extracted_message, map, size_bit);
    
    unsigned char decrypted_message[size_byte];

	unsigned char key[size_byte];
	
    generate_key(key, size_byte, seed);
    
	decrypt(extracted_message, decrypted_message, key, size_byte);

	write_text(output_text, decrypted_message);

    for (int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }

    free(row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	
	print_success(flag, input_image, NULL, NULL, output_text);
}

int main(int argc, char **argv)
{
	if ((argc == 5) && !strcmp(argv[1], "-w"))
	{
		write(argc, argv);
	}
	else if ((argc == 4) && !strcmp(argv[1], "-r"))
	{
		read(argc, argv);
	}
	else
	{
		print_menu(argv);
		exit(EXIT_FAILURE);
	}

    exit(EXIT_SUCCESS);
}