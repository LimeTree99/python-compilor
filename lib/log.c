#include "log.h"

char LOG_CHAR[] = {'E','F','W','I','D','T'};

void log_init(){
    for (int i=0; i < 6; i++){
        LOG_OUT[i] = stdout;
    }
}

void _builtin_log(LOG_LEVEL level, char *str, ...){
    va_list args;
    char pr[400];
    FILE *out = LOG_OUT[level];
    va_start(args, str);

    vsprintf(pr, str, args);
    
    fprintf(LOG_OUT[level], "\t%c:\t%s\n", LOG_CHAR[level], pr);
    
    va_end(args);
}

void set_log_out(LOG_LEVEL level, FILE *out){
    LOG_OUT[level] = out;
}