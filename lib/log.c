#include "log.h"

char LOG_CHAR[] = {'E','F','W','I','D','T'};

void log_init(){
    for (int i=0; i < 6; i++){
        LOG_OUT[i] = stdout;
    }
}

void _logs(LOG_LEVEL level, String *str){
    char pr[400];
    FILE *out = LOG_OUT[level];
    
    sprintf(pr, "\t%c:\t%s\n", LOG_CHAR[level], str->string);
    
    fprintf(out, pr);
    str_free(str);
}

void _log(LOG_LEVEL level, char *str, ...){
    va_list args;
    _logs(level, string(str, args));
}

void set_log_out(LOG_LEVEL level, FILE *out){
    LOG_OUT[level] = out;
}