#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int my_atoi(char* str){

    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i){
        if(str[i] == 13 || str[i] == 10){
            break;
        }
        result = result * 10 + str[i] - '0';
    }

    return sign * result;
}

int my_strlen(char *s)
{
    int i = 0;
    while(s[i]){
        i++;
    }
    return i;
}
void my_strcpy(char *s1, char *s2)
{
    int i;
    for(i = 0; s2[i]; i++){
        s1[i] = s2[i];
    }
    s1[i] = 0;
}
void my_strcat(char *s1, char *s2)
{
    int i = 0;
    while(s1[i])
        i++;
    int j = 0;
    while(s2[j]){
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = s2[j];
}

void my_special_concat(char **to, char *from){
    int size1 = my_strlen(*to);
    int size2 = my_strlen(from);
    if(size2 == 0 || size1 == 0){
        return;
    }
    char temp[size1+1];
    my_strcpy(temp, *to);
    *to = (char *)realloc(*to, (size1 + size2 + 1));
    my_strcpy(*to, temp);
    int i;
    for(i = 0; from[i] != '\n' && from[i] != 0; i++){
        (*to)[size1+i] = from[i];
    }
    (*to)[size1 + i] = 0;
}

int find_new_line_index(char *str){
    for(int i = 0; str[i]; i++){
        if(str[i] == '\n'){
            return i;
        }
    }
    return -1;
}
int min(int a, int b, int c){
    if(a <= b && a <= c){
        return a;
    }
    if(c <= b && c <= a){
        return c;
    }
    return b;
}

void line_by_line(char *str){
    for(int i = 0; str[i] != 0; i++){
        printf("%d th: :%c: or :%d:\n", i, str[i], str[i]);
    }
}
