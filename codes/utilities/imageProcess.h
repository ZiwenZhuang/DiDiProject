/* This is just a function set that help sharpen the matrix,
and help doing convolution.
*/
#ifndef IMG_PROCESS_H
#define IMG_PROCESS_H

#include <cstring>

#include "../included/convolution.h"
#include "matrix.h"
#include "KNNFloatImg.h"

/* The following operations will modifies the given matrix directly.
    And based on the API we use, the size of the matrix should not be
too big, or there will be an overflow when converting unsigned int to
int.
*/
Matrix<int>& sharpen_matrix(Matrix<int> &mat_in, Matrix<int> &mat_out);

/* Using KNN removal method and try to enhance the paths of all orders,
see if it can make the path detection easier.
*/
Matrix<int>& knn_removal(Matrix<int> &mat_in, Matrix<int> &mat_out);

/* This operation split entries into only 1 and 0
*/
Matrix<int>& two_level(Matrix<int> &mat_in, Matrix<int> &mat_out);

/* Applying anisotropic diffusion methods and try to eliminate the noise
*/
Matrix<int>& anios_diff(Matrix<int> &mat_in, Matrix<int> &mat_out);

#include "imageProcess.tpp"

#endif