/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Oct. 6, 2020
 * @assignment Lab 4
 * @course CSC 250
 *
 * header files for parsing the command line arguments
 **/  
#ifndef PROC_ARGS
#define PROC_ARGS

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>


void print_command_usage(char executable_name[]);
int process_args(int argc, char *argv[], int* enc_ptr, int* key_ptr, char file_name[]);

#endif


