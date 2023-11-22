#include "log.h"

typedef struct datafrm{
    int width;
    int height;
    char **names;
    char ***columns;
}datafrm;


datafrm *imp_testf(char file_name[], const char *delin);