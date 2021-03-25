/**
 * @author Frank (Tongtong) Liu {liut18@wfu.edu}
 * @date Oct. 6, 2020
 * @assignment Lab 3
 * @course CSC 250
 *
 * This program reads a text file and prints the words and it's corresponding freqency to another file. 
 * The word frequencies are sorted in descending order . The two file names are provided using command line 
 * arguments. If the file names are not provided or not enough or the file is not readable, the program will exit
 * and provide an error message. This program applies knowledge of pointers and dynamic allocations.
 **/   

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_SIZE 20

/* a useful struct, if you choose to use it */  
struct WordFreq {
    char* word;
    int count;
};

/* function declarations go here */
bool searchWord(char tmpString[MAX_STRING_SIZE], struct WordFreq** pointerToList, const int *num);
void addToStruct(char tmpString[MAX_STRING_SIZE], struct WordFreq** pointerToList, int *num);
void processFile(FILE *filePointer, struct WordFreq** pointerToList, int *num);
void writeToFile(const char* fileName, struct WordFreq** pointerToList, const int *num);
void bubbleSort(struct WordFreq** pointerToList, const int *num);

int main(int argc, char* argv[]){
    FILE *fp;
    int *num;   /* pointers to number of pointers */
    int numPtr = 0;
    struct WordFreq *stringFreq = 0;
    struct WordFreq **pointerToList = &stringFreq; /* double pointer point to the struct pointer */
    int i;
    num = &numPtr;
    /* not sufficient number of arguments provided */
    if(argc < 3) {
        printf("Usage: %s filename \n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    /*check to see if file exist and successfully opened */
    if (fp == NULL) {
        puts("Cannot open the file successfully! File does not exist!");
        return 1;
    }
    /* call function to process file and print out the result */
    processFile(fp, pointerToList, num);
    printf("%s has %d unique words \n", argv[1], *num);
    bubbleSort(pointerToList, num);
    writeToFile(argv[2], pointerToList, num);
    fclose(fp);
    /* free any dynamically allocated memory to prevent segmentation fault */
    if (*pointerToList) {
        for(i = 0; i < numPtr; i++) {
            if((*pointerToList)[i].word) {
                free((*pointerToList)[i].word);
            }
        }
        free(*pointerToList);
    }
    return 0;
}

/**
 *  This function will search the struct and compare elements in the struct char* variable with c-string array.
 *  Return a bool value indicates whether the string is found in the struct
 *  @Parameters:
 *     char tmpString[MAX_STRING_SIZE]: a temporary array holds for a string found in the file
 *     struct WordFreq ** pointerToList: a pointer to the struct pointer
 *     int *num: a pointer to the number of pointers of the struct
 */
bool searchWord(char tmpString[MAX_STRING_SIZE], struct WordFreq ** pointerToList, const int *num){
    bool isFind = 0;
    int j;
    for (j = 0; j < *num; j++) {
        /* compare temString with elements in struct */
        if (strcmp(tmpString, (*pointerToList)[j].word) == 0) { 
            (*pointerToList)[j].count++;
            isFind = 1; /*true*/
        }
    }
    return isFind;
}

/**
 *  This function will add the string to the struct and set the counter to 1.
 *  It will allocate memory that have a larger size, copy the old struct to the new one
 *  and append the string to it.
 *  @Parameters:
 *     char tmpString[MAX_STRING_SIZE]: a temporary array holds for a string found in the file
 *     struct WordFreq ** pointerToList: a pointer to the struct pointer
 *     int *num: a pointer to the number of pointers of the struct
 */
void addToStruct(char tmpString[MAX_STRING_SIZE], struct WordFreq** pointerToList, int *num){
    /* allocate tmpStruct with memory have one more space for struct */
    struct WordFreq *tmpStruct;
    tmpStruct = malloc(sizeof(struct WordFreq) * (*num + 1));
    if (*num > 0) {
        /* copy the content of that memory pointers pointing to */
        memcpy(tmpStruct, *pointerToList, sizeof(struct WordFreq) * (*num));
    }
    tmpStruct[*num].word = malloc(strlen(tmpString) + 1);
    strncpy(tmpStruct[*num].word, tmpString, strlen(tmpString) + 1);
    tmpStruct[*num].count = 1;
    *num = *num + 1;
    /* free pointers and let the pointer point to the tmp */
    if (*pointerToList) {
        free(*pointerToList);
    }
    *pointerToList = tmpStruct;
}

/**
 *  This function will write the sorted struct to an output file
 *  @Parameters:
 *     const char* fileName: provided from command line arguments, a file name.
 *     struct WordFreq ** pointerToList: a pointer to the struct pointer
 *     int *num: a pointer to the number of pointers of the struct
 */
void writeToFile(const char* fileName, struct WordFreq** pointerToList, const int *num){
    FILE *fpw;
    int i;
    fpw = fopen(fileName,"w");
    if (fpw == NULL) {
       puts("Output file cannot be opened");
    }
    
    for (i = 0; i < *num; i++) {
        /* write content of struct to file */
        fputs((*pointerToList)[i].word, fpw);
        fprintf(fpw, " %d", (*pointerToList)[i].count);
        fputs("\n", fpw);      
    }
    fclose(fpw);
}
/**
 *  This function will read each char from the file and put them as string when non-char is encountered.
 *  Process the file by calling other functions.
 *  @Parameters:
 *     FILE *filePointer: an input file pointer.
 *     struct WordFreq ** pointerToList: a pointer to the struct pointer
 *     int *num: a pointer to the number of pointers of the struct
 */
void processFile (FILE *filePointer, struct WordFreq** pointerToList, int *num){
    char tmp;
    char tmpString[MAX_STRING_SIZE];
    int i = 0;  /* keep track of number of char in a string */
    int j;
    bool isFind;
    tmp = fgetc(filePointer);

    /* read until the end of the file */
    while(tmp != EOF) {
        /* do something to tmp */
        if(((tmp >='a' && tmp <='z') || (tmp >='A' && tmp<='Z')) && (i < 20)) {
            /* convert capital letters to lower case */
            if (tmp >= 'A' && tmp <= 'Z') {
                tmp = tmp + 32;
            }
            tmpString[i] =tmp;
            i++;
        }
        else if(i > 0) {
            /* if there is char in the string and encounter word delimiter */
            tmpString[i] = '\0';
            i = 0;
            isFind = searchWord(tmpString, pointerToList, num);
            if(isFind == 0) { /* not find */
                addToStruct(tmpString, pointerToList, num);
            }
            /* clear the tmp array */
            for(j=0; j<MAX_STRING_SIZE; j++) {
                tmpString[j] = '\0';
            }
        }
        tmp = fgetc(filePointer);
    }
}

/**
 *  This function will implement bubble sort to sort the struct by their counter
 *  @Parameters:
 *     struct WordFreq ** pointerToList: a pointer to the struct pointer
 *     int *num: a pointer to the number of pointers of the struct
 */
void bubbleSort(struct WordFreq** pointerToList, const int *num){
    struct WordFreq *tmpStruct = malloc(sizeof(struct WordFreq));
    int i, j;
    
    for (i = 0; i < *num - 1; i++) {
        for (j = 0; j < (*num -1 - i); j++){
            if ((*pointerToList)[j].count < (*pointerToList)[j + 1].count) {
                *tmpStruct = (*pointerToList)[j];
                (*pointerToList)[j] = (*pointerToList)[j + 1];
                (*pointerToList)[j + 1] = *tmpStruct;
            } 
        }
    }
    free(tmpStruct);
}