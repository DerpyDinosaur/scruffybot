#include <stdlib.h>
#define RED 	"\x1b[31m"
#define GREEN 	"\x1b[32m"
#define YELLOW 	"\x1b[33m"
#define BLUE 	"\x1b[34m"
#define RESET 	"\x1b[0m"

void manipArray(char *array, int buffer, size_t size, int opt);
void createArray(char *array, int buffer, size_t size);
void colourText(char *text, char colour);