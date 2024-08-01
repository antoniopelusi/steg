#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BOLD_ON "\e[1m"
#define BOLD_OFF "\e[m"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"

void print_menu(char **argv)
{
	printf("+-----------------------------------------------+\n");
    printf("| %sUsage%s\t\t\t\t\t\t|\n", BOLD_ON, BOLD_OFF);
    printf("+-----------------------------------------------+\n");
    printf("| %sWrite%s: %s %s-w%s <%simage%s> <%spassword%s> <%stext%s>\t|\n", BOLD_ON, BOLD_OFF, argv[0], COLOR_YELLOW, COLOR_RESET, COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET, COLOR_BLUE, COLOR_RESET);
    printf("| %sRead%s:  %s %s-r%s <%simage%s> <%spassword%s>\t\t|\n", BOLD_ON, BOLD_OFF, argv[0], COLOR_YELLOW, COLOR_RESET, COLOR_GREEN, COLOR_RESET, COLOR_RED, COLOR_RESET);
    printf("+-----------------------------------------------+\n");
    printf("| %sSupported image formats%s: .%spng%s\t\t\t|\n", BOLD_ON, BOLD_OFF, COLOR_CYAN, COLOR_RESET);
    printf("| %sPassword length%s: %s4%s-%s8%s digits\t\t\t|\n", BOLD_ON, BOLD_OFF, COLOR_CYAN, COLOR_RESET, COLOR_CYAN, COLOR_RESET);
    printf("+-----------------------------------------------+\n\n");
}

void print_success(char* flag, char *input_image, char *input_text, char *output_image, char *output_text)
{
	char *hidden_pwd = "********";
	
	if (!strcmp(flag, "-w"))
	{
		printf("+-----------------------------------------------+\n");
		printf("| %s[✓]%s %sMessage written%s\t\t\t\t|\n", COLOR_GREEN, COLOR_RESET, BOLD_ON, BOLD_OFF);
		printf("+-----------------------------------------------+\n");
		printf("|  %s•%s  Input image:\t%-24s|\n", COLOR_YELLOW, COLOR_RESET, input_image);
		printf("|  %s•%s  Password:\t\t%-24s|\n", COLOR_YELLOW, COLOR_RESET, hidden_pwd);
		printf("|  %s•%s  Input text:\t%-24s|\n", COLOR_YELLOW, COLOR_RESET, input_text);
		printf("+-----------------------------------------------+\n");
		printf("|  %s•%s  Output image:\t%-24s|\n", COLOR_CYAN, COLOR_RESET, output_image);
		printf("+-----------------------------------------------+\n\n");
	}
	else if (!strcmp(flag, "-r"))
	{
		printf("+-----------------------------------------------+\n");
		printf("| %s[✓]%s %sMessage read%s\t\t\t\t|\n", COLOR_GREEN, COLOR_RESET, BOLD_ON, BOLD_OFF);
		printf("+-----------------------------------------------+\n");
		printf("|  %s•%s  Input image:\t%-24s|\n", COLOR_YELLOW, COLOR_RESET, input_image);
		printf("|  %s•%s  Password:\t\t%-24s|\n", COLOR_YELLOW, COLOR_RESET, hidden_pwd);
		printf("+-----------------------------------------------+\n");
		printf("|  %s•%s  Output text:\t%-24s|\n", COLOR_CYAN, COLOR_RESET, output_text);
		printf("+-----------------------------------------------+\n\n");
	}
}

void print_error(char *flag)
{
	if (!strcmp(flag, "-w"))
	{
		printf("+-----------------------------------------------+\n");
		printf("| %s[✗]%s %sError%s: Write\t\t\t\t|\n", COLOR_RED, COLOR_RESET, BOLD_ON, BOLD_OFF);
		printf("+-----------------------------------------------+\n");
		
	}
	else if (!strcmp(flag, "-r"))
	{
		printf("+-----------------------------------------------+\n");
		printf("| %s[✗]%s %sError%s: Read\t\t\t\t|\n", COLOR_RED, COLOR_RESET, BOLD_ON, BOLD_OFF);
		printf("+-----------------------------------------------+\n");
	}

	exit(EXIT_FAILURE);
}

void init_array(int *map, int size)
{    
    for (int i = 0; i < size; i++)
    {
    	map[i] = i + 1;
    }
}

char *read_text(char *input_text, char *text)
{
	FILE *file = fopen(input_text, "rb"); 

	if (file)
	{
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		rewind(file);
		
		text = (char*) malloc((size + 1) * sizeof(char));
		
		if (text)
		{
			fread(text, sizeof(char), size, file);
			text[size] = '\0';
		}
		
		fclose(file);
	}

	return text;
}

void write_text(char *output_text, char *text)
{
	FILE *file = fopen(output_text, "w");

    fprintf(file, "%s", text);
    
    fclose(file);
}