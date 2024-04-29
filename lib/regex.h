/** \file */

#include "parse_settings.h"

#define CHARSET_SIZE 255

//regex matrix
typedef struct regmat{
    int size;           //! size to the 2d array mat
    int char_size;      //! defined as size of askii for the mo
    int num_nodes;      //! number of nodes, there may be extra unused ones 
    int *mat;           //! 2d array of size char_size X num_nodes 
    char **ends;        //! 1d array of strings that are the name of the ends
}regmat;

regmat *init_regmat(int size, int char_size);


regmat *gen_regex_matrix(char *regex, char *name);

regmat *gen_regex_matrix_sub(char **cursor, char *name);

//! stich one regmat into another
/*!
    Stitch mat2 into mat1 at node
    \param mat1 the matrix to be added onto
    \param mat2 the matrix to added to mat1
    \param node the node in mat1 that mat2 will start on
    \return Error code
*/
int stitch_regex_matrix(regmat *mat1, regmat *mat2, int node);

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

void pr_regex_matrix(regmat *mat);

void free_regex_matrix(regmat *mat);