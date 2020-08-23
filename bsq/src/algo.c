#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

void my_matrix_print(int lines, char *arr[]){
    for(int i = 0; i < lines; i++){
        printf("%s\n", arr[i]);
    }
}

void free_matrix(int lines, char *arr[]){
    for(int i = 0; i < lines; i++){
        free(arr[i]);
    }
}

int findBiggestSquare(int lines, int columns, char *arr[lines]){

    int found_x = -1, found_y = -1;
    int **bitField = malloc(sizeof(int*)*(lines));
    int maxSquare = 0;
    for(int i = 0; i < lines; i++){
        bitField[i] = malloc(sizeof(int)*(columns));
        for(int j = 0; j < columns; j++){
            if(i == 0 ){
                if(arr[i][j] == '.'){
                    bitField[i][j] = 1;
                    if(maxSquare <= bitField[i][j]){
                        maxSquare = bitField[i][j];
                        found_x = i;
                        found_y = j;
                    }
                }else{
                    bitField[i][j] = 0;
                }
            }else{
                if(j == 0){
                    if(arr[i][j] == '.'){
                        bitField[i][j] = 1;
                        if(maxSquare <= bitField[i][j]){
                            maxSquare = bitField[i][j];
                            found_x = i;
                            found_y = j;
                        }
                    }else{
                        bitField[i][j] = 0;
                    }
                }else{
                    if(arr[i][j] == '.'){
                        bitField[i][j] = 1 + min(bitField[i-1][j-1], bitField[i-1][j], bitField[i][j-1]);
                        if(maxSquare <= bitField[i][j]){
                            maxSquare = bitField[i][j];
                            found_x = i;
                            found_y = j;
                        }
                    }else{
                        bitField[i][j] = 0;
                    }
                }
            }
        }
        if(i > 0){
            free(bitField[i-1]);
        }
    }

    free(bitField[columns-1]);
    free(bitField);

    printf("found x and y: %d %d\n", found_x, found_y);
    for(int i = found_x; i > found_x - maxSquare; i--)
    {
        for(int j = found_y; j > found_y - maxSquare; j--)
        {
            arr[i][j] = 'X';
        }
    }

    return maxSquare;
}
