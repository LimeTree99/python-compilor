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


regmat *init_regmat(int size, int char_size){
    regmat *mat = malloc(sizeof(regmat));
    
    mat->char_size = char_size;
    mat->num_nodes = size;
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
    return mat;
}

regmat *gen_regex_matrix(char *regex, char *name){
    char **cursor = &regex;    
    regmat *re = gen_regex_matrix_sub(cursor, name);
    return re;
}

regmat *gen_regex_matrix_sub(char **cursor, char *name){
    char *cur = *cursor;
    regmat *mat = init_regmat(strlen(cur)+1, CHARSET_SIZE);
    regmat *sub_mat;
    bool end = false;
    int n;

    n=0;
    while (!end && *cur != '\0'){
        
        //the special character <\> used
        if (*cur == '\\'){
            //advance to next letter
            cur = cur+1;
            if (*cur == '\\' || *cur == '(' || *cur == ')' ||
                    *cur == '*' || *cur == '+' || *cur == '|' ||
                    *cur == '?'){
                *(mat->mat + (n * mat->char_size) + *cur) = n+1;
            }else if (*cur == 'n'){
                *(mat->mat + (n * mat->char_size) + '\n') = n+1;
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
        }else if (*cur == '?'){
            cur = cur + 1;
            *(mat->mat + (n * mat->char_size) + *cur) = n+1;
            *(mat->mat + ( (n-1) * mat->char_size) + *cur) = n+1;
        }else if (*cur == '+'){
            *(mat->mat + (n * mat->char_size) + *(cur-1)) = n;
            n--;
        }else if (*cur == '(' || *cur == '|'){
            // Plan:
            // This will begin a recursive call.
            // Each time that "|" is reached it is stitched between
            // a start node and an end node (how do i put the end
            // node after all this mess). Then once ")" is reached
            // stitch it all to the end node. 
            // Stitch the two parts onto the end of the original 
            
            // impliment:
            // here i need it to stop at "|" & ")"
            // also somehow advance cur 
            
            cur = cur + 1;
            *cursor = cur;
            sub_mat = gen_regex_matrix_sub(cursor, "");
            cur = *cursor;
            
            mat->size = n;
            
            stitch_regex_matrix(mat, sub_mat, n-1);
            free_regex_matrix(sub_mat);
            n--;
            
        }else if (*cur == ')'){
            // this will end a recursive call
            // note: only used in recursion level > 1
            end = true;
            n--;
            
        }else{
            //point the character in array to next unfilled node
            *(mat->mat + (n * mat->char_size) + *cur) = n+1;
        }
        cur = cur + 1;
        n++;
    }
    
    printf("in: <%s>\n", *cursor);
    free(mat->ends[n]);
    mat->ends[n] = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(mat->ends[n], name);
    mat->size = n+1;
    pr_regex_matrix(mat);
    return mat;
}
int copyto_regex_matrix(regmat *mat1, regmat *mat2, int mat1_node, int mat2_start, int mat2_end){
    int points;
    for (int y=0; y<mat2_end+1-mat2_start; y++){
        for (int x=0;x<mat1->char_size; x++){
            points = *(mat2->mat + ((y+mat2_start) * mat2->char_size) + x);
            if (points != -1){
                points += mat1_node;
                *(mat1->mat + ((y+mat1_node) * mat1->char_size) + x) = points;
            }
        }
        
        if (**(mat2->ends+y+mat2_start) != '\0'){
            free(*(mat1->ends+y+mat1_node));
            *(mat1->ends+y+mat1_node) = (char*)malloc(sizeof(char) * (strlen(*(mat2->ends+y+mat2_start)) + 1));
            strcpy(*(mat1->ends+y+mat1_node), *(mat2->ends+y+mat2_start));
            
        }
    }
    return 0;
}

int stitch_regex_matrix(regmat *mat1, regmat *mat2, int node){
    regmat *new_mat = init_regmat(mat1->num_nodes + mat2->num_nodes, CHARSET_SIZE);

    printf("1 node: %d, 2 start: %d, 2 end: %d\n", 0, 0, node);    
    copyto_regex_matrix(new_mat, mat1, 0, 0, node);
    pr_regex_matrix(new_mat);
    
    printf("1 node: %d, 2 start: %d, 2 end: %d\n", node+1, 0, mat2->size-1);
    copyto_regex_matrix(new_mat, mat2, node+1, 0, mat2->size-1);
    pr_regex_matrix(new_mat);
    
    printf("1 node: %d, 2 start: %d, 2 end: %d\n", node+1+mat2->size, node+1, mat1->size-1);
    copyto_regex_matrix(new_mat, mat1, node+1+mat2->size, node+1, mat1->size-1);
    
    free_regex_matrix(mat1);
    *mat1 = *new_mat;
    
    printf("submat:\n");
    pr_regex_matrix(mat1);
    
    return 0;
}

char *parse_regex(regmat *mat, char *str){
    char *cur = str;
    int prev_node = -1;
    int node = 0;
    char *re;

    while (*cur != '\0' && node != -1){
        prev_node = node;
        node = *(mat->mat + node * mat->char_size + *cur);
        cur++;
    }
    if (*cur == '\0' && node != -1){
        re = (char*)malloc(sizeof(char) * (strlen( mat->ends[node] ) + 1));
        strcpy(re, mat->ends[node]);
    }else{
        //fail
        re = (char*)malloc(sizeof(char) * 3);
        strcpy(re, "\0");
    }
    return re;
}

void pr_regex_matrix(regmat *mat){
    for (int y=0; y<mat->num_nodes; y++){
        printf("<%d>: ", y);
        for (int x=0; x<mat->char_size; x++){
            if ( *(mat->mat + (y * mat->char_size) + x) != -1 ){
                printf("%c->%-2d ",x, *(mat->mat + (y * mat->char_size) + x));
            }
        }
        if (**(mat->ends+y) != '\0'){
            printf("<%s>", *(mat->ends+y));
        }
        printf("\n");
    }
}

void free_regex_matrix(regmat *mat){
    for (int i=0; i<mat->num_nodes; i++){
        free( *(mat->ends+i));
    }
    free(mat->ends);
    free(mat->mat);
    
    // this will crash the program. Why??? I don't think mat is being properly freed
    //free(mat);  
}