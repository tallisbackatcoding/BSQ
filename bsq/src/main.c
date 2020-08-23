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
            if(rand()%100 > -1){
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
