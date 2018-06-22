/* The file follow the convention of oop and defines how we operates
the matrix.
    Since there should not be too much complex operations, and install
libraries could be to complex for this project, we only implement
some basic functions.
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>

using namespace std;

template <class T>
class Matrix {
    private:
        T* data; // row expanded
        unsigned int num_rows;
        unsigned int num_cols;
    public:
        /* When using constructor, you can set the content later or set
        the content in row expanded form (put the data in a signle array).
            When you constructing the matrix object with data provided,
        remember that you have handed over the ownership of the data, which will
        be freed (using delete operation) when disconstructing the Matrix instance.
        */
        Matrix();
        Matrix(unsigned int num_rows, unsigned int num_cols);
        Matrix(unsigned int num_rows, unsigned int num_cols, T* data);
        Matrix(const Matrix<T> &);
        ~Matrix();
        bool initialized();

        /* You can add data after construction or cover the old data.
            Since you pass with a pointer, we cannot check if the matrix size is
        valid, you have to check it on your own.
            You cannot set the number of rows and columns after the matrix's data
        is set.
        */
        void set_data(T*);
        void setSize(unsigned int row, unsigned int col);
        T* get_data();
        unsigned int getRowNum();
        unsigned int getColNum();

        /* The method returns a pointer to the row, which means you can possibly
        access the entries in the next rows, which might cause some unexpected
        problem.
        */
        T* operator[](unsigned int);

        /* When assign a matrix to another matrix (constructed by the default
        constructor) the data attributes will be copied. So, be sure to implement
        copy behavior on object T.
        */
        Matrix& operator=(const Matrix &other);
};

// Read and write matrix to file, since the pgm file might loss some of the details.
template<class T> int writeMatrix(string filename, Matrix<T> &target);
template<class T> int readMatrix(string filename, Matrix<T> &target);

/* Add patches on the matrix of to make the dots more visiable
    The three type is the type of three channel of matrix.
*/
template<class T, class Y, class U>
void add_patch(std::pair<int, int>* nodes, int nodes_num\
        , Matrix<T> matrixR, Matrix<Y> matrixG, Matrix<U> matrixB\
        , T patch_valueR, Y patch_valueG, U patch_valueB\
        , int patch_size = 2);
/* Add patches on only one channel
*/
template<class T>
void add_patch(Matrix<T> &target, std::pair<int, int>* nodes, int nodes_num\
    , T patch_value, int patch_size = 2);

#include "matrix.tpp"

#endif