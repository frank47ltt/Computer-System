/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Oct. 11, 2020
 * @assignment Lab 5
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
int process_image_args(int argc, char *argv[], int* hide_ptr, int* bit_ptr, char image_file_name[], char text_file_name[]); 
#endif


