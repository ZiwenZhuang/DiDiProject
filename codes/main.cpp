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

void usage() {
    cout << "please specify the usage in the next argument\n";
    cout << "\t'raw': only write the raw image\n";
    cout << "\t'enhance': use simple enhance kernel and do the comvolution, write result to 'paths_enhanced.pgm'\n";
    cout << "\t'two_level': split pixels in only 0 or 1, write result into 'two_level.pgm'\n";
    cout << "\t'knn': applying knn_removal method, write result into 'knn_removal_result.pgm'\n";
    cout << "\t'anios': applying Aniostropic diffusion method, write result into 'anios_diff.pgm'\n";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        printf("The program ends\n\tpress any key and Enter to quit\n");
        char q; cin >> q;
        return 0;
    }
    cout << "start the program\n";

    fstream order_file; order_file.open("../data/order_20161101", ios_base::in);
    fstream gps_file; gps_file.open("../data/gps_20161101", ios_base::in);

    
    Matrix<int> paths_img = Matrix<int>(720, 480);
    paths_img.set_data(pixel(gps_file, \
        paths_img.getRowNum(), paths_img.getColNum()));
    if (strcmp(argv[1], "raw") == 0) {
        // write directly the readin image from Lottie
        pgm_ASCII::write_image<int>(paths_img, "../data/paths_img.pgm");
        return 0;
    }

    if (strcmp(argv[1], "enhance") == 0) {
        // Using edge detection kernel to enhance the image. The kernel is in the cooresponding function.
        Matrix<int> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        sharpen_matrix(paths_img, temp_img);
        pgm_ASCII::write_image<int>(temp_img, "../data/paths_enhanced.pgm");

    } else if (strcmp(argv[1], "two_level") == 0) {
        // Set the image with only two value either 0 or 1, the threshold is in the function.
        Matrix<int> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        two_level(paths_img, temp_img);
        pgm_ASCII::write_image<int>(temp_img, "../data/two_level.pgm");

    } else if (strcmp(argv[1], "knn") == 0) {
        // Using KNN removal method try to make the process clear.
        Matrix<int> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        Matrix<int> tempp_img (paths_img.getRowNum(), paths_img.getColNum());
        two_level(paths_img, temp_img);
        knn_removal(temp_img, tempp_img);
        pgm_ASCII::write_image<int>(tempp_img, "../data/knn_removal_result.pgm");

    } else if (strcmp(argv[1], "anios") == 0) {
        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<int> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        anios_diff(paths_img, temp_img);
        pgm_ASCII::write_image<int>(temp_img, "../data/anios_diff.pgm");

    } else {
        usage();
    }

    printf("The program ends\n\tpress any key and Enter to quit\n");
    char q; cin >> q;
    order_file.close(); gps_file.close();
    return 0;
}
