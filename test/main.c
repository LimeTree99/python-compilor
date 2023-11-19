#include "../lib/lib.h"


void test_gen_regex_matrix();


int main(int argc, char *argv[]){
    log_init();

    printf("============\n");
    printf("Test regex.c\n");
    printf("============\n");
    test_gen_regex_matrix();

    return 0;
}

void test_gen_regex_matrix(){
    //note the memory leek with unfreed strings
    regmat *a;
    char *result;
    int test_len = 5;
    char *test_reg[] =  {"aab",     "aab",      "aab",      "print\\(\\d\\)",   "a*b"};
    char *test_str[] =  {"aab",     "aabx",     "a",        "print(9)",         "aaaab"};
    char *test_name[] = {"a",       "a",        "a",        "a",                "a"};
    char *exp_result[] = {"a",      "",         "",         "a",                "a"};
    printf("-----------------------------------------\n");
    printf("Test gen_regex_matrix() and parse_regex()\n");
    printf("-----------------------------------------\n");

    for (int i=0; i<test_len; i++){
        a = gen_regex_matrix(test_reg[i], test_name[i]);
        result = parse_regex(a, test_str[i]);
        _log(LOG_D, "test reg <%s> test str <%s> result <%s>", 
                test_reg[i], test_str[i], result);
        if (strcmp(result, exp_result[i])){
            _log(LOG_W, "incorrect result for test reg <%s> and test str <%s>", test_reg[i], test_str[i]);
        }
        free(a);
        free(result);
    }

}