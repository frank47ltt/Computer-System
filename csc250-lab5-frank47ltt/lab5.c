/**
 * @author Frank (Tongtong) Liu {liut18@wfu.edu}
 * @date Oct. 22, 2020
 * @assignment Lab 5
 * @course CSC 250
 *
 * This program will use command line arguments for bits, filename, and a flag to implement image steganography.
 * It will hides data in the pixels that form the image, specifically the lower order bits of the RGB values.
 * Data will be split into different parts and hide it into the LSB of images pixels, and then extract them out
 * in a separate function.
 **/   

#include "get_image_args.h"
#include "ppm_read_write.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function declaration goes there */
int hide_msg(struct Image *img, int bit, char text_file_name[], char img_file_name[]);
int recov_msg(struct Image *img, int bit);

int main(int argc, char* argv[]){
    struct Image *img; /* do not know how big so need dynamic allocation */
    char image_file_name[20];
    char text_file_name[20];
    int hide;
    int bit;
    int status_ok;

    status_ok = process_image_args(argc, argv, &hide, &bit, image_file_name, text_file_name);

    if (status_ok) {
        if(hide) { /* -h, go start to hide */
            /* status_ok = read_image(&img, image_file_name); */
            read_image(&img, image_file_name);  /* avoid warning saying status_ok is never used */
            status_ok = hide_msg(img, bit, text_file_name, image_file_name);
        }
        else { /* for writing, use same trick */
            /* status_ok = read_image(&img, image_file_name); */
            read_image(&img, image_file_name);  /* avoid warning saying status_ok is never used */
            status_ok = recov_msg(img, bit);
        }
    }
    return status_ok;
}
/**
 *  This function will be called when command line argument includes flag -h.
 *  Specifically it will read char from a text file and hide it into image according to 
 *  the size of input bits.
 *  @Parameters:
 *     struct Image *img: pointer to image struct
 *     int bit: number of bits to hide in each pixel
 *     char text_file_name[]: filename of text file to read from
 *     char img_file_name[]: name of image
 */
int hide_msg(struct Image *img, int bit, char text_file_name[], char img_file_name[]){   /* fixme double pointer here?*/
    FILE *fp; /* input file pointer */
    unsigned char *pixel_comp = (unsigned char *)img->data;  /*dereference img */
    /* move from red to green to blue to red to green to blue */
    int i;
    int j;
    int counter = 1;
    int num_pixels;
    unsigned char ch_mask;
    unsigned char img_mask;
    unsigned char tmp = 0;
    unsigned char prev_tmp = 0;
    const int num_done_process_char = 8 / bit;
    unsigned int positions_to_shift = 8 - bit;
    fp = fopen(text_file_name, "a+"); /* open for reading and writing, appending to file */
    if (fp == NULL) {
        puts("Cannot open the file successfully! File does not exist!");
        return 1;
    }
    if (bit == 1) {
        ch_mask = 0x01; /* 00000001 */
    }
    else if (bit == 2) {
        ch_mask = 0x03; /* 00000011 */
    }
    else { /* bit = 4 */
        ch_mask = 0x0f; /* 00001111 */
    }
    img_mask = ~ch_mask; /* img_mask will be the inverse of char mask */

    /* add :) to text */
    fputs(":)", fp); 
    fseek ( fp , 0 , SEEK_SET );
    tmp = fgetc(fp);
    i = 0;
    /* stop hidding when encounter :) and stop hidding when read the end of image */
    while (((prev_tmp != ':') || (tmp != ')')) && (i <= (img->height * img->width * 3))) {  
        /* mask parts of img and char out individually and OR them together */
        pixel_comp[i] = (unsigned char)((unsigned char)(pixel_comp[i] & img_mask) | (unsigned char)((unsigned char)(tmp >> positions_to_shift) & ch_mask));
        i++;
        positions_to_shift = positions_to_shift - bit;
        /* reset everything when finish hiding one char */
        if (i % num_done_process_char == 0) {
            positions_to_shift = 8 - bit;
            prev_tmp = tmp;
            tmp = fgetc(fp);
            counter++;
        }
    }

    /* store ")" in the image */
    for (j = 0; j < num_done_process_char; j++) {
        /* add those unsigned char everywhere simply reduce the warning from make tidy */
        printf("tmp is %c", tmp);
        pixel_comp[i] = (unsigned char)((unsigned char)(pixel_comp[i] & img_mask) | (unsigned char)((unsigned char)(tmp >> positions_to_shift) & ch_mask));
        printf("tmp is %c", tmp);
        i++;
        positions_to_shift = positions_to_shift - bit;
    }
    num_pixels = counter * num_done_process_char;
    write_image(img_file_name, img);
    fclose(fp);
    printf("%d characters hidden in %d pixels \n", counter, num_pixels);
    return 1;
}

/**
 *  This function will be called when command line argument includes flag -r.
 *  Specifically it will recover bits from pixels back and form the char.
 *  @Parameters:
 *     struct Image *img: pointer to image struct
 *     int bit: number of bits to hide in each pixel
 */
int recov_msg(struct Image *img, int bit) {
    unsigned char *pixel_comp = (unsigned char *)img->data; 
    int i = 0;
    int counter = 0;
    int num_pixels;
    unsigned int positions_to_shift = 8 - bit;
    const int num_of_pixel_to_getChar = 8 / bit;
    unsigned char tmp = 0;
    unsigned char prev_tmp = 0;
    unsigned char recover_mask;
    FILE *fpw;
    fpw = fopen("recover.txt","w");
    if (bit == 1) {
        recover_mask = 0x01; /* 00000001 */
    }
    else if (bit == 2) {
        recover_mask = 0x03; /* 00000011 */
    }
    else { /* bit = 4 */
        recover_mask = 0x0f; /* 00001111 */
    }
    /* stop recovering when encounter :) and stop hidding when read the end of image */
    while (((prev_tmp != ':') || (tmp != ')')) && (i <= (img->height * img->width * 3))) {
        if (i % num_of_pixel_to_getChar == 0) {
            prev_tmp = tmp;
            tmp = 0;
        }
        /* retrieve bits from pixels and OR them back to form a char */
        tmp = tmp | (unsigned char)((unsigned char)(pixel_comp[i] & recover_mask) << positions_to_shift);
        i++;
        positions_to_shift = positions_to_shift - bit;
        /* reset everything when finish recovering one char */
        if(i % num_of_pixel_to_getChar == 0) {
            fputc(tmp, fpw);
            counter++;
            positions_to_shift = 8 - bit;
        }
 
    }
    num_pixels = counter * num_of_pixel_to_getChar;
    printf("%d characters recovered from %d pixels \n", counter, num_pixels);
    fclose(fpw);
    return 1;
}
