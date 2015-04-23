/*
 ============================================================================
 Name        : function-trace.c
 Author      : Michael
 Version     : 0.1
 Copyright   : Your copyright notice
 Description : parse function tracer log and call grep on .map file.
 Example 	 : $>ftrace.exe tracelog.txt contiki-ek123gxl.map
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	FILE *tracelog = fopen(argv[1], "r");

	if (argc != 3 || tracelog == NULL) {
		printf("file read error\n");
		fclose (tracelog);
		return EXIT_FAILURE;
	}

	char line[25];
	char cmd[100];
	char* address_string;
	int address;

	while(fgets(line, 25, tracelog) != NULL) {
		if (line[10] != ' ') {
			printf("-----------------------------------------------------------------------------------------\n");
		}
		else {
			memset(cmd, 0, 100);
			line[10] = 0; // stringify the hex address
			address_string = line;
			address = (int)strtol(address_string, NULL, 16);
			address--;

			sprintf(cmd, "grep 0x%08x %s", address, argv[2]);
			printf("%s", line+11);
			system(cmd);
		}
	}

	fclose(tracelog);
	return EXIT_SUCCESS;
}
