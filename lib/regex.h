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

//! copy one, or part of one, regmat into another at a specifided position
/*!
    Copy mat2 from mat2_start to mat2_end into mat1 starting at mat1_node.
    \param mat1 
    \param mat2
    \param mat1_node
    \param mat2_start
    \param mat2_end
*/ 
int copyto_regex_matrix(regmat *mat1, regmat *mat2, int mat1_node, int mat2_start, int mat2_end);

//! stich one regmat into another
/*!
    Stitch mat2 into mat1 after specified node. mat2_start and mat2_end are inclusive.
    \param mat1 the matrix to be added onto
    \param mat2 the matrix to added to mat1
    \param node the node in mat1 that will point to the mat2 start node
    \return debug
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