#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "my_readline.h"
#include "algo.h"


//delete after, time.h header
#include <time.h>

/////////////////////////////////////BITFIELD MACROS AND FUNCTIONS
/*
#define SetBit(A,k)   ( A[(k/32)] |= (1 << (k%32)) )
#define ClearBit(A,k) ( A[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(A,k)  ( A[(k/32)] & (1 << (k%32)) )

int* getNewBitField(int size){
    int array_size = size/32 + 1;
    int *BitField = malloc(sizeof(int)*array_size);
    return BitField;
}

void copyToBitFieldFromStr(int *bitField, char *str, int strSize, int index){
    for(int i = 0; i < strSize; i++){
        if(str[i] == '.'){
            SetBit(bitField, index+i);
        }else if(str[i] == 'o'){
            ClearBit(bitField, index+i);
        }
    }
}
*/
//////////////////////////////////////////////////////////////////

void bitFieldGenerator(int x, int y, int density /*from 0 to 99*/){
    time_t t;
    srand((unsigned) time(&t));
    FILE *f = fopen("a.txt", "w");
    fprintf(f, "%d\n", y);
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(rand()%100 > density){
                putc('.', f);
            }else{
                putc('o', f);
            }
        }
        putc('\n', f);
    }
    fclose(f);
}
int main(int argc, char *argv[]){

    if(argc < 2){
        printf("No input file!");
        return 0;
    }
    char *fileName = argv[1];
    int fd = open(fileName, O_RDONLY);


    bitFieldGenerator(10000, 10000, 2);


    char *charLine = my_readline(fd);
    int lines = my_atoi(charLine);
    free(charLine);

    charLine = my_readline(fd);
    int columns = my_strlen(charLine);
    charLine[columns] = '\0';
    printf("lines: %d, columns: %d\n", lines, columns);

    int *bitField = getNewBitField(columns*lines);
    copyToBitFieldFromStr(bitField, charLine, columns, 0);
    free(charLine);

    int bitsIndex = 0;
    bitsIndex += columns;
    while(charLine){

        charLine = my_readline(fd);
        if(!charLine){
            break;
        }
        charLine[columns] = '\0';
        copyToBitFieldFromStr(bitField, charLine, columns, bitsIndex);

        free(charLine);
        bitsIndex += columns;
    }

    printf("square size %d\n", findBiggestSquare(lines, columns, bitField));
    //my_matrix_print(lines, arr);

    close(fd);
    free(bitField);
}
/*
int main(int argc, char *argv[]){

    if(argc < 2){
        printf("No input file!");
        return 0;
    }
    char *fileName = argv[1];

    bitFieldGenerator(10000, 10000, 10);

    int fd = open(fileName, O_RDONLY);
    char *charLine = my_readline(fd);

    int lines = my_atoi(charLine);
    free(charLine);

    charLine = my_readline(fd);
    int columns = my_strlen(charLine);


    char *arr[lines];
    charLine[columns] = '\0';
    arr[0] = malloc(sizeof(char)*(columns+1));
    my_strcpy(arr[0], charLine);


    free(charLine);

    int i = 1;
    printf("lines: %d, columns: %d\n", lines, columns);
    while(charLine){

        charLine = my_readline(fd);

        if(!charLine){
            break;
        }
        arr[i] = malloc(sizeof(char)*(columns+1));
        charLine[columns] = '\0';
        my_strcpy(arr[i], charLine);

        free(charLine);
        i++;
    }

    printf("%d\n", findBiggestSquare(lines, columns, arr));
    //my_matrix_print(lines, arr);

    close(fd);
    free_matrix(lines, arr);
}
*/
