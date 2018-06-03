#include <iostream>
#include <string>
#include <fstream>

#include "utilities/imageProcess.h"
#include "utilities/pgm_process.h"
#include "utilities/matrix.h"
#include "utilities/pixel.h"

using namespace std;

/* This function is designed to read a line of string through the given
file stream, which means you have to open the file before calling it.
*/
string read_a_line(fstream& file) {
    if (!file.is_open()) {
        fprintf(stderr, "Error detected, in read_a_line(): the fstream to read is not open yet\n");
    }
    string one_line;
    getline(file, one_line);
    return one_line;
}

int main() {
    cout << "start the program\n";

    fstream order_file; order_file.open("../data/order_20161101", ios_base::in);
    fstream gps_file; gps_file.open("../data/gps_20161101", ios_base::in);

    Matrix<int> paths_img = Matrix<int>(720, 480);
    paths_img.set_data(pixel(gps_file, \
        paths_img.getRowNum(), paths_img.getColNum()));

    pgm_ASCII::write_image<int>(paths_img, "../data/paths_img.pgm");

    Matrix<int> paths_enhanced;
    sharpen_matrix(paths_img, paths_enhanced);

    pgm_ASCII::write_image<int>(paths_enhanced, "../data/paths_enhanced.pgm");

    Matrix<int> two_lv;
    two_level(paths_img, two_lv);

    pgm_ASCII::write_image<int>(two_lv, "../data/two_level.pgm");

    printf("The program ends\n\tpress any key and Enter to quit\n");
    char q; cin >> q;
    order_file.close(); gps_file.close();
    return 0;
}