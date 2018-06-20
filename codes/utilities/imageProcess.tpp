#include "imageProcess.h"

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

template<class T>
Matrix<int>& two_level(Matrix<T> &mat_in, Matrix<int> &mat_out, unsigned int threshold) {
   // The threshold that seperate the pixel to 0 or 1.
	int* data_out = new int [mat_in.getRowNum() * mat_in.getColNum()];
	mat_out.set_data(data_out);
	for (int i = 0; i < mat_in.getRowNum(); i++) {
		for (int j = 0; j < mat_in.getColNum(); j++) {
			mat_out[i][j] = (mat_in[i][j] > threshold) ? 1 : 0;
		}
	}
}

float gradient(Matrix<float> &mat, int centerX, int centerY) {
    float k = 2; // Define the threshold to calcualte the diffustion
    float learning_rate = 1; // The lambda parameter in the iterating equation
    float gradient_sum = 0;
    gradient_sum += (mat[centerX][centerY - 1] - mat[centerX][centerY]) \
        / (1 + pow(((mat[centerX][centerY - 1] - mat[centerX][centerY])/k), 2));
    gradient_sum += (mat[centerX][centerY + 1] - mat[centerX][centerY]) \
        / (1 + pow(((mat[centerX][centerY + 1] - mat[centerX][centerY])/k), 2));
    gradient_sum += (mat[centerX - 1][centerY] - mat[centerX][centerY]) \
        / (1 + pow(((mat[centerX - 1][centerY] - mat[centerX][centerY])/k), 2));
    gradient_sum += (mat[centerX + 1][centerY] - mat[centerX][centerY]) \
        / (1 + pow(((mat[centerX + 1][centerY] - mat[centerX][centerY])/k), 2));
    return (learning_rate * gradient_sum / 4);
}

Matrix<float>& anios_diff(Matrix<int> &mat_in, Matrix<float> &mat_out) {
    Matrix<float> mat_tmp (mat_in.getRowNum(), mat_in.getColNum());
    for (int i = 0; i < (mat_in.getRowNum() * mat_in.getColNum()); i++) {
        mat_out[0][i] = (float)mat_in[0][i];
        mat_tmp[0][i] = (float)mat_in[0][i];
    }

    for (int iter = 0; iter < 50; iter++) {
        for (int x = 1; x < mat_out.getRowNum()-1; x++) {
            for (int y = 1; y < mat_out.getColNum()-1; y++) {
                mat_tmp[x][y] = mat_out[x][y] + gradient(mat_out, x, y);
            }
        }
        memcpy(mat_out[0], mat_tmp[0], (mat_in.getColNum() * mat_in.getRowNum() * sizeof(int)));
    }

    return mat_out;
}