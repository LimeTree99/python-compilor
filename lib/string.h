#include "imports.h"

/*
a library for manipulating strings
*/


typedef struct String{
    int size;
    char *string;
}String;

String *string(char *string, ...);
void print(String *str);
void printl(String *str);
int str_len(String *str);
void str_cat(String *str1, String *str2);
String *str_cp(String *str);
void str_free(String *str);