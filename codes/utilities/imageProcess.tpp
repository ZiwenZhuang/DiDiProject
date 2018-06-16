#include "imageProcess.h"
#include "KNNFloatImg.h"

Matrix<int>& sharpen_matrix(Matrix<int> &mat_in, Matrix<int> &mat_out) {
    int kernel_size_x = 3;
    int kernel_size_y = 3;
    float kernel[] = {
        0,  -1,  0,\
        -1,  5,  -1,\
        0,  -1,  0
    };
    int* data_out = new int [mat_in.getRowNum() * mat_in.getColNum()];

    // perform convolution and check if it is sucess to store the result.
    if (convolve2D(mat_in.get_data(), data_out, mat_in.getColNum(), mat_in.getRowNum(),\
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

Matrix<int>& knn_removal(Matrix<int> &mat_in, Matrix<int> &mat_out) {
    KNN_removal((float*)mat_in[0],(int*)mat_out[0],mat_in.getRowNum(),mat_in.getColNum(),15,30,1.5);//kernelsize,k,dis_th
    return mat_out;
}

Matrix<int>& two_level(Matrix<int> &mat_in, Matrix<int> &mat_out) {
    unsigned int threshold = 3; // The threshold that seperate the pixel to 0 or 1.
	int* data_out = new int [mat_in.getRowNum() * mat_in.getColNum()];
	mat_out.setRowNum(mat_in.getRowNum()); mat_out.setColNum(mat_in.getColNum());
	mat_out.set_data(data_out);
	for (int i = 0; i < mat_in.getRowNum(); i++) {
		for (int j = 0; j < mat_in.getColNum(); j++) {
			mat_out[i][j] = (mat_in[i][j] > threshold) ? 1 : 0;
		}
	}
}