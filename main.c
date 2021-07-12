/*
	Developed By: Adam Brickhill
	In loving memory of my dog Scruffy
*/
#include "verbose.h"
#include "looting.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#define LINESIZE 500

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
	puts("\t-v\tVerbose mode, enter as the first argument or it will be ignored.");
}

int main(int argc, char *argv[]){
// Init variables
	int opt;
	char *_logsPath = NULL;

// Loop through arguments, colons can have extra commands after them.
	while((opt = getopt(argc, argv, ":l:ov")) != -1){
		switch(opt){
			case 'l':// Define log file location
				_logsPath = optarg;
				break;

			case 'o':// Deactivate Data Collection
				setLooting(true);
				break;

			case 'v':// Activate verbose
				setVerbose(true);
				break;

			case 'h':
			case '?':
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
	size_t jailSize = 0;
	jail = malloc(jailSize+1 * sizeof(char));
	jail[0] = malloc(16 * sizeof(char));
	// Black listed URLs
	size_t nonoUrlSize = 3;
	const char nonoUrl[][20] = {
		"wp-includes", "xmlrpc.php", "wordpress"
	};
	bool malicious = false;
// File Pointer vars
	FILE *fp;
	char buffer[LINESIZE];
// Token vars
	const char ipToken[6] = " - - ";
	char *token;

// Open log file
	if ((fp = fopen("logSamples/access.log", "r")) == NULL){
		// Close 
		fclose(fp);
		printf("Error: Log file was not found or is unreadable\n");
		return -1;
	}

// Loop through log file and find bad ips'
	// while(!feof(fp)){
	for (int z = 0; z < 10; ++z){
		fgets(buffer, LINESIZE, fp);
	// Check if the IP infringes on nonoUrl laws
		for (int x = 0; x < 3; ++x){
		// If a someone is accessing the CTF give them a free pass
			if(strstr(buffer, "GET /ctf/") != NULL){
				break;
			}

		// If an illegal url has been accessed set malicious bool to true
			if (strstr(buffer, nonoUrl[x]) != NULL){
				printf("\nAccessed Illegal URL: %s\n", nonoUrl[x]);
				malicious = true;
				break;
			}
		}

	// Check If IP is already in jail
		token = strtok(buffer, ipToken);
		for (size_t i = 0; i < jailSize; ++i){
			if (strcmp(jail[i], token) == 0){
				malicious = false;
			}
		}
	// If buffer is found malicious then save IP to Jail.
		if (malicious){
			colourText("[+] IP has been added to jail.", 'g');
		// TODO: reallocate memory to jail
			strcpy(jail[jailSize], token);
			malicious = false;
		}
	}
	puts("");
	for (size_t i = 0; i < jailSize; ++i){
		printf("%s\n", jail[i]);
	}
	return 0;
}