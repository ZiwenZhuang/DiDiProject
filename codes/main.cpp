#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    cout << "start the program\n";

    fstream order_file; order_file.open("../data/order_20161101", ios_base::in);
    fstream gps_file; gps_file.open("../data/gps_20161101", ios_base::in);

    string one_line;
    getline(gps_file, one_line);
    cout << one_line << endl;
    
    getline(gps_file, one_line);
    cout << one_line << endl;

    printf("press any key and Enter to quit\n");
    char q;
    cin >> q;
    return 0;
}