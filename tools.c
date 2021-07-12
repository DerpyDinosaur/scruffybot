// Tools
#include "tools.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/*---------------------------------
	Colour
*/
#define RED 	"\x1b[31m"
#define GREEN 	"\x1b[32m"
#define YELLOW 	"\x1b[33m"
#define BLUE 	"\x1b[34m"
#define RESET 	"\x1b[0m"
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
