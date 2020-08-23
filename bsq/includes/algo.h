#ifndef ALGO_H_INCLUDED
#define ALGO_H_INCLUDED

int* getNewBitField(int size);

void copyToBitFieldFromStr(int *bitField, char *str, int strSize, int index);

void my_matrix_print(int lines, char *arr[]);

void free_matrix(int lines, char *arr[]);

int findBiggestSquare(int lines, int columns, int *bitField);


#endif
