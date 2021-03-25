/**
 * @author Frank (Tongtong) Liu {liut18@wfu.edu}
 * @date Oct. 12, 2020
 * @assignment Lab 4
 * @course CSC 250
 *
 * This program will use command line arguments for a key to encrypt/decrypt the file, the filename, and a flag
 * that indicates either decrypt or encrypt. It reads a text file, use a key to encrypt the characters in the file 
 * using bitwise operation (XOR), and decrypt the file back using the same key.
 **/   

#include "get_args.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_SIZE 20


/* function declarations go here */
void encryption(FILE *filepointer, int key, char filename[20]);
void decryption(FILE *filepointer, int key, char filename[20]);

int main(int argc, char* argv[]){
    FILE *fp;
    /* int args_ok; */
    int enc;
    int key;
    char filename[20];

    /* you need to change enc and key from command line */
    /* args_ok = process_args(argc, argv, &enc, &key, filename); */
    /*
    if (args_ok) {
        printf("enc %d, key %d, filename %s \n", enc, key, filename);
    }
    */
    process_args(argc, argv, &enc, &key, filename);

    /* not sufficient number of arguments provided */
    if(argc < 5) {
        printf("Usage: %s filename \n", argv[0]);
        return 1;
    }

    fp = fopen(filename, "r");
    /*check to see if file exist and successfully opened */
    if (fp == NULL) {
        puts("Cannot open the file successfully! File does not exist!");
        return 1;
    }
    if(enc == 1) { /* true, encryption */
        encryption(fp, key, filename);
    }
    else { /*false, do decryption */
        decryption(fp, key, filename);
    }
    fclose(fp);
    return 0;
}
/**
 *  This function will be called when command line argument includes flag -e.
 *  Specifically this will read 4 chars at a time and encrypted them into a 32 bits
 *  integer, and print it to the encrypted file.
 *  @Parameters:
 *     FILE *filepointer: pointer to input file
 *     int key: encrypted key
 *     char filename[20]: filename of input file. Use to concat .enc for output file
 */
void encryption(FILE *filepointer, int key, char filename[20]){
    char tmp;
    char content[4];
    int counter;
    unsigned int result;
    char encNull = (unsigned int)'\0' ^ (unsigned int)key ;
    int numChars = 0;
    char filenameHolder[20];
    FILE *fpw;
    strncpy(filenameHolder, filename, strlen(filenameHolder));  /* store the filename before concat for the print out statements */
    strncat(filename,".enc",strlen(filename));
    fpw = fopen(filename,"w");
    if (fpw == NULL) {
       puts("Output file cannot be opened");
    }
    tmp = fgetc(filepointer);
    counter = 0;
    while (tmp != EOF) {
        if (counter != 4) {
            /* encrypt with key and store 4 chars to an array */
            tmp = (unsigned int)tmp ^ (unsigned int)key;
            content[counter] = tmp;
        }
        counter ++;
        if (counter == 4) {
            /* assembly 4 chars to an int when array is full and reset varaibles */
            counter = 0;
            result = 0;
            result = (((unsigned int) content[0]) << 24u) | result;
            result = (((unsigned int) content[1]) << 16u) | result;
            result = (((unsigned int) content[2]) << 8u) | result;
            result = ((unsigned int) content[3]) | result;
            /*
            result |= content[0] << 24u;
            result |= content[1] << 16u;
            result |= content[2] << 8u;
            result |= content[3];
            */
            /* print to the output file */
            fprintf(fpw, "%d \n", result);
        }
        numChars++;
        tmp = fgetc(filepointer);
    }
    /* if the array is not full, append encrypted null to make it full */
    if (counter > 0 && counter < 4) {
        while (counter > 0 && counter < 4) {
        content[counter] = encNull;
        counter ++;
        }
        result = 0;
        result = (((unsigned int) content[0]) << 24u) | result;
        result = (((unsigned int) content[1]) << 16u) | result;
        result = (((unsigned int) content[2]) << 8u) | result;
        result = ((unsigned int) content[3]) | result;
        /*
        result |= content[0] << 24u;
        result |= content[1] << 16u;
        result |= content[2] << 8u;
        result |= content[3];
        */
        fprintf(fpw, "%d \n", result);
    }
    printf("encrypted %d characters in %s \n", numChars, filenameHolder);
    printf("encrypted file is %s \n", filename);
}
/**
 *  This function will be called when command line argument includes flag -d.
 *  Specifically this will split the integer back to 4 decrypted chars and print
 *  them back to the decrypted file
 *  @Parameters:
 *     FILE *filepointer: pointer to input file
 *     int key: encrypted key
 *     char filename[20]: filename of input file. Use to concat .dec for output file
 */
void decryption(FILE *filepointer, int key, char filename[20]){
    char content[4];
    unsigned int toBeDec;
    char tmpHolder[20];
    int i;
    int numOfChar = 0;
    FILE *fpw;
    char filenameHolder[20];
    strncpy(filenameHolder, filename, strlen(filenameHolder)); /* store the filename before concat for the print out statements */
    strncat(filename,".dec", strlen(filename));
    fpw = fopen(filename,"w");
    if (fpw == NULL) {
       puts("Output file cannot be opened");
    }
    /* read an int per time */
    fscanf(filepointer, "%s", tmpHolder);
    toBeDec = (unsigned int)strtoul(tmpHolder,NULL, 10);
    /* scan in as a string and then convert it to a ui */
    while (!feof (filepointer)) {
        /* process the int into 4 chars */
        content[0] = (((toBeDec >> 24u) & 0xffu) ^ (unsigned int)key);
        content[1] = (((toBeDec >> 16u) & 0xffu) ^ (unsigned int)key);
        content[2] = (((toBeDec >> 8u) & 0xffu) ^ (unsigned int)key);
        content[3] = ((toBeDec & 0xffu) ^ (unsigned int)key);
        fscanf(filepointer, "%s", tmpHolder);
        toBeDec = (unsigned int)strtoul(tmpHolder,NULL, 10);
        for(i = 0; i < 4; i ++) {
            if (content[i] != '\0') {
                fputc(content[i], fpw);
                numOfChar ++;
            }
        }

    }
    printf("decrypted %d characters in %s \n", numOfChar, filenameHolder);
    printf("decrypted file is %s \n", filename);
    fclose(fpw);
}