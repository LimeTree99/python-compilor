#include "log.h"

#define CHARSET_SIZE 255

//regex matrix
typedef struct regmat{
    int size;           //size to the 2d array mat
    int char_size;
    int num_nodes;
    int *mat;
    String **ends;      
}regmat;

regmat *gen_regex_matrix(String *regex, String *name);
String *parse_regex(regmat *mat, String *str);