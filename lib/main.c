#include "regex.h"

/*
order:
    main
    regex
    log
    string
    imports
*/




void lex(){

}

void tokenize(){

}

void imp_file(char *buff, int size, char file_name[]){
    FILE *fh;
    fh = fopen(file_name, "r");
    
    if (fh){
        fgets(buff, size, fh);
        pclose(fh);
    }else if (fh == NULL){
        //there was an error
        printf("err\n");
    }
}

int main(int argc, char *argv[]){
    log_init();
    String *a = string("number %d", 1);
    String *b = string("letter %c", 'a');
    str_cat(a, string("-"));
    str_cat(a, b);
    printl(a);
}