// Loot Data
#include "looting.h"
#include "tools.h"

#include <json-c/json.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/*
	LINKS
		https://linuxprograms.wordpress.com/2010/05/20/json-c-libjson-tutorial/
*/

#define LINESIZE 500
#define APACHE "?"
#define NGINX "?"

bool Looting = false;
size_t arraySize = 256;
int arrayCount = 0;
struct Loot{
	int seen;
	char ipAddress[16];
};

void lootTest(){
	// size_t buff = 3;
	// int arraySize = 1;
	// char *array = malloc(buff * arraySize * sizeof(char));
	// if (array == NULL){
	// 	printf("MEMROY CANNOT BE ALLOCATED");
	// 	free(array);
	// }
	// array[0] = 'h';
	// array[1] = 'i';
	// array[2] = '\0';
	// printf("%s\n", array+buff*arraySize);

	// arraySize += 1;
	// char *tmp = realloc(array, buff * arraySize * sizeof(char));
	// if (tmp == NULL){
	// 	printf("MEMROY CANNOT BE ALLOCATED");
	// 	free(tmp);
	// }
	// array = tmp;
	// strcpy(array+buff*arraySize, "fo");
	// printf("%s\n", array+buff*arraySize);

//----------------------------------------------
	// char *array[3 * 4];
	size_t size = 1;
	size_t buff = 4;
	char *array = malloc(buff * size * sizeof(char*));
	strcpy(array, "aa");

	size += 1;
	array = realloc(array, buff * size * sizeof(char*));
	strcpy(array+buff*(size-1), "bb");

	size += 1;
	array = realloc(array, buff * size * sizeof(char*));
	
	strcpy(array+buff+buff, "cc");
	printf("%s\n", array);
	printf("%s\n", array+buff);
	printf("%s\n", array+buff*2);

	for (size_t i = 0; i < sizeof(array); ++i){
		printf("%d ", array[i]);
	}

	free(array);
	return;
}

void setLooting(bool setting){
	Looting = setting;
}

/*--------------------
	Main
*/
int lootData(char *path){
	// if ( !Looting )
	// 	return 0;

// Token vars
	const char ipToken[6] = " - - ";
	// const char uriToken[3] = "\" ";
	char *token;

// Vars
	// TODO: Use alternative method for struct 
	// https://www.youtube.com/watch?v=shYMgRcjm5A&list=RDCMUC6qj_bPq6tQ6hLwOBpBQ42Q&index=4
	struct Loot *data = malloc(arraySize * sizeof(struct Loot));
	if (data == NULL){
		free(data);
		colourText("[-] Error: Cannot allocate memory to array.\n", 'r');
		return 0;
	}
	char line[LINESIZE];
	FILE *fp;

// Open log file
	if ((fp = fopen(path, "r")) == NULL){
		// Close 
		fclose(fp);
		printf("Error: Log file was not found or is unreadable\n");
		return -1;
	}

// Start looping through log file and finding bannable IPs
	// while(!feof(fp)){
	for (int z = 0; z < 10; ++z){
		fgets(line, LINESIZE, fp);
		token = strtok(line, ipToken);
		printf("\nFound IP: %s", token);

		bool foundInArray = false;

		for (int i = 0; i < arrayCount+1; ++i){
			if (strcmp(data[i].ipAddress, token) == 0){
				colourText(": [+] I know your still there", 'g');
				data[i].seen += 1;
				foundInArray = true;
				break;
			}else{
				colourText(": [-]", 'r');
				foundInArray = false;
			}
		}

		if (!foundInArray){
			strcpy(data[arrayCount].ipAddress, token);
			data[arrayCount].seen += 1;

			struct Loot *tmp;
			arrayCount += 1;

		// Increase the memory allocation
			if (arrayCount == 250){
				arraySize *= 2;
				//|
				tmp = realloc(data, arraySize * sizeof(struct Loot));
				if (tmp == NULL){
					colourText("[-] Error: Cannot reallocate memory to array.\n", 'r');
					free(tmp);
					exit(EXIT_FAILURE);
				}
				data = tmp;
			}
			printf(" Added IP to struct");
		}
	}
	
// DEBUGGING
	// puts("Data Collected");
	// for (int i = 0; i < arrayCount; ++i){
	// 	printf("%s\t", data[i].ipAddress);
	// 	printf("%d\n", data[i].seen);
	// }
	// puts("");
	// int foo = 5;
	// printf("\n%s\n", data[foo].ipAddress);
	// printf("%d\n", data[foo].seen);

	fclose(fp);
	return 0;
}