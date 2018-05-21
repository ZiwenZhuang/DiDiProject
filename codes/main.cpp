#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    printf("start the program\n");

    fstream order; order.open("./data/order_20161101", ios_base::in);

    string one_line;
    order >> one_line;
    printf(one_line.data()); printf("\n");

    printf("press any key and Enter to quit\n");
    char q;
    cin >> q;
    return 0;
}