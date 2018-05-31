#include <iostream>
#include <string>
#include <fstream>

#include "included/convolution.h"
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

    for (int i = 0; i < 12; i++) {
        cout << read_a_line(gps_file) << endl;
    }

    printf("The program ends\n\tpress any key and Enter to quit\n");
    char q; cin >> q;
    order_file.close(); gps_file.close();
    return 0;
}