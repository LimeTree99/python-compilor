#include "regex.h"


/*
example regex:
    abc
    a*b
    A+b
regex fetures:
    *   repeat 0 or infinite times

method:
    the regex will be made into a dfa matrix 
    the dfa matracies will be combined with each endpoint indicating an output

types:
    -regex_matrix a 2d matrix where y represents each node x represents the 
        paths to the next node
    - int -1 returned means end reached
    - after end reached reference the final node index to name index.
        If the contense of the name array is null -> '\0' the string is not a match
        else if the contense of name array is a string, return the name of token found
        
*/

regmat *gen_regex_matrix(String *regex, String *name){
    regmat *mat = malloc(sizeof(regmat));
    char cur;
    int n;
    mat->char_size = CHARSET_SIZE;
    mat->num_nodes = regex->size;
    mat->size = mat->char_size * mat->num_nodes;
    mat->mat = (int*)malloc(sizeof(int) * mat->size);
    mat->ends = (String**)calloc(sizeof(String*), mat->num_nodes);

    //set all of mat to default -1
    for (int i=0; i<mat->size; i++){
        *(mat->mat + i) = -1;
    }

    _logs(LOG_I, str_cp(regex));

    n=0;
    while (n<regex->size){
        cur = *(regex->string + n);
        if (cur == '\\'){
            //advance to next letter
            n++;
            cur = *(regex->string + n);
            if (cur == '\\'){
                *(mat->mat + (n * mat->char_size) + cur) = n+1;
            }else if (cur == 'n'){
                *(mat->mat + (n * mat->char_size) + '\n') = n+1;
            }else if (cur == 't'){
                *(mat->mat + (n * mat->char_size) + '\t') = n+1;
            }else if (cur == 'w'){
                for (int i='a'; i<='z';i++){
                    *(mat->mat + (n * mat->char_size) + i) = n+1;
                }
                for (int i='A'; i<='Z';i++){
                    *(mat->mat + (n * mat->char_size) + i) = n+1;
                }
            }else if (cur == 'd'){
                for (int i='0'; i<='9';i++){
                    *(mat->mat + (n * mat->char_size) + i) = n+1;
                }
            }

        }else if (cur == '*'){

        }else if (cur == '+'){

        }else if (cur == '|'){
            
        }else{
            //point the character in array to next unfilled node
            *(mat->mat + (n * mat->char_size) + cur) = n+1;
        }
        n++;
    }
    //n now is last node index
    n--;
    //reset end node to -1
    *(mat->mat + (n * mat->char_size) + cur) = -1; 
    *(mat->ends + n) = str_cp(name);

    return mat;
}

String *parse_regex(regmat *mat, String *str){
    char *cur = str->string;
    int prev_node = -1;
    int node = 0;

    while (*cur != '\0' && node != -1){
        prev_node = node;        
        node = *(mat->mat + node * mat->char_size + *cur);

        cur++;
    }
    return str_cp( *(mat->ends+prev_node) );
}