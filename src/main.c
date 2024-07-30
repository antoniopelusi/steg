#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "utils.h"
#include "image.h"
#include "random.h"
#include "steganography.h"

#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[m"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"

int main(int argc, char *argv[])
{
	int seed = 0;
	long size = 0;
	int *map = NULL;
	
	char *flag = NULL;
	char *input_image = NULL;
	char *input_text = NULL;
	char *text = NULL;
	char *output_image = "output.png";
	char *output_text = "output.txt";
	
	seed = strtol(argv[3], NULL, 10);
	
	if ((argc == 5) && !strcmp(argv[1], "-w") && check_validity(argv[3]))
	{
		flag = argv[1];
		input_image = argv[2];
		input_text = argv[4];

	    png_structp png_ptr;
	    png_infop info_ptr;
	    png_bytep *row_pointers = NULL;
	    int width, height;

	    read_png(input_image, &png_ptr, &info_ptr, &row_pointers, &width, &height);

		size = ((width * height) * 4);
		
		map = (int*) malloc(size * sizeof(int));
		
		init_array(map, size);

	    shuffle(map, size, &seed);

		text = read_text(input_text, text);

		embed_message(row_pointers, width, height, text, map, size);

		write_png(output_image, png_ptr, info_ptr, row_pointers, width, height);

		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		
		char hidden_pwd[strlen(argv[3]) + 1];
		
		for (int i = 0; i < strlen(argv[3]); i++)
		{
			hidden_pwd[i] = '*';
		}
		hidden_pwd[strlen(argv[3])] = '\0';
		
		print_success(flag, input_image, input_text, output_image, output_text, hidden_pwd);
	}
	else if ((argc == 4) && !strcmp(argv[1], "-r") && check_validity(argv[3]))
	{
		flag = argv[1];
		input_image = argv[2];

	    png_structp png_ptr;
	    png_infop info_ptr;
	    png_bytep *row_pointers = NULL;
	    int width, height;

	    read_png(input_image, &png_ptr, &info_ptr, &row_pointers, &width, &height);
	
		size = ((width * height) * 4);
		
		map = (int*) malloc(size * sizeof(int));

		init_array(map, size);

	    shuffle(map, size, &seed);
		
	    char *extracted_message = (char *)malloc(size * sizeof(char));
	
	    extract_message(row_pointers, width, height, extracted_message, size, map, size);
		
		write_text(output_text, extracted_message);
		
		free(extracted_message);

	    for (int y = 0; y < height; y++) {
	        free(row_pointers[y]);
	    }

	    free(row_pointers);
	    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		
		char hidden_pwd[strlen(argv[3]) + 1];

		for (int i = 0; i < strlen(argv[3]); i++)
		{
			hidden_pwd[i] = '*';
		}
		hidden_pwd[strlen(argv[3])] = '\0';

		print_success(flag, input_image, input_text, output_image, output_text, hidden_pwd);
	}
	else
	{
		print_menu(argc, argv);
		
		exit(EXIT_FAILURE);
	}

    exit(EXIT_SUCCESS);
}