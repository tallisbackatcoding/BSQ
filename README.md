# Qwant my_bsq project

> my bsq will maybe beat yours

---

## Table of Contents

- [How to run](#run)
- [Dynammic Programming](#DynamicProgramming)
- [Bitfields](#Bitfields)
- [Tests](#tests)
- [Team](#team)


---
## run
```shell
$ make
$ ./bsq [input_file.txt]
```

---

## DynamicProgramming

- to prevent memory stackoverflow we just free the row that already been used

```c

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
```

---


## Bitfields

- using macros created integer data structure that holds bits

```c
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
```
---
## tests

- testing with 1k x 1k matrix and density -1

![test1](imgs/test2.png)

- testing with 10k x 10k matrix and density 10

![test1](imgs/test1.png)

---

## Team

> Contributors

<p>Nursultan Altayev</p>

<img src="imgs/nurs.jpg">

<p>Yerzhan Tolysbekk</p>

<img src="imgs/erj.jpg">

---
