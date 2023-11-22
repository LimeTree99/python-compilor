/** \file */

#include "imports.h"


#define _log(level,string,...) _builtin_log(level,__FILE__,__LINE__,string,##__VA_ARGS__)


FILE *LOG_OUT[6];
char LOG_CHAR[6];
WORD LOG_COLOR[6];

typedef enum LOG_LEVEL{
    LOG_F,
    LOG_E,
    LOG_W,
    LOG_I,
    LOG_D,
    LOG_T,
}LOG_LEVEL;

void log_init();

//log using regular c strings
void _builtin_log(LOG_LEVEL level, char* _file, int _line, char *string, ...);

void set_log_out(LOG_LEVEL level, FILE *out);