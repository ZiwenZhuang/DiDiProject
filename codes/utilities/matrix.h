/* The file follow the convention of oop and defines how we operates
the matrix.
    Since there should not be too much complex operations, and install
libraries could be to complex for this project, we only implement
some basic functions.
*/
#include <iostream>
#include <fstream>

#ifndef MATRIX_DEF
#define MATRIX_DEF
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
        ~Matrix();
        bool initialized();

        /* You can add data after construction or cover the old data.
            Since you pass with a pointer, we cannot check if the matrix size is
        valid, you have to check it on your own.
            You cannot set the number of rows and columns after the matrix's data
        is set.
        */
        void set_data(T*);
        void setRowNum(unsigned int num);
        void setColNum(unsigned int num);
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
template <class T> int writeMatrix(string filename, Matrix<T> &target);
template <class T> int readMatrix(string filename, Matrix<T> &target);

#endif