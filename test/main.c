#include "../lib/lib.h"


void test_gen_regex_matrix();


int main(int argc, char *argv[]){
    log_init();
    //LOG_OUT[LOG_D] = NULL;

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
    datafrm *frame = imp_testf("test/inp/regex.txt", " \t");
    int test_len = frame->height;
    char **test_reg = *(frame->columns + 0);
    char **test_str = *(frame->columns + 1);
    char **test_name = *(frame->columns + 2);
    char **exp_result = *(frame->columns + 3);    
    
    //printf("-----------------------------------------\n");
    //display_frame(frame);   
    
    printf("-----------------------------------------\n");
    printf("Test gen_regex_matrix() and parse_regex()\n");
    printf("-----------------------------------------\n");

    for (int i=0; i<test_len; i++){
        a = gen_regex_matrix(test_reg[i], test_name[i]);
        result = parse_regex(a, test_str[i]);
        _log(LOG_D, "reg <%s> test str <%s> result <%s>", 
                test_reg[i], test_str[i], result);
        if (strcmp(result, exp_result[i])){
            _log(LOG_W, "incorrect result for reg <%s> and test str <%s>", test_reg[i], test_str[i]);
            pr_regex_matrix(a);            
        }
        
        free_regex_matrix(a);
        free(result);
    }
}