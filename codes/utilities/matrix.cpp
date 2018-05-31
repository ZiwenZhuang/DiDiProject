#include "matrix.h"

// constructor
template <class T> Matrix::Matrix() {
    this->num_rows = 0; this->num_cols = 0;
    this->data = nullptr;
}
template <class T> Matrix::Matrix(unsigned int num_rows, unsigned int num_cols) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->data = nullptr;
}
template <class T> Matrix::Matrix(unsigned int num_rows, unsigned int num_cols, T* data) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->data = data;
}
template <class T> Matrix::~Matrix() {
    if (this->data != nullptr) delete[] this->data;
}
template <class T> bool Matrix::initialized() {
    return (!(this->data == nullptr));
}

// setting data
template <class T> void Matrix::set_data(T* data) {
    if (this->data != nullptr) {
        cout << "Warning: when setting data to matrix, you are about to cover the old data.\n";
        delete[] this->data;
    }
    this->data = data;
}
template <class T> void Matrix::setRowNum(unsigned int num) {
    if (!this->initialized()) this->num_rows = num;
}
template <class T> void Matrix::setColNum(unsigned int num) {
    if (!this->initialized()) this->num_cols = num;
}
template <class T> T* Matrix::get_data() {
    return this->data;
}
template <class T> unsigned int Matrix::getRowNum() {
    return this->num_rows;
}
template <class T> unsigned int Matrix::getColNum() {
    return this->num_cols;
}

// access entry
template <class T> T* Matrix::operator[](unsigned int row_index) {
    if (row_index >= this->num_rows) {
        stderr << "Error detected when using operator[]: to large on the first index";
        return nullptr;
    }
    return this->data + this->num_cols * row_index;
}
// matrix assignment
template <class T> Matrix& Matrix::operator=(const Matrix& other) {
    this->num_rows = other.num_rows;
    this->num_cols = other.num_cols;
    if（this->data != nullptr) delete[] this->data;
    this->data = new T [this->num_rows * this->num_cols];
    memcpy(this->data, other.data, this->num_rows * this->num_cols * sizeof(T));
    return *this;
}

template <class T> int writeMatrix(string filename, Matrix<T> &target) {
    ofstream file; file.open(filename);
    if (!file.is_open()) {
        cerr << "Error detected when try to write " << filename << endl;
        return -1;
    }
    file << typeid(T).name() << endl;
    file << target.getRowNum() << " " << target.getColNum() << endl;
    file.write(target.get_data(), target.getRowNum() * target.getColNum() * sizeof(T));
    return 0;
}
template <class T> int readMatrix(string filename, Matrix<T> &target) {
    ifstream file; file.open(filename);
    if (!file.is_open()) {
        cerr << "Error detected when try to read " << filename << endl;
        return -1;
    } else if (target.initialized()) {
        cerr << "You cannot have write to a initialized matrix"
        return -1;
    }
    string type_name; file >> type_name;
    if (type_name.compare(typeid(T).name()) != 0) {
        cerr << "You should pass in a matrix with type: " << type_name << endl;
        return -1;
    }
    unsigned int num;
    file >> num; target.setRowNum(num);
    file >> num; target.setColNum(num);
    file.read(target.get_data(), target.getRowNum() * target.getColNum() * sizeof(T));
    return 0;
}