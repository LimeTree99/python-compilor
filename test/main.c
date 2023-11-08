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
    regmat *a = gen_regex_matrix(string("aab"), string("testlaksjfh(o^o)"));
    String *result = parse_regex(a, string("aab"));
    _log(LOG_D, result->string);

    a = gen_regex_matrix(string("print(\\d)"), string("print-dig"));
    result = parse_regex(a, string("print(8)"));
    _log(LOG_D, result->string);
}