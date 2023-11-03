#include "log.h"

char LOG_CHAR[] = {'E','F','W','I','D','T'};

void log_init(){
    for (int i=0; i < 6; i++){
        LOG_OUT[i] = stdout;
    }
}

void _log(LOG_LEVEL level, char *string, ...){
    va_list args;
    va_start(args, string);
    char pr[400];
    FILE *out = LOG_OUT[level];
    
    sprintf(pr, "\t%c:\t%s", LOG_CHAR[level], string);
    
    vfprintf(out, pr, args);
    
    va_end(args);
}

void set_log_out(LOG_LEVEL level, FILE *out){
    LOG_OUT[level] = out;
}