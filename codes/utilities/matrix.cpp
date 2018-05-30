#include "matrix.h"

// constructor
template <class T> Matrix::Matrix(uint num_rows, uint num_cols) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->data = nullptr;
}
template <class T> Matrix::Matrix(uint num_rows, uint num_cols, T* data) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->data = data;
}
template <class T> Matrix::~Matrix() {
    delete[] this->data;
}
// setting data
template <class T> void Matrix::set_data(T* data) {
    if (this->data != nullptr) {
        cout << "Warning: when setting data to matrix, you are about to cover the old data.\n";
        delete[] this->data;
    }
    this->data = data;
}
// access entry
template <class T> T* Matrix::operator[](uint row_index) {
    if (row_index >= this->num_rows) {
        stderr << "Error detected when using operator[]: to large on the first index";
        return nullptr;
    }
    return this->data + this->num_cols * row_index;
}