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


    bitFieldGenerator(10, 10, 2);

    char *charLine = my_readline(fd);
    int lines = my_atoi(charLine);
    free(charLine);

    charLine = my_readline(fd);
    int columns = my_strlen(charLine);
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
        copyToBitFieldFromStr(bitField, charLine, columns, bitsIndex);

        free(charLine);
        bitsIndex += columns;
    }

    printf("square size %d\n", findBiggestSquare(lines, columns, bitField));

    close(fd);
    free(bitField);
}

