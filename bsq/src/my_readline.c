#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READLINE_READ_SIZE 512

static char left_over[READLINE_READ_SIZE];


char *my_readline(int fd){
    if(fd < 0){
        return NULL;
    }
    int length = -1;
    char *buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char));

    if(left_over[0] == 0){
        length = read(fd, buffer, READLINE_READ_SIZE);
        if(length == -1 || length == 0){
            free(buffer);
            return NULL;
        }
        buffer[length] = 0;
    }else{
        //if there is something in left_over I copy from it to buffer and then read
        my_strcpy(buffer, left_over);
        int rem_chars = READLINE_READ_SIZE - my_strlen(buffer);
        char remaining_chars[rem_chars];
        int end = read(fd, remaining_chars, rem_chars);
        remaining_chars[end] = 0;
        my_strcat(buffer, remaining_chars);
    }

    int new_line_index = find_new_line_index(buffer);

    if(new_line_index != -1)
        buffer[new_line_index] = 0;
    int i;


    //if new line was found we copy chars after new_line to left_over[] array
    if(new_line_index != -1){
        new_line_index++;
        for(i = 0; buffer[i + new_line_index]; i++){
            left_over[i] = buffer[i + new_line_index];
        }
        left_over[i] = 0;

    }else{
        //if it wasn't found we read from fd untill we find is new_line or end of file
        left_over[0] = 0;
        char temp[READLINE_READ_SIZE];
        while(1){
            int stop = read(fd, temp, READLINE_READ_SIZE);
            temp[stop] = 0;
            my_special_concat(&buffer, temp);
            new_line_index = find_new_line_index(temp);
            if(new_line_index != -1 || !stop){
                break;
            }
        }
        //and if it was found we copy to left_over again
        if(new_line_index -= -1){
            for(i = 0; temp[i + new_line_index]; i++){
                left_over[i] = temp[i+new_line_index];
            }
            left_over[i] = 0;
        }

    }
    return buffer;
}
