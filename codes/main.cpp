#include <iostream>
#include <string>
#include <fstream>

#include "utilities/imageProcess.h"
#include "utilities/pgm_process.h"
#include "utilities/matrix.h"
#include "utilities/pixel.h"
#include "utilities/graph.h"

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
    cout << "\t'anios_lighter': applying Aniostropic diffusion method, and make the picture lighter, write result into 'anios_lighter'\n";
    cout << "\t'anios_two_level': apply Anios... method and write result in onlye 2 level\n";
    cout << "\t'graph': Used for storing the vertices and detecting neighbors\n";
    cout << "\t'get_graph': add the node list to the Graph object and forms the digitalized object\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        printf("The program ends\n\tpress any key and Enter to quit\n");
        char q; cin >> q;
        return 0;
    }

    fstream order_file; order_file.open("../data/order_20161101", ios_base::in);
    fstream gps_file; gps_file.open("../data/gps_20161101", ios_base::in);

    
    Matrix<int> paths_img = Matrix<int>(480, 480);
    if (string(argv[1]) == string("raw")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        paths_img.set_data(pixel(gps_file, \
            paths_img.getRowNum(), paths_img.getColNum()));
        // write directly the readin image from Lottie
        pgm_ASCII::write_image<int>(paths_img, "../data/paths_img.pgm");

    } else if (string(argv[1]) == string("enhance")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        paths_img.set_data(pixel(gps_file, \
            paths_img.getRowNum(), paths_img.getColNum()));
        // Using edge detection kernel to enhance the image. The kernel is in the cooresponding function.
        Matrix<int> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        sharpen_matrix(paths_img, temp_img);
        pgm_ASCII::write_image<int>(temp_img, "../data/paths_enhanced.pgm");

    } else if (string(argv[1]) == string("two_level")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        paths_img.set_data(pixel(gps_file, \
            paths_img.getRowNum(), paths_img.getColNum()));
        // Set the image with only two value either 0 or 1, the threshold is in the function.
        Matrix<int> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        two_level(paths_img, temp_img);
        pgm_ASCII::write_image<int>(temp_img, "../data/two_level.pgm");

    } else if (string(argv[1]) == string("knn")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        paths_img.set_data(pixel(gps_file, \
            paths_img.getRowNum(), paths_img.getColNum()));
        // Using KNN removal method try to make the process clear.
        Matrix<int> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        Matrix<int> tempp_img (paths_img.getRowNum(), paths_img.getColNum());
        two_level(paths_img, temp_img);
        knn_removal(temp_img, tempp_img);
        pgm_ASCII::write_image<int>(tempp_img, "../data/knn_removal_result.pgm");

    } else if (string(argv[1]) == string("anios")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        paths_img.set_data(pixel(gps_file, \
            paths_img.getRowNum(), paths_img.getColNum()));
        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<float> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        anios_diff(paths_img, temp_img);
        Matrix<int> output (paths_img.getRowNum(), paths_img.getColNum());
        for (int i = 0; i < (paths_img.getRowNum() * paths_img.getColNum()); i++) {
            output[0][i] = (int)temp_img[0][i];
        }
        pgm_ASCII::write_image<int>(output, "../data/anios_diff.pgm");

    } else if (string(argv[1]) == string("anios_two_level")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        paths_img.set_data(pixel(gps_file, \
            paths_img.getRowNum(), paths_img.getColNum()));
        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<float> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        anios_diff(paths_img, temp_img);
        Matrix<int> output (paths_img.getRowNum(), paths_img.getColNum());
        two_level(temp_img, output, 50);
        pgm_ASCII::write_image<int>(output, "../data/anios_diff.pgm");


    } else if (string(argv[1]) == string("graph")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        graph<int> new_g(10);
        std::pair<node<int>**,int> nei;
        new_g.create_node(1,22);

        new_g.create_node(2,33);
        new_g.create_road(1,22,2,33);
        nei=new_g.find_neighbor(1,22);

    } else if (string(argv[1]) == string("anios_lighter")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        paths_img.set_data(pixel(gps_file, \
            paths_img.getRowNum(), paths_img.getColNum()));
        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<float> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        anios_diff(paths_img, temp_img);
        lighter(temp_img, temp_img, 200);
        Matrix<int> output (paths_img.getRowNum(), paths_img.getColNum());
        for (int i = 0; i < (paths_img.getRowNum() * paths_img.getColNum()); i++) {
            output[0][i] = (int)temp_img[0][i];
        }
        pgm_ASCII::write_image<int>(output, "../data/anios_lighter.pgm");

    } else if (string(argv[1]) == string("get_graph")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        // paths_img.set_data(pixel(gps_file, \
        //     paths_img.getRowNum(), paths_img.getColNum()));
        // writeMatrix("../data/path_matrix.matrix", paths_img);
        // Matrix<int> &order_img = paths_img;
        
        Matrix<int> order_img;
        readMatrix("../data/path_matrix.matrix", order_img);

        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<float> temp_img (order_img.getRowNum(), order_img.getColNum());
        anios_diff(order_img, temp_img);
        lighter(temp_img, temp_img, 3000);
        Matrix<int> to_display (order_img.getRowNum(), order_img.getColNum());
        two_level(temp_img, to_display, 2000);

        string filename = "../data/node_array";
        // Get the list of nodes recognized by the python program
        int node_number = 0;
        std::pair<int, int>* node_list = acquire_node_list(filename, node_number);
        // The first is the row index
        // and the second is column index
        // (which is just x, y coordinates)

        // Constructing the graph
        graph<int> graph (node_number);
        for (int i = 0; i < node_number; i++) {
            graph.create_node(node_list[i].first, node_list[i].second);
        }

        // Recognizing between each nodes whether there are direct roads
        for (int i = 0; i < node_number; i++) {
            // checking the i-th nodes neighbors (index greater than i)
            for (int j = i; j < node_number; j++) {
                // if this two node is neighbor, connect them in Graph object
                // Given the processed matrix.
                if (check_connected(to_display, node_list[i], node_list[j])) {
                    graph.create_road(node_list[i].first, node_list[i].second,\
                        node_list[j].first, node_list[j].second);
                }
            }
        }
        
    } else {
        usage();
    }

    printf("The program ends\n\tpress any key and Enter to quit\n");
    char q; cin >> q;
    order_file.close(); gps_file.close();
    return 0;
}
