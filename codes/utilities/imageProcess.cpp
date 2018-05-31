#include "imageProcess.h"

Matrix& sharpen_matrix(Matrix<int> &mat_in, Matrix<int> &mat_out) {
    int kernel_size_x = 3;
    int kernel_size_y = 3;
    float kernel[] = {
        -1, 2,  -1,\
        2,  3,  2,\
        -1, 2,  -1
    };
    int* data_out = new int [mat_in.getRowNum() * mat_in.getColNum()];
    if (convolve2D(mat_in.get_data(), data_out, mat_in.getRowNum(), mat_in.getColNum(),\
    kernel + 4, kernel_size_x, kernel_size_y)) {
        mat_out.setRowNum(mat_in.getRowNum());
        mat_out.setColNum(mat_in.getColNum());
        mat_out.set_data(data_out);
    } else {
        cerr << "Cannot perform convolution on the input matrix," << endl;
        cerr << "\t reasons differs" << endl;
    }
    return mat_out;
}