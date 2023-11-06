#include "../lib/lib.h"

void test_regex(){
    //note the memory leek with unfreed strings
    regmat *a = gen_regex_matrix(string("aab"), string("testlaksjfh(o^o)"));
    String *result = parse_regex(a, string("aab"));
    _logs(LOG_I, result);

    a = gen_regex_matrix(string("print(\\d)"), string("print-dig"));
    result = parse_regex(a, string("print(8)"));
    _logs(LOG_I, result);
}

int main(int argc, char *argv[]){
    log_init();

    test_regex();
}