/*
	Developed By: Adam Brickhill
	In loving memory of my dog Scruffy
*/
#include "verbose.h"
#include "looting.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

// CONSTANTS
#define LINESIZE 500
#define JAILCHAR 17
/*
TODO:
	0: Create support for multiple log files and servers
	1: Blanket block IPs from services like Amazon and Digital Ocean or other countries.

	10: Learn how to make dependancies


	* Program is woken via cron job
	* Reads contents of current logs
		Data is first gathered about each IP address
		Collect {offences, numOffences, OSTypes, numOSTypes, browserTypes, numBrowserTypes}

	* Increase/decrease offence grade to IP addresses causing trouble
	* Check jail file and proceed with bans and un-bans to those diserving

IDEAS
	- Harsher bans on non-Australian IP addresses
	- Harsher bans on IPs that are derived from services like Amazon and Digital Ocean ...
	- Create a jail system that remembers IP addresses and inflics harsher punishments
	  based on their previous sentence

LINKS
	~ TOKEN ~
	https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

	~ STRUCTURES ~
	https://www.dummies.com/programming/c/basics-of-structure-for-c-programming/

*/

void help(){
	puts("EXAMPLES");
	puts("\tscruff -h");

	puts("\nOPTIONS\t\tDESCRIPTION");
	puts("\t-o\tOutput Type mode, outputs a file based on the format.\n\t\t\tTypes include htaccess, foo, bar");
	puts("\t-v\tVerbose mode.");
}

int main(int argc, char *argv[]){
// Init variables
	int opt;
	char *_outputfile;

// Loop through arguments, colons can have extra commands after them.
	while((opt = getopt(argc, argv, ":o:v")) != -1){
		switch(opt){
			case 'o':// Set output file
				if (strcmp(optarg, "htaccess") == 0){
					_outputfile = optarg;
				}else{
					help();
					return 0;
				}
				break;

			case 'v':// Enable verbose
				setVerbose(true);
				break;

			case ':':
				printf("Option: -%c requires a value\n", optopt);
				exit(EXIT_SUCCESS);

			case 'h':
			case '?':
				printf("Invalid Option: %c\n", optopt);
				help();
			    exit(EXIT_SUCCESS);

			default:
				break;
		}
	}

	// verbose("Verbose is active\n");
	// lootData("logSamples/access.log");
	// lootTest();
	// exit(EXIT_SUCCESS);

// Vars
	// Create a jail array
	char **jail;
	size_t jailSize = 1;
	jail = malloc(jailSize * sizeof(char*));
	jail[0] = malloc(JAILCHAR * sizeof(char));
	// Black listed URLs
	const char *nonoUrl[20] = {
		"wp-includes", "xmlrpc.php", "wordpress", "robots.txt", "login",
		"@md5", ".git", "../"
	};
	const size_t nonoUrlSize = sizeof(&nonoUrl);
	bool malicious = false;
	char verboseStr[64];
// File Pointer vars
	FILE *fp;
	char buffer[LINESIZE];
// Token vars
	const char ipToken[6] = " - - ";
	char *token;

/*---------------------------------
	PROGRAM START
*/
	printf("Scruffy is on the hunt...\n");
// Open log file
	if ((fp = fopen("logSamples/access.log", "r")) == NULL){
		// Close 
		fclose(fp);
		printf("Error: Log file was not found or is unreadable\n");
		return -1;
	}

// Loop through log file and find bad ips'
	while(!feof(fp)){
	// for (int z = 0; z < 10; ++z){
		fgets(buffer, LINESIZE, fp);
	// Check if the IP infringes on nonoUrl laws
		for (int x = 0; x < nonoUrlSize; ++x){
		// If a someone is accessing the CTF give them a free pass
			if(strstr(buffer, "GET /ctf/") != NULL){
				break;
			}

		// If an illegal url has been accessed set malicious bool to true
			if (strstr(buffer, nonoUrl[x]) != NULL){
				strcpy(verboseStr, nonoUrl[x]);
				malicious = true;
				break;
			}
		}

	// Check If IP is already in jail
		token = strtok(buffer, ipToken);
		for (size_t i = 0; i < jailSize-1; ++i){
			if (strcmp(jail[i], token) == 0){
				malicious = false;
			}
		}
	// If buffer is found malicious then save IP to Jail.
		if (malicious){
			strcpy(jail[jailSize-1], token);

			jailSize += 1;
			jail = realloc(jail, jailSize * sizeof(char*));
			jail[jailSize-1] = malloc(JAILCHAR * sizeof(char));

			malicious = false;

		// DEBUG
			verbose(GREEN"[+] IP: %s\n"RED"    Accessed: %s\n"RESET, token, verboseStr);
		}
	}
// puts("");
// 	for (size_t x = 0; x < 2; ++x){
// 		for (size_t y = 0; y < JAILCHAR; ++y){

// 			if (y == 16){
// 				printf("%d\n", jail[x][y]);
// 			}else{
// 				printf("%d ", jail[x][y]);
// 			}
// 		}
// 	}
// puts("");
// 	puts("~ JAIL ~");
// 	for (size_t i = 0; i < jailSize; ++i){
// 		printf("%s\n", jail[i]);
// 	}

	// for (int i = 0; i < sizeof(verboseStr); ++i){
	// 	printf("%d", verboseStr[i]);
	// }printf("\n");

	free(jail);
	return 0;
}