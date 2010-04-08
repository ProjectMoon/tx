/*
 * tx: Run programs for a specified time
 * Copyright (C) 2010 projectmoon
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.       
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tx.h"
/**
 * FILENAME: tx_cmdline.c
 * AUTHOR: projectmoon
 * DESCRIPTION:
 * Implementations for the command line portion of tx: parsing, setting
 * of variables, etc. 
 */

void help() {
	printf("Usage: tx -t <SECS> <COMMAND>...\n");
	printf("Executes COMMAND for a number of seconds SECS.\n");
	printf("Arguments must agree with the form specified in Usage.\n");
	printf("Options:\n");
	printf("  -t: execute for the specified number of seconds.\n");
}

unsigned long get_tx_secs(char* arg) {
	unsigned long ret = -1;
	char junk[80];
	
	int test = sscanf(arg, "%d%s", &ret, junk);
	
	//If one item is matched, it is a number.
	if (test == 1) {	
		return ret;
	}
	else {
		fprintf(stderr, "-t requires a numerical value.\n");
		help();
		exit(1);
	}
}

void parseargs(int argc, char** argv) {
	if (argc < 4) {
		fprintf(stderr, "%s: not enough arguments specified.\n", argv[0]);
		help();
		exit(1);
	}
	else {
		if (strcmp(argv[1], "-t") == 0) {
			tx_time = get_tx_secs(argv[2]);
		}
		else {
			fprintf(stderr, "%s: illegal argument specified.\n", argv[0]);
			help();
			exit(1);
		}
		
		//Now forward the rest of the arguments to the child.
		//minus 2 instead of 3 so we have room for null terminator.
		tx_argc = argc - 2;							
		tx_argv = calloc(tx_argc, sizeof(char*));
		
		int c;
		for (c = 3; c < argc; c++) {
			char* tx_arg = calloc(sizeof(argv[c]), sizeof(char));
			strcpy(tx_arg, argv[c]);
			tx_argv[c - 3] = tx_arg;
		}
		
		//null terminate argv array
		tx_argv[c - 3] = NULL;
		
	}
}

void args_value_error(char arg) {
	if (arg == 't') {
		fprintf(stderr, "Option -%c requires an argument.\n", arg);
		exit(1);
	}
}
