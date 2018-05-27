#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    cout << "start the program\n";

    //fstream order_file; order_file.open("../data/order_20161101", ios_base::in);
    fstream gps_file; gps_file.open("../data/gps_20161101", ios_base::in);

    string one_line;
    for (int i = 0; i < 12; i++) {
        gps_file >> one_line;
        cout << "Read one Line |" << one_line << endl;
    }

    printf("press any key and Enter to quit\n");
    char q; cin >> q;
    order_file.close(); gps_file.close();
    return 0;
}