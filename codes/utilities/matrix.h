/* The file follow the convention of oop
and defines how we operates the matrix.
    Since there should not be too much
complex operations, and install libraries
could be to complex for this project, we
only implement some basic functions
*/

template <class T>
class matrix {
    T* data; // row expanded
    uint num_rows;
    uint num_cols;
}