/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Oct. 6, 2020
 * @assignment Lab 4
 * @course CSC 250
 *
 * source files for parsing the command line arguments
 **/   
#include "get_args.h"

/**
 *  function processes the command line arguments using getopt()
 *
 *  function returns 1 if the arguments are "correct", 0 otherwise
 *
 *  argc - number of command line arguments
 *  argv - list of command line arguments (list of C-strings)
 *  enc_ptr - pointer to an integer, set to 1 if encode, 0 for decode
 *  key_ptr - pointer to integer, key for encryption and decryption
 *  file_name - pointer to the filename that will be encrypted or decrypted 
 */
int process_args(int argc, char *argv[], int* enc_ptr, int* key_ptr, char file_name[]) {
    int opt;
    int encode = 0;
    int decode = 0;
    int got_key = 0;

    while ((opt = getopt(argc, argv, "k:d:e:")) != -1) {
        switch (opt) {
        case 'k':
            *key_ptr = atoi(optarg);
            got_key = 1;
            break;
        case 'e':
            encode = 1;
            strcpy(file_name, optarg);
            break;
        case 'd':
            decode = 1;
            strcpy(file_name, optarg);
            break;
        default: 
            print_command_usage(argv[0]);
            return 0;
        }
    }

    /* printf("d: %d, e: %d, k: %d, f: [%s] \n", decode, encode, *key_ptr, file_name); */  

    /* xor? well, not the smartest thing to do, but we just covered it in class... */
    if(!(decode ^ encode) || !got_key){
        print_command_usage(argv[0]);
        return 0;
    }

    *enc_ptr = encode;

    return 1;
}


/**
 *  function to print a useful help message
 */
void print_command_usage(char executable_name[]) {
    fprintf(stderr, "Usage: %s -k key -d|-e file_name \n", executable_name);
    fprintf(stderr, " -k key to decode or encode \n");
    fprintf(stderr, " -d decode file_name \n");
    fprintf(stderr, " -e encode file_name \n");
}


