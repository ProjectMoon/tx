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
#include <sys/types.h>
#include <signal.h>
#include "tx.h"
/**
 * FILENAME: tx.c
 * AUTHOR: projectmoon
 * DESCRIPTION:
 * Implementations for the main part of tx: forking, executing process,
 * and then killing said process.
 */

void tx_free() {
	//Free tx_argv
	int c;
	for (c = 0; c < tx_argc; c++) {
		free(tx_argv[c]);
	}
	
	//Now free all of tx_argv
	free(tx_argv);
}

void execute() {
	pid_t pid = fork();
	
	if (pid != 0) {
		parent(pid);
	}
	else {
		child();
	}
}

void parent(pid_t pid) {
	//Sleep for tx_time and then kill the child process.
	sleep(tx_time);
	kill(pid, SIGINT);
	tx_free();
}

void child() {
	execvp(tx_argv[0], tx_argv);
	
	//Should not be reachable if the program executes successfully.
	fprintf(stderr, "%s: file not found\n", tx_argv[0]);
	tx_free();
}

int main(int argc, char** argv) {
	parseargs(argc, argv);
	execute();
	return 0;
}
