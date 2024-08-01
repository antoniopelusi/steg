#ifndef UTILS_H
#define UTILS_H

void print_menu(char **argv);

void print_success(char* flag, char *input_image, char *input_text, char *output_image, char *output_text);

void print_error(char *flag);

void init_array(int *map, int size);

char *read_text(char *input_text, char *text);

void write_text(char *input_text, char *text);

#endif