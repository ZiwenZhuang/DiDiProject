#include "matrix.h"

// constructor
template <class T> Matrix<T>::Matrix() {
    this->num_rows = 0; this->num_cols = 0;
    this->data = nullptr;
}
template <class T> Matrix<T>::Matrix(unsigned int num_rows, unsigned int num_cols) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->data = new T [num_rows * num_cols];
}
template <class T> Matrix<T>::Matrix(unsigned int num_rows, unsigned int num_cols, T* data) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->data = data;
}
template <class T> Matrix<T>::Matrix(const Matrix<T> &matrix) {
    this->num_rows = matrix.num_rows;
    this->num_cols = matrix.num_cols;
    this->data = new T [num_rows * num_cols];
    memcpy(this->data, matrix.data, (this->num_rows * this->num_cols * sizeof(T)));
}
template <class T> Matrix<T>::~Matrix() {
    if (this->data != nullptr) delete[] this->data;
}
template <class T> bool Matrix<T>::initialized() {
    return (!(this->data == nullptr));
}

// setting data
template <class T> void Matrix<T>::set_data(T* data) {
    if (this->data != nullptr) {
        // cout << "Warning: when setting data to matrix, you are about to cover the old data.\n";
        delete[] this->data;
    }
    this->data = data;
}
template <class T> void Matrix<T>::setSize(unsigned int row, unsigned int col) {
    if (!this->initialized()) {
        this->num_rows = row;
        this->num_cols = col;
        this->data = new T [row * col];
    } else {
        cerr << "Your are changing a matrix to different size and we didn't do that" << endl;
        exit(0);
    }
    cout << "Initialized matrix into " << row << ", " << col << " dimension\n";
}
template <class T> T* Matrix<T>::get_data() {
    return this->data;
}
template <class T> unsigned int Matrix<T>::getRowNum() {
    return this->num_rows;
}
template <class T> unsigned int Matrix<T>::getColNum() {
    return this->num_cols;
}

// access entry
template <class T> T* Matrix<T>::operator[](unsigned int row_index) {
    if (row_index >= this->num_rows) {
        cerr << "Error detected when using operator[]: to large on the first index";
        return nullptr;
    }
    return this->data + this->num_cols * row_index;
}
// matrix assignment
template <class T> Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    this->num_rows = other.num_rows;
    this->num_cols = other.num_cols;
    if (this->data != nullptr) delete[] this->data;
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
    for (int i = 0; i < target.getRowNum() * target.getColNum(); i++) {
        file << target[0][i] << endl;
    }
    cout << "Read matrix from " << filename << " done\n";
    return 0;
}
template <class T> int readMatrix(string filename, Matrix<T> &target) {
    ifstream file; file.open(filename);
    if (!file.is_open()) {
        cerr << "Error detected when try to read " << filename << endl;
        return -1;
    }
    string type_name; file >> type_name;
    if (type_name.compare(typeid(T).name()) != 0) {
        cerr << "You should pass in a matrix with type: " << type_name << endl;
        return -1;
    }
    unsigned int row, col;
    file >> row; file >> col;
    target.setSize(row, col);
    for (int i = 0; i < row*col; i++) {
        file >> target[0][i];
    }
    cout << "Write matrix to " << filename << " done!\n";
    return 0;
}
template<class T, class Y, class U>
void add_patch(std::pair<int, int>* nodes, int nodes_num\
        , Matrix<T> matrixR, Matrix<Y> matrixG, Matrix<U> matrixB\
        , T patch_valueR, Y patch_valueG, U patch_valueB\
        , int patch_size) {
    for (int i = 0; i < nodes_num; i++) {
        matrixR[nodes[i].first][nodes[i].second] = patch_valueR;
        matrixG[nodes[i].first][nodes[i].second] = patch_valueG;
        matrixB[nodes[i].first][nodes[i].second] = patch_valueB;
        for (int a = (0-patch_size); a <= patch_size; a++) {
            for (int b = (0-patch_size); b <= patch_size; b++) {
                matrixR[nodes[i].first + a][nodes[i].second + b] = patch_valueR;
                matrixG[nodes[i].first + a][nodes[i].second + b] = patch_valueG;
                matrixB[nodes[i].first + a][nodes[i].second + b] = patch_valueB;
            }
        }
    }
}
template<class T>
void add_patch(Matrix<T> &target, std::pair<int, int>* nodes, int nodes_num\
    , T patch_value, int patch_size) {
    for (int i = 0; i < nodes_num; i++) {
        target[nodes[i].first][nodes[i].second] = patch_value;
        for (int a = (0-patch_size); a <= patch_size; a++) {
            for (int b = (0-patch_size); b <= patch_size; b++) {
                target[nodes[i].first + a][nodes[i].second + b] = patch_value;
            }
        }
    }
}