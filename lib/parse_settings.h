#include "log.h"

typedef struct datafrm{
    int width;
    int height;
    char **names;
    char ***columns;
}datafrm;
/*
the format of columns   (this needs verification, it SHOULD be this)
***         **          *
columns ->  col_1   ->  str_1
            |           str_2
            |
            col_2   ->  str_1
                        str_2
*/


datafrm *imp_testf(char file_name[], const char *delin);
void display_frame(datafrm *frame);