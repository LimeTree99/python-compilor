#include "regex.h"


/*
Overview:
    THIS IS NOT REGEX!!!!
    Terrible naming I know. A dfa is created from the parse string NOT an NFA.
    This means that there can be no non deterministic behavior in the parse 
    string.  
example regex:
    abc
    a*b
    A+b
example invalaid strings:
    a*a     ->  this is not deterministic, where's the exit point from 'a' char?
    a*\w    ->  same as above
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

regmat *gen_regex_matrix(char *regex, char *name){
    regmat *mat = malloc(sizeof(regmat));
    char *cur;
    int n;
    mat->char_size = CHARSET_SIZE;
    mat->num_nodes = strlen(regex);
    mat->size = mat->char_size * mat->num_nodes;
    mat->mat = (int*)malloc(sizeof(int) * mat->size);
    mat->ends = (char**)malloc(sizeof(char*) * mat->num_nodes);
    
    //set default value for return name
    for (int i=0; i<mat->num_nodes; i++){        
        mat->ends[i] = (char*)malloc(sizeof(char)*10);
        strcpy(mat->ends[i], "");
    }
    
    //set all of mat to default -1 and ends with defalt '\0'
    for (int i=0; i<mat->size; i++){
        *(mat->mat + i) = -1;
    }

    n=0;
    cur = regex;
    while (*cur != '\0'){
        //the special character <\> used
        if (*cur == '\\'){
            //advance to next letter
            cur = cur+1;
            if (*cur == '\\'){
                *(mat->mat + (n * mat->char_size) + *cur) = n+1;
            }else if (*cur == 'n'){
                *(mat->mat + (n * mat->char_size) + '\n') = n+1;
            }else if (*cur == '('){
                *(mat->mat + (n * mat->char_size) + '(') = n+1;
            }else if (*cur == ')'){
                *(mat->mat + (n * mat->char_size) + ')') = n+1;
            }else if (*cur == '*'){
                *(mat->mat + (n * mat->char_size) + '*') = n+1;
            }else if (*cur == '+'){
                *(mat->mat + (n * mat->char_size) + '+') = n+1;
            }else if (*cur == '|'){
                *(mat->mat + (n * mat->char_size) + '|') = n+1;
            }else if (*cur == 't'){
                *(mat->mat + (n * mat->char_size) + '\t') = n+1;
            }else if (*cur == 'w'){
                for (int i='a'; i<='z';i++){
                    *(mat->mat + (n * mat->char_size) + i) = n+1;
                }
                for (int i='A'; i<='Z';i++){
                    *(mat->mat + (n * mat->char_size) + i) = n+1;
                }
            }else if (*cur == 'd'){
                for (int i='0'; i<='9';i++){
                    *(mat->mat + (n * mat->char_size) + i) = n+1;
                }
            }
        }else if (*cur == '*'){
            //go back to the prev node and have it loop to itself in all 
            //cases where it goes to the next node.
            n--;
            for (int i=0; i<mat->char_size; i++){
                if (*(mat->mat + (n * mat->char_size) + i) != -1){
                    *(mat->mat + (n * mat->char_size) + i) = n;
                }
            }
            //if not at the end go back one so next char will be written to 
            //this node
            if (*(cur+1) != '\0'){
                n--;
            }
        }else if (*cur == '+'){
            
        }else if (*cur == '|'){

        }else if (*cur == ')'){

        }else if (*cur == '('){
            
        }else{
            //point the character in array to next unfilled node
            *(mat->mat + (n * mat->char_size) + *cur) = n+1;
        }
        cur = cur + 1;
        n++;
    }
    //n now is last node index
    n--;
    _log(LOG_I, "n <%d>",n);
    //reset end node to -1
    *(mat->mat + (n * mat->char_size) + *(cur - 1)) = -1;
    
    free(mat->ends[n]);
    mat->ends[n] = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(mat->ends[n], name);

    return mat;
}

char *parse_regex(regmat *mat, char *str){
    char *cur = str;
    int prev_node = -1;
    int node = 0;
    char *re;

    while (*cur != '\0' && node != -1){
        prev_node = node;
        node = *(mat->mat + node * mat->char_size + *cur);
        //printf("char: %c prev_node: %d node: %d\n", *cur, prev_node, node);
        cur++;
    }
    if (*cur == '\0'){
        re = (char*)malloc(sizeof(char) * (strlen( mat->ends[prev_node] ) + 1));
        strcpy(re, mat->ends[prev_node]);
    }else{
        //not at end of string, fail
        re = (char*)malloc(sizeof(char) * 3);
        strcpy(re, "\0");
    }
    return re;
}

void free_regex_matrix(regmat *mat){
    for (int i=0; i<mat->num_nodes; i++){
        free(mat->ends[i]);
    }
    free(mat->ends);
    free(mat->mat);
    free(mat);
}