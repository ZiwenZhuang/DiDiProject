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

int read_image(Matrix<uint> &target, string &filename) {
    ifstream fileIn; fileIn.open(filename.c_str(), ios_base::in);
    string a_line; getline(fileIn, a_line);
    // check mode
    if (!check_mode(a_line)) return -1;
    // read matrix size
    fileIn >> target.num_rows; fileIn >> target.num_cols;
    // read data as uint
    uint total = target.num_rows * target.num_cols;
    uint* array = new uint [total];
    for (uint i = 0; i < total; i++) {
        uint value; fileIn >> value;
        target[0][i] = value;
    }
    return 0;
}
int read_image(Matrix<uint> &target, ifstream &file) {
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
    for (uint i = 0; i < total; i++) {
        uint value; file >> value;
        target[0][i] = value;
    }
    return 0;
}
int read_image(Matrix<uint> &target, fstream &file) {
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
    for (uint i = 0; i < total; i++) {
        uint value; file >> value;
        target[0][i] = value;
    }
    return 0;
}