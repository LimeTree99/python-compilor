/** \file */

#include "parse_settings.h"

#define CHARSET_SIZE 255

//regex matrix
typedef struct regmat{
    int size;           //! size to the 2d array mat
    int char_size;
    int num_nodes;
    int *mat;
    char **ends;      
}regmat;

regmat *gen_regex_matrix(char *regex, char *name);

//! thing
/*! 
    Parse the whole of str
    \param mat
    \param str
    \return A string that must be freed later 
*/
char *parse_regex(regmat *mat, char *str);

//! Parse single character
int parse_regex_step(regmat *mat, char c, int node);

void free_regex_matrix(regmat *mat);