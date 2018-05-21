#include <iostream>
#include <fstream>

using namespace std;

int main() {
    printf("start the program\n");
    FILE* data_file = fopen("../data/order_20161101", "r");


    printf("press any key and Enter to quit\n");
    char q;
    cin >> q;
    return 0;
}