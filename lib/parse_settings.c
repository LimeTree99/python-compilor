#include "parse_settings.h"

/*

***dataframe->columns ->   **c1      c2      c3
                            |       |       |
                            *item
                            |
                            *item

*/

//! if cur in the string delin return true
#define instr(c,str) memchr(str,(int)c,str##_size)

int fnum_lines(FILE *fh);



datafrm *imp_testf(char file_name[], const char *delin){
    /*
    complexity: 
    */
    FILE *fh;
    fpos_t pos;
    int buff_size = 1024;
    char *buff = (char*)malloc(sizeof(char) * buff_size);
    char prev = -1;
    char cur = -1;
    
    int word_size = 0;
    char *word_cur;
    int column = -1;
    int row;
    
    int delin_size = strlen(delin);
    datafrm *re = (datafrm*)malloc(sizeof(datafrm));
    
    re->width = 0;
    re->height = 0;
    
    fh = fopen(file_name, "r");
    
    if (fh){
        re->height = fnum_lines(fh) - 1;    //O(n)
        
        //get the number of columns 
        do{
            prev = cur;
            cur = fgetc(fh);
            if (instr(cur, delin) && !instr(prev, delin)){
                    re->width++;
                }
        }while(cur != '\n');
        
        if (!memchr(delin, prev, delin_size)){
            re->width++;
        }        
        
        //set the memory size and fill re->names
        rewind(fh);
        re->names = (char**)malloc(sizeof(char*) * re->width);
        column = 0;
        do{
            prev = cur;
            cur = fgetc(fh);
            
            if (instr(cur, delin) && !instr(prev, delin)){
                    //end of word commit word size
                    printf("%d\n", word_size);
                    
                    *(re->names + column) = (char*)malloc(sizeof(char) * (word_size+1));
                    fsetpos(fh, &pos);
                    
                    word_cur = *(re->names + column);
                    do{
                        cur = fgetc(fh);
                        *word_cur = cur;
                        word_cur++;                        
                    }while(!instr(cur, delin));
                    *word_cur = '\0';
                    
                    
                    column++;
                    word_size = 0;
                
            }else if (!instr(cur, delin)){
                if (word_size == 0){
                    fgetpos(fh, &pos);
                }
                printf("%c", cur);
                word_size++;
            }
        }while(cur != '\n');
        
        re->columns = (char***)malloc(sizeof(char**) * re->width);
        for (int i=0; i<re->width; i++){
            *(re->columns + i) = (char**)malloc(sizeof(char*) * re->height);
        }
        column = 0;
        row = 0;
        do{
            prev = cur;
            cur = fgetc(fh);
            
            if (( instr(cur, delin) && !instr(prev, delin) ) || cur == '\n'){
                    //end of word commit word size
                    _log(LOG_I, "column <%d> row<%d> word_size <%d>", column, row, word_size);
                    *(*(re->columns + column) + row)  = (char*)malloc(sizeof(char) * (word_size+1));
                    
                    fsetpos(fh, &pos);
                    
                    word_cur = *(*(re->columns + column) + row);
                    do{
                        cur = fgetc(fh);
                        *word_cur = cur;
                        word_cur++;                        
                    }while(!instr(cur, delin) && cur != '\n');
                    *word_cur = '\0';
                    
                    
                    if (cur == '\n'){
                        //reset for next row
                        *(re->columns + column) = (char**)malloc(sizeof(char*) * re->width);
                        row++;
                        column = 0;
                    }else{
                        column++;
                    }
                    
                    word_size = 0;
                    
            }else if (!instr(cur, delin)){
                if (word_size == 0){
                    fgetpos(fh, &pos);
                }
                word_size++;
            }
        }while(cur != EOF);
        
        pclose(fh);
        
    }else if (fh == NULL){
        //there was an error
        _log(LOG_E, "Error loading file <%s>", file_name);
    }
    
    _log(LOG_I, "width <%d>, height <%d>", re->width, re->height);
    
    free(buff);    
    return re;
}

//get the number of NON-EPMTY lines in a file
int fnum_lines(FILE *fh){
    fpos_t pos;
    char cur = 'a';
    int size = 0;
    bool line_empty = true;
    
    fgetpos(fh, &pos);
    rewind(fh);
    
    do{
        cur = fgetc(fh);
        if (cur == '\n'){
            line_empty = true;
        }else if(line_empty && cur != ' ' && cur != '\t'){
            line_empty = false;
            size++;
        }
    }while(cur != EOF);
        
    fsetpos(fh, &pos);
    
    return size;
}