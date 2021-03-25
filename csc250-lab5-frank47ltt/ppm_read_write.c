/**
 * @author Nirre Pluf {@literal pluf@wfu.edu}
 * @date Oct. 11, 2020
 * @assignment Lab 5
 * @course CSC 250
 *
 * functions for reading and writing PPM files
 **/

#include "ppm_read_write.h"


/**
 *  reads PPM image data and returns information in ia list of Image structs
 *
 *  img - pointer to a dynamic list of Image structs (data from PPM file)
 *  file_name - C-string, name of the PPM file
 *
 *  returns 1 if successful, 0 otherwise
 */
int read_image(struct Image **img, char file_name[])
{
    char buffer[16];     /* buffer used to read data from file */
    FILE *file_ptr;      /* PPM file pointer */
    int ch;              /* temporary character (byte) read from file */
    int rgb_comp_color;  /* component color */  

    /* open PPM file for reading */
    file_ptr = fopen(file_name, "rb");
    if(!file_ptr) {
        fprintf(stderr, "Unable to open file '%s'\n", file_name);
        return 0;
    }

    /* read image format */
    if(!fgets(buffer, sizeof(buffer), file_ptr)) {
        perror(file_name);
        return 0;
    }

    /* check the image format */
    if(buffer[0] != 'P' || buffer[1] != '6') {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        return 0;
    }

    /* alloc memory form image */
    (*img) = (struct Image *) malloc(sizeof(struct Image));
    if(!(*img)) {
        fprintf(stderr, "Unable to allocate memory\n");
        return 0;
    }

    /* check for comments */
    ch = getc(file_ptr);
    while(ch == '#') {
        while(getc(file_ptr) != '\n')
            ;
        ch = getc(file_ptr);
    }

    ungetc(ch, file_ptr);
    /* read image size information */
    if(fscanf(file_ptr, "%d %d", &((*img)->width), &((*img)->height)) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", file_name);
        return 0;
    }

    /* read rgb component */
    if(fscanf(file_ptr, "%d", &rgb_comp_color) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n",
                file_name);
        return 0;
    }

    /* check rgb component depth */
    if(rgb_comp_color != RGB_COMPONENT_COLOR) {
        fprintf(stderr, "'%s' does not have 8-bits components\n", file_name);
        return 0;
    }

    while(fgetc(file_ptr) != '\n')
        ;
    /* memory allocation for pixel data */
    (*img)->data = (struct Pixel *) malloc((*img)->width * (*img)->height * sizeof(struct Pixel));

    if(!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        return 0;
    }

    /* read pixel data from file */
    if(fread((*img)->data, 3 * (*img)->width, (*img)->height, file_ptr) != (*img)->height) {
        fprintf(stderr, "Error loading image '%s'\n", file_name);
        return 0;
    }

    fclose(file_ptr);
    return 1;
}


/**
 *  write PPM image data to a file (destructive)
 *
 *  file_name - C-string, name of the PPM file
 *  img - pointer to a list of Image structs (data for PPM image)
 *
 *  returns 1 is successful, 0 otherwise
 */
int write_image(char file_name[], struct Image *img)
{
    FILE *file_ptr;  /* pointer to the PPM file */

    /* open file for output */
    file_ptr = fopen(file_name, "wb");
    if(!file_ptr) {
        fprintf(stderr, "Unable to open file '%s'\n", file_name);
        return 0;
    }

    /* write the header file image format */
    fprintf(file_ptr, "P6\n");

    /* comments */
    fprintf(file_ptr, "# try http://goo.gl/rxnHB1 shhhhhhhhhh it's a secret \n");

    /* image size */
    fprintf(file_ptr, "%d %d\n", img->width, img->height);

    /* rgb component depth */
    fprintf(file_ptr, "%d\n", RGB_COMPONENT_COLOR);

    /* pixel data */
    fwrite(img->data, 3 * img->width, img->height, file_ptr);
    fclose(file_ptr);

    return 0;
}


/**
 * folloing functions are not needed, just changing-up the pixels for phum
 */

void changeColor(struct Image *img)
{
    int i;
    if(img) {
        for(i = 0; i < img->width * img->height; i++) {
            img->data[i].red = RGB_COMPONENT_COLOR - img->data[i].red;
            img->data[i].green = RGB_COMPONENT_COLOR - img->data[i].green;
            img->data[i].blue = RGB_COMPONENT_COLOR - img->data[i].blue;
        }
    }
}


void rgbPixels(struct Image *img)
{
    int i;
    int n;
    if(img) {
        for(i = 0; i < img->width * img->height; i++) {
            img->data[i].red = img->data[i].green = img->data[i].blue = 0x0;
            n = i%3;
            if(n == 0)
                img->data[i].red = 0xff;
            else if(n == 1)
                img->data[i].green = 0xff;
            else
                img->data[i].blue = 0xff;
        }
    }
}


