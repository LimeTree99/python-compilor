#include "log.h"

char LOG_CHAR[] = {'E','F','W','I','D','T'};

void log_init(){
    for (int i=0; i < 6; i++){
        LOG_OUT[i] = stdout;
    }
    LOG_COLOR[0] = FOREGROUND_RED;
    LOG_COLOR[1] = FOREGROUND_GREEN;
    LOG_COLOR[2] = FOREGROUND_GREEN;
    LOG_COLOR[3] = FOREGROUND_GREEN;
    LOG_COLOR[4] = FOREGROUND_GREEN;
    LOG_COLOR[5] = FOREGROUND_GREEN;
    LOG_COLOR[6] = FOREGROUND_GREEN;
}

void _builtin_log(LOG_LEVEL level, char* _file, int _line, char *string, ...){
    va_list args;
    char pr[400];
    FILE *out = LOG_OUT[level];
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    
    va_start(args, string);

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, LOG_COLOR[level]);

    fprintf(LOG_OUT[level], "%c", LOG_CHAR[level]);

    SetConsoleTextAttribute(hConsole, saved_attributes);
    
    vsprintf(pr, string, args);
    fprintf(LOG_OUT[level], " : %s:%d %s\n", _file, _line, pr);

    SetConsoleTextAttribute(hConsole, saved_attributes);
    
    va_end(args);
}

void set_log_out(LOG_LEVEL level, FILE *out){
    LOG_OUT[level] = out;
}