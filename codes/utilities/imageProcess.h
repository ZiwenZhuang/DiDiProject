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
template<class T>
Matrix<int>& two_level(Matrix<T> &mat_in, Matrix<int> &mat_out, unsigned int threshold = 1);

/* Applying aniostropic diffusion methods and try to eliminate the noise
*/
Matrix<float>& anios_diff(Matrix<int> &mat_in, Matrix<float> &mat_out, int iteration = 60);

/* By changing the maximum value into a setting value, and all values
greater than the set value are changed to that 'set value'.
*/
template<class T>
Matrix<T>& lighter(Matrix<T> &mat_in, Matrix<T> &mat_out, float max = 5000);

/* This function view through the image and check if there are really
a stright line connecting them.
    The maxLength parameter is used to decided the maximum possible length of the road,
which is used to compared with the distance of two coordinates. (In Manhantan Distance)
If they are too far away, this function will return false directly.
*/
bool check_connected(Matrix<int> &image, const std::pair<int, int> &nodeA, const std::pair<int, int> &nodeB\
    , int threshold = 2000, int line_width = 1, int maxSegments = 0, int maxLength = 100);

#include "imageProcess.tpp"

#endif