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
#ifndef TX_H
#define TX_H
/**
 * FILENAME: tx.h
 * AUTHOR: projectmoon
 * DESCRIPTION:
 * Header file with prototypes for tx functions, as well as the global
 * variables for the program.
 */

/**
 * Gets the number of seconds to execute this program.
 */
unsigned long get_tx_secs(char* arg);

/**
 * Parses command-line arguments and sets the proper flags.
 */
void parseargs(int argc, char** argv);

/**
 * Signifies an error parsing command line arguments.
 * Prints an error message based on argument and then exits.
 */
void args_value_error(char arg);

/**
 * Prints help text.
 */
void help();

/**
 * Memory management.
 */
void tx_free();

/**
 * Functions relating to the parent/child.
 */
void execute();
void parent(pid_t pid);
void child();

/**
 * The time to execute the program in seconds, as well as its extern
 * declaration.
 */
unsigned long tx_time;
extern unsigned long tx_time;

/**
 * Child argument array and argc.
 */
char** tx_argv;
extern char** tx_argv;
int tx_argc;
extern int tx_argc;

#endif
