#include "pgm_process.h"

using namespace pgm_ASCII;

// check the pgm file mode
bool check_mode(string &a_line) {
    if (a_line.compare("P2") != 0) {
        fprintf(stderr, "Cannot open pgm file that is not in P2 mode!");
        return false;
    }
    return true;
}

template <class T> int read_image(Matrix<T> &target, string &filename) {
    ifstream file; file.open(filename.c_str(), ios_base::in);
    string a_line; getline(file, a_line);
    // check mode
    if (!check_mode(a_line)) return -1;
    // read matrix size
    file >> target.num_rows; file >> target.num_cols;
    // read data as uint
    uint total = target.num_rows * target.num_cols;
    uint* array = new uint [total];
    for (uint i = 0; i < num_cols; i++) {
        getline(file, a_line); stringstream ss (a_line);
        for (uint j = 0; j < num_rows; j++) {
            ss >> target[j][i];
        }
    }
    return 0;
}
template <class T> int read_image(Matrix<T> &target, ifstream &file) {
    if (!file.is_open()) {
        fprintf(stderr, "Error detected in read_image, your provided a un-opened file stream");
        return -1;
    }
    string a_line; getline(file, a_line);
    // check mode
    if (!check_mode(a_line)) return -1;
    // read matrix size
    file >> target.num_rows; file >> target.num_cols;
    // read data as uint
    uint total = target.num_rows * target.num_cols;
    uint* array = new uint [total];
    for (uint i = 0; i < num_cols; i++) {
        getline(file, a_line); stringstream ss (a_line);
        for (uint j = 0; j < num_rows; j++) {
            ss >> target[j][i];
        }
    }
    return 0;
}
template <class T> int read_image(Matrix<T> &target, fstream &file) {
    if (!file.is_open()) {
        fprintf(stderr, "Error detected in read_image, your provided a un-opened file stream");
        return -1;
    }
    string a_line; getline(file, a_line);
    // check mode
    if (!check_mode(a_line)) return -1;
    // read matrix size
    file >> target.num_rows; file >> target.num_cols;
    // read data as uint
    uint total = target.num_rows * target.num_cols;
    uint* array = new uint [total];
    for (uint i = 0; i < num_cols; i++) {
        getline(file, a_line); stringstream ss (a_line);
        for (uint j = 0; j < num_rows; j++) {
            ss >> target[j][i];
        }
    }
    return 0;
}

template <class T> int write_image(Matrix<T> &target, string filename) {
    if (!target.initialized()) {
        fprintf(stderr, "Error detected, you let me write a matrix that has no data");
        return -1;
    }
    ofstream file; file.open(filename.c_str(), ios_base::out);
    file << "P2\n" << target.rows << " " << target.cols;
    for (uint i = 1; i < num_cols; i++) {
        file << endl << target[0][i];
        for (uint j = 1; j < num_rows; j++) {
            file << "\t" << target[j][i];
        }
    }
    return 0;
}