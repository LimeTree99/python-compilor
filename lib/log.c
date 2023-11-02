#include "log.h"

volatile FILE *LOG_OUT[] = {stdout, stdout, stdout, stdout, stdout, stdout};
char LOG_CHAR[] = {'E','F','W','I','D','T'};

void _log(LOG_LEVEL level, char *string, ...){
    va_list args;
    va_start(args, string);
    char *pr;

    FILE *out = LOG_OUT[level];

    memcpy(pr, LOG_CHAR+level, 1);

    strcat(pr, string);
    
    vfprintf(out, pr, args);
    
    va_end(args);
}

void set_log_out(LOG_LEVEL level, FILE *out){
    LOG_OUT[level] = out;
}