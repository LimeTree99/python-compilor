#include "../lib/lib.h"


void test_regex();


int main(int argc, char *argv[]){
    log_init();

    printf("Test regex.c\n");
    test_regex();

    return 0;
}

void test_regex(){
    //note the memory leek with unfreed strings
    regmat *a;
    char *result;
    char test_str[100];
    char test_reg[100];
    char test_name[100];

    strcpy(test_reg, "aab");
    strcpy(test_name, "t01");
    strcpy(test_str, "aab");
    a = gen_regex_matrix("aab", "testlaksjfh(o^o)");
    result = parse_regex(a, "aab");
    _log(LOG_D, result);

    a = gen_regex_matrix("print(\\d)", "print-dig");
    result = parse_regex(a, "print(8)");
    _log(LOG_D, result);
}