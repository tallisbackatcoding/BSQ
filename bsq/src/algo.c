#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

#define SetBit(A,k)   ( A[(k/32)] |= (1 << (k%32)) )
#define ClearBit(A,k) ( A[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(A,k)  ( A[(k/32)] & (1 << (k%32)) )

int* getNewBitField(int size){
    int array_size = size/32 + 1;
    int *BitField = malloc(sizeof(int)*array_size);
    printf("array size %d \n", array_size);
    return BitField;
}

void copyToBitFieldFromStr(int *bitField, char *str, int strSize, int index){
    for(int i = 0; i < strSize; i++){
        int k = index+i;
        if(str[i] == '.'){
            SetBit(bitField, k);
        }
        else if(str[i] == 'o'){
            ClearBit(bitField, k);
        }
    }
}

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

int findBiggestSquare(int lines, int columns, int *bitField){

    int found_x = -1, found_y = -1;
    int **minValues = malloc(sizeof(int*)*(lines));
    int maxSquare = 0;
    for(int i = 0; i < lines; i++){
        minValues[i] = malloc(sizeof(int)*(columns));
        for(int j = 0; j < columns; j++){
            if(i == 0 ){
                int test = i*columns + j;
                if(TestBit(bitField, test)){
                    minValues[i][j] = 1;
                    if(maxSquare <= minValues[i][j]){
                        maxSquare = minValues[i][j];
                        found_x = i;
                        found_y = j;
                    }
                }else{
                    minValues[i][j] = 0;
                }
            }else{
                if(j == 0){
                    int test = i*columns + j;
                    if(TestBit(bitField, test)){
                        minValues[i][j] = 1;
                        if(maxSquare <= minValues[i][j]){
                            maxSquare = minValues[i][j];
                            found_x = i;
                            found_y = j;
                        }
                    }else{
                        minValues[i][j] = 0;
                    }
                }else{
                    int test = i*columns + j;
                    if(TestBit(bitField, test)){
                        minValues[i][j] = 1 + min(minValues[i-1][j-1], minValues[i-1][j], minValues[i][j-1]);
                        if(maxSquare <= minValues[i][j]){
                            maxSquare = minValues[i][j];
                            found_x = i;
                            found_y = j;
                        }
                    }else{
                        minValues[i][j] = 0;
                    }
                }
            }
        }
        if(i > 0){
            free(minValues[i-1]);
        }
    }

    free(minValues[columns-1]);
    free(minValues);

    printf("found x and y: %d %d\n", found_x, found_y);
//    for(int i = found_x; i > found_x - maxSquare; i--)
//    {
//        for(int j = found_y; j > found_y - maxSquare; j--)
//        {
//            arr[i][j] = 'X';
//        }
//    }

    return maxSquare;
}
