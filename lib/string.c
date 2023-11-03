#include "string.h"

String *string(char *string, ...){
    va_list args;
    String *str = malloc(sizeof(String));

    va_start(args, string);

    //this is not the real size. the function overcompensates
    str->size = snprintf(NULL, 0, string, args); 
    str->string = malloc(sizeof(char) * (str->size + 1) );
    //this is the real size. only does the correct size if it has something to write to 
    str->size = vsnprintf(str->string, str->size + 1, string, args);
    
    va_end(args);
    return str;
}

void print(String *str){
    printf(str->string);
}
void printl(String *str){
    printf(str->string);
    printf("\n");
}

//return int Length of String *str not including NULL term.
int str_len(String *str){
    return str->size;
}

//append String *str1 with String *str2
void str_cat(String *str1, String *str2){
    char *new = malloc(sizeof(char) * (str1->size + str2->size + 1));
    
    for (int i=0; i<str1->size; i++){
        *(new + i) = *(str1->string + i);
    }

    for (int i=0; i<str2->size; i++){
        *(new + str1->size + i) = *(str2->string + i);
    }

    *(new + str1->size + str2->size) = '\0';

    free(str1->string);
    str1->string = new;   
    str1->size += str2->size; 
}

void str_free(String *str){
    free(str->string);
    free(str);
}
