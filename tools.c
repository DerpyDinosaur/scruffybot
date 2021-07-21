// Tools
#include "tools.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/*---------------------------------
	Arrays
*/

void manipArray(char *array, int buffer, size_t size, int opt){
	char *tmp;
	switch(opt){
		case 0:
			tmp = malloc(buffer * sizeof(char));
			break;
		case 1:
			tmp = realloc(array, size * sizeof(char*));
			break;

		default:
			colourText("Error switch statement broke...", 'r');
			break;
	}

	if (tmp == NULL){
		colourText("Error creating an array, program will terminate", 'r');
		exit(EXIT_FAILURE);
	}
	array = tmp;
}

// void growArray(char *array, int buffer, size_t size){
// 	char *tmp = realloc(array, buffer * size * sizeof(char));
// 	if (tmp == NULL){
// 		colourText("Error creating an array, program will terminate", 'r');
// 		exit(EXIT_FAILURE);
// 	}
// 	array = tmp;
// }


/*---------------------------------
	Colour
*/

//||
void colourText(char *text, char colour){
	if (colour == 'r'){
		printf(RED"%s"RESET, text);
	}else if(colour == 'g'){
		printf(GREEN"%s"RESET, text);
	}else if(colour == 'y'){
		printf(YELLOW"%s"RESET, text);
	}else if(colour == 'b'){
		printf(BLUE"%s"RESET, text);
	}
}
