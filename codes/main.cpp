#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    cout << "start the program\n";

    //fstream order_file; order_file.open("../data/order_20161101", ios_base::in);
    fstream gps_file; gps_file.open("../data/gps_20161101", ios_base::in);

    string one_line;
    fstream& file2read = gps_file;
    for (int i = 0; i < 12; i++) {
        file2read >> one_line;
        cout << "Read one Line |" << one_line << endl;
    }

    printf("press any key and Enter to quit\n");
    char q;
    cin >> q;
    return 0;
}