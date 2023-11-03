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
    static int buff_size = 1048;
    char buff1[buff_size];
    char buff2[buff_size];

    log_init();
    _log(LOG_I, "Start\n");
    if (argc > 1){
        //input
        _log(LOG_I, "importing %s\n", argv[1]);
        imp_file(buff1, buff_size, argv[1]);
        printf(buff1);
    }
}