#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

int my_atoi(char* str);
int my_strlen(char *s);
void my_strcpy(char *s1, char *s2);
void my_strcat(char *s1, char *s2);
void my_special_concat(char **to, char *from);
int find_new_line_index(char *str);
int min(int a, int b, int c);
void line_by_line(char *str);

#endif
