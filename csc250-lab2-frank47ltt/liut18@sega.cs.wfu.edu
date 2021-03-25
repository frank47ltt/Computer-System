/**
 * This program reads a text file and prints the top 5 most frequent letters (upper or lower case)
 * and the top 5 most frequent digits that are in the file. If the file has less than 5 unique letters
 * and/or digits the top list is adjusted accordingly. The file name is provided using command line 
 * arguments. If the file name is not provided or the file is not readable, the program will exit
 * and provide an error message.
 *
 * @author Frank Liu {liut18@wfu.edu>}
 * @date Sept. 20, 2020
 * @assignment Lab 2
 * @course CSC 250
 **/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_SIZE 20
#define MAX_LIST_SIZE 100

/* a useful struct, if you choose to use it */  
struct Char_Freq {
    char ch;
    int count;
};

/* function declarations go here */
void processFile(FILE *filePointer);
void bubbleSort(struct Char_Freq list[], int endSize, int startIndex);

int main(int argc, char* argv[]){
    FILE *fp;
    if(argc < 2){
        printf("Usage: %s filename \n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    /*check to see if file exist and successfully opened */
    if (fp == NULL){
        puts("Cannot open the file successfully! File does not exist!");
        return -1;
    }
    /* call function to process file and print out the result */
    processFile(fp);
    fclose(fp);
    return 0;
}

void processFile (FILE *filePointer){
    char temp;
    int i;
    int num;
    int numOfChar = 0;  /* keep track of numbers of different chars or digits (maybe less than 5) */
    int numOfDig = 0;
    struct Char_Freq tempNumStr[10];   /* struct that sort the numbers */
    struct Char_Freq arrOfChar[36];
    /* ready to process the character */
    /* initialize the struct accordingly */
    for(i = 0; i < 26; i++){
        arrOfChar[i].ch = (char)(97 + i);
        arrOfChar[i].count = 0;
    }
    for(i = 26; i < 36; i++){
        arrOfChar[i].ch = (char)(22+i);
        arrOfChar[i].count = 0;
    }
    while(1){
        /* read each character from the file until reach the end*/
        temp = fgetc(filePointer);
        /* convert from upper case to lower case */
        if (temp >= 'A' && temp <= 'Z'){
            temp = temp + 32;
        }
        for (i = 0; i < 36; i++){
            if(isdigit(temp)){
                num = num * 10 + temp - '0';
                if (num == arrOfChar[i].ch){
                    arrOfChar[i].count++;
                }
            }
            if (temp == arrOfChar[i].ch){
                arrOfChar[i].count++;
            }
        }
        if (temp == EOF){
            break;
            /* break out the loop when reach the end*/
        }
    }
    /* keep track of number of different characters or digits appeared */
    for (i = 0; i < 26; i++){
        if(arrOfChar[i].count > 0){
            numOfChar ++;
        }
    }
    if (numOfChar >=5){
        numOfChar = 5;
    }
    for (i = 26; i < 36; i++){
        if(arrOfChar[i].count > 0){
            numOfDig ++;
        }
    }
    if (numOfDig >=5){
        numOfDig = 5;
    }
    /* use bubblesort to sort the struct and print out the top 5 (or less) */
    bubbleSort(arrOfChar,26,0);
    /* I copy the original struck from index 26 - 36 (the digits part) to a temp struct and sort it
    * since I try to sort the substruct of original struct but it doesn't work that way */
    for (i = 0; i < 10; i++){
        tempNumStr[i] = arrOfChar[i+26];
    }
    bubbleSort(tempNumStr,10,0);
    /* print the results */
    if (numOfChar == 0){
        printf("\n No characters were found! \n");
    }
    else{
        printf("\n alpha top %d out of 26 \n", numOfChar);
        printf("---------------------- \n");
        for (i = 0; i < numOfChar; i++){
            printf("[%c] %d \n",arrOfChar[i].ch, arrOfChar[i].count);
        }
    }
    if (numOfDig == 0){
        printf("\n No digits were found! \n");
    }
    else{
        printf("\n digit top %d out of 10 \n", numOfDig);
        printf("---------------------- \n");
        for (i = 0; i < numOfDig; i++){
            printf("[%c] %d \n",tempNumStr[i].ch, tempNumStr[i].count);
        }
    }
}
/* implementation of bubblesort */
void bubbleSort(struct Char_Freq list[], int endSize, int startIndex){
    struct Char_Freq temp;
    int i, j;
    
    for (i = startIndex; i < endSize - 1; i++){
        for (j = startIndex; j < (endSize -1 - i); j++){
            if (list[j].count < list[j + 1].count){
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            } 
        }
    }
}
