/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Oct. 11, 2020
 * @assignment Lab 5
 * @course CSC 250
 *
 * source files for parsing the command line arguments
 **/   
#include "get_image_args.h"

/**
 *  function processes the command line arguments using getopt()
 *
 *  function returns 1 if the arguments are "correct", 0 otherwise
 *
 *  argc - number of command line arguments
 *  argv - list of command line arguments (list of C-strings)
 *  hide_ptr - pointer to an integer, set to 1 if hide, 0 for recover
 *  bit_ptr - pointer to integer, number of LSB bits (1, 2, or 4)
 *  file_name - pointer to the filename that will be encrypted or decrypted 
 */
int process_image_args(int argc, char *argv[], int* hide_ptr, int* bit_ptr, char image_file_name[], char text_file_name[]) {
    int opt;
    int hide = 0;
    int recover = 0;
    int got_bit = 0;

    while ((opt = getopt(argc, argv, "b:h:r:")) != -1) {
        switch (opt) {
        case 'b':
            *bit_ptr = atoi(optarg);
            got_bit = *bit_ptr == 1 || *bit_ptr == 2 || *bit_ptr == 4;
            break;
        case 'h':
            hide = 1;
            strcpy(image_file_name, optarg);
            break;
        case 'r':
            recover = 1;
            strcpy(image_file_name, optarg);
            break;
        default: 
            print_command_usage(argv[0]);
            return 0;
        }
    }


    /* printf("d: %d, e: %d, k: %d, img_f: [%s], txt_f:[%s] \n", hide, recover, *bit_ptr, img_file_name, text_file_name); */  

    /* xor? well, not the smartest thing to do, but we just covered it in class... */
    if(!(hide ^ recover) || !got_bit || optind >= argc){
        print_command_usage(argv[0]);
        return 0;
    }

    strcpy(text_file_name, argv[optind]);
    *hide_ptr = hide;

    return 1;
}


/**
 *  function to print a useful help message
 */
void print_command_usage(char executable_name[]) {
    fprintf(stderr, "Usage: %s -b bit -h|r ppm_image_file_name text_file_name \n", executable_name);
    fprintf(stderr, " -b bits per pixel to decode or encode (1, 2, or 4)\n");
    fprintf(stderr, " -h hide text (in text_file_name) in image (ppm_image_file_name) \n");
    fprintf(stderr, " -r recover text (store in text_file_name) from image (ppm_image_file_name) \n");
}


