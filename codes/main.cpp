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

/* This function only transfroms a list of std::pair<int> base on the given
square matrix (clock-wise 90 degree)
*/
template<class T> // the coordinate type to transform
void clockwise90(std::pair<T, T>* coordinates, int number, T dimension) {
    for (int i = 0; i < number; i++) {
        T x, y;
        x = coordinates[i].second;
        y = dimension - coordinates[i].first;
        coordinates[i] = std::pair<T, T>(x, y);
    }
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
    cout << "\t'lighter': simply make the raw image lighter for visual\n";
    cout << "\t'get_nodes': simply read the node file and put then on a display file 'withnodes.ppm'\n";
    cout << "\t'demo': perform the demo and all the files will be put in number sequence in ../demo/ directory.\n";
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

        Matrix<int> order_img;
        readMatrix("../data/path_matrix.matrix", order_img);
        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<float> temp_img (order_img.getRowNum(), order_img.getColNum());
        anios_diff(order_img, temp_img, 20);
        Matrix<int> output (order_img.getRowNum(), order_img.getColNum());
        two_level(temp_img, output, 50);
        pgm_ASCII::write_image<int>(output, "../data/anios_diff_it20.pgm");


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

    } else if (string(argv[1]) == string("lighter")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        
        Matrix<int> order_img;
        readMatrix("../data/path_matrix.matrix", order_img);
        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<int> temp_img (paths_img.getRowNum(), paths_img.getColNum());
        lighter(order_img, temp_img, 2000);
        pgm_ASCII::write_image<int>(temp_img, "../data/lighter.pgm");

    } else if (string(argv[1]) == string("get_nodes")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        
        Matrix<int> order_img;
        readMatrix("../data/path_matrix.matrix", order_img);

        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<float> temp_img (order_img.getRowNum(), order_img.getColNum());
        anios_diff(order_img, temp_img);
        lighter(temp_img, temp_img, 3000);
        Matrix<int> to_display (order_img.getRowNum(), order_img.getColNum());
        two_level(temp_img, to_display, 200);

        string filename = "../data/intersection.bin";
        // Get the list of nodes recognized by the python program
        int node_number = 0;
        std::pair<int, int>* node_list = acquire_node_list(filename, node_number);
        clockwise90(node_list, node_number, (int)order_img.getRowNum());
        // The first is the row index
        // and the second is column index
        // (which is x, y coordinates)

        Matrix<int> nodes_marks = to_display;
        add_patch<int>(nodes_marks, node_list, node_number, 0, 3);
        add_patch<int>(to_display, node_list, node_number, 1, 3);

        pgm_ASCII::write_image_3C(to_display, nodes_marks, to_display, "../data/marked_nodes.ppm");

    } else if (string(argv[1]) == string("get_graph")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        
        Matrix<int> order_img;
        readMatrix("../data/path_matrix.matrix", order_img);

        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<float> temp_img (order_img.getRowNum(), order_img.getColNum());
        anios_diff(order_img, temp_img);
        lighter(temp_img, temp_img, 3000);
        Matrix<int> to_display (order_img.getRowNum(), order_img.getColNum());
        two_level(temp_img, to_display, 2000);

        string filename = "../data/corner.bin";
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

    } else if (string(argv[1]) == string("demo")) {
        cout << "start the program with argv[1]: " << argv[1] << endl;
        
        Matrix<int> order_img;
        readMatrix("../data/path_matrix.matrix", order_img);

        // Apply Aniostropic diffusion method to try to eliminate the noise
        Matrix<float> temp_img (order_img.getRowNum(), order_img.getColNum());
        anios_diff(order_img, temp_img);
        lighter(temp_img, temp_img, 3000);
        Matrix<int> to_display (order_img.getRowNum(), order_img.getColNum());
        two_level(temp_img, to_display, 500);
        
        // Generate the preprocessed image
        pgm_ASCII::write_image(to_display, "../demo/prepeocessed.pgm");

        string filename = "../data/intersection.bin";
        // Get the list of nodes recognized by the python program
        int node_number = 0;
        std::pair<int, int>* node_list = acquire_node_list(filename, node_number);
        clockwise90(node_list, node_number, (int)order_img.getRowNum());
        // The first is the row index
        // and the second is column index
        // (which is just x, y coordinates)

        // Generate the nodes patches that are recognized
        Matrix<int> nodes_marksR = to_display;
        Matrix<int> nodes_marksG = to_display;
        Matrix<int> nodes_marksB = to_display;
        add_patch(node_list, node_number\
            , nodes_marksR, nodes_marksG, nodes_marksB\
            , 1, 1, 0\
            , 3);
        pgm_ASCII::write_image_3C(nodes_marksR, nodes_marksG, nodes_marksB, "../demo/marked_nodes.ppm");

        // Constructing the graph
        graph<int> graph (node_number);
        for (int i = 0; i < node_number; i++) {
            graph.create_node(node_list[i].first, node_list[i].second);
        }

        // Recognizing between each nodes whether there are direct roads
        cout << "Connecting the nodes\n";
        for (int i = 0; i < node_number; i++) {
            // checking the i-th nodes neighbors (index greater than i)
            for (int j = i+1; j < node_number; j++) {
                // if this two node is neighbor, connect them in Graph object
                // Given the processed matrix.
                if (check_connected(to_display, node_list[i], node_list[j])) {
                    graph.create_road(node_list[i].first, node_list[i].second,\
                        node_list[j].first, node_list[j].second);
                    cout << "\tcreate edges on node |" << i << "| and |" << j << "|\n";
                }
            }
        }
        cout << "Done!\n";

        int a, b; // input node index to search route
        a = node_number + 1;
        while ((a < 0) || (a > node_number - 1) || (b < 0) || (b > node_number - 1)) {
            cout << "There are " << node_number << " nodes in total," << endl;
            cout << "\tplease choose two nodes (by index) to search the nodes: ";
            cin >> a; cout << "\tpess next number to choose the next node: "; cin >> b;
        }// get the index

        // Acquire path
        std::pair<std::pair<int,int>*,int> result = graph.path(node_list[a], node_list[b]);

        // Display the node in the path
        cout << endl;
        for (int i = 0; i < result.second; i++) {
            cout << "\tnode in the path: (" << result.first[i].first << ", " << result.first[i].second << ")\n";
        }
        Matrix<int> pathsR = nodes_marksR;
        Matrix<int> pathsG = nodes_marksG;
        Matrix<int> pathsB = nodes_marksB;
        add_patch<int, int, int>(result.first, result.second\
            , pathsR, pathsG, pathsB\
            , 0, 1, 1\
            , 3);
        add_patch<int, int, int>(&(node_list[a]), 1\
            , pathsR, pathsG, pathsB\
            , 0, 0, 1\
            , 3);
        add_patch<int, int, int>(&(node_list[b]), 1\
            , pathsR, pathsG, pathsB\
            , 0, 0, 1\
            , 3);
        pgm_ASCII::write_image_3C(pathsR, pathsG, pathsB, "../demo/nodes_on_the_pathway.ppm");
        

    } else {
        usage();
    }

    printf("The program ends\n\tpress any key and Enter to quit\n");
    char q; cin >> q;
    order_file.close(); gps_file.close();
    return 0;
}
