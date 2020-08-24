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

void myMatrixPrint(int lines, char *arr[]){
    for(int i = 0; i < lines; i++){
        printf("%s\n", arr[i]);
    }
}

void freeMatrix(int lines, char *arr[]){
    for(int i = 0; i < lines; i++){
        free(arr[i]);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Algorithm: https://github.com/mission-peace/interview/blob/master/src/com/interview/dynamic/MaximumSizeSubMatrix.java /////////////////
//  Video Explanation: https://www.youtube.com/watch?v=_Lf1looyJMU                                                        /////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int findBiggestSquare(int lines, int columns, int *bitField){

    int found_x = -1, found_y = -1;

    // These two arrays are for storing the row of current i-index(vertical) and row above of current (i-1)-index row,
    // because to calculate the minimum value for current cell (arr i j = min(arr i-1 j-1, arr i j-1, arr i-1 j) + 1) one need only current row and the above one not the whole 2d int array.

    int minValues1[columns];
    int minValues2[columns];

    // These two pointers to array are for swapping between two using if statement
    int *currentMinVal;
    int *aboveMinVal;

    int flag = 0;
    int maxSquareSize = 0;

    for(int i = 0; i < lines; i++){

        if(flag == 0){
            currentMinVal = minValues1;
            aboveMinVal = minValues2;
            flag = 1;
        }else{
            currentMinVal = minValues2;
            aboveMinVal = minValues1;
            flag = 0;
        }
        for(int j = 0; j < columns; j++){

            int bitIndex = i*columns + j;
            if(TestBit(bitField, bitIndex)){
                if(i == 0){
                    currentMinVal[j] = 1;
                }else{
                    if(j == 0){
                        currentMinVal[j] = 1;
                    }else{
                        currentMinVal[j] = 1 + min(aboveMinVal[j-1], aboveMinVal[j], currentMinVal[j-1]);
                    }
                }

                if(maxSquareSize <= currentMinVal[j]){
                    maxSquareSize = currentMinVal[j];
                    found_x = i;
                    found_y = j;
                }
            }else{
                currentMinVal[j] = 0;
            }
        }
    }
    printf("found x and y: %d %d\n", found_x, found_y);


    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            int test = i*columns + j;
            if(TestBit(bitField, test)){
                if(i <= found_x && i > found_x - maxSquareSize && j <= found_y && j > found_y - maxSquareSize){
                    printf("X");
                }else{
                    printf(".");
                }
            }else{
                printf("o");
            }

        }
        printf("\n");
    }

    return maxSquareSize;
}

