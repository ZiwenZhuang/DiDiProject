/* This is just a function set that help sharpen the matrix,
and help doing convolution.
*/
#ifndef IMG_PROCESS_H
#define IMG_PROCESS_H

#include "../included/convolution.h"
#include "matrix.h"

/* The following operations will modifies the given matrix directly.
    And based on the API we use, the size of the matrix should not be
too big, or there will be an overflow when converting unsigned int to
int.
*/
Matrix<int>& sharpen_matrix(Matrix<int> &mat_in, Matrix<int> &mat_out);

#include "imageProcess.tpp"

#endif