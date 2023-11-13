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
    char test_str[100];
    char test_reg[100];
    char test_name[100];

    printf("---------------------\n");
    printf("Test gen_regex_matrix\n");
    printf("---------------------\n");

    strcpy(test_reg, "aab");
    strcpy(test_name, "t01");
    strcpy(test_str, "aab");
    a = gen_regex_matrix(test_reg, test_name);
    result = parse_regex(a, test_str);
    _log(LOG_D, "test reg <%s> test str <%s> result <%s>", test_reg, test_str, result);
    free(a);
    free(result);

    strcpy(test_reg, "print(\\d)");
    strcpy(test_name, "t02");
    strcpy(test_str, "print(9)");
    a = gen_regex_matrix(test_reg, test_name);
    result = parse_regex(a, test_str);
    _log(LOG_D, "test reg <%s> test str <%s> result <%s>", test_reg, test_str, result);
}