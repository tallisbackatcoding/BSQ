#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED

int* getNewBitField(int size);

void copyToBitFieldFromStr(int *bitField, char *str, int strSize, int index);

void myMatrixPrint(int lines, char *arr[]);

void freeMatrix(int lines, char *arr[]);

int findBiggestSquare(int lines, int columns, int *bitField);


#endif
