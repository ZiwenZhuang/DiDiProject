/* This is just a function set that help sharpen the matrix,
and help doing convolution.
*/
#include "matrix.h"
#include "../included/convolution.h"

/* The following operations will modifies the given matrix directly.
    And based on the API we use, the size of the matrix should not be
too big, or there will be an overflow when converting unsigned int to
int.
*/
Matrix& sharpen_matrix(Matrix &mat_in, Matrix &mat_out);