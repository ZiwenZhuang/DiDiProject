#include "pgm_process.h"

namespace pgm_ASCII {

    // check the pgm file mode
    static bool check_mode(string &a_line) {
        if (a_line.compare("P2") != 0) {
            fprintf(stderr, "Cannot open pgm file that is not in P2 mode!");
            return false;
        }
        return true;
    }

    template <class T> int read_image(Matrix<T> &target, string &filename) {
        ifstream file; file.open(filename.c_str(), ios_base::in);
        string a_line; getline(file, a_line);
        // check mode
        if (!check_mode(a_line)) return -1;
        // read matrix size
        unsigned int num; 
        file >> num; target.setRowNum(num);
        file >> num; target.setColNum(num);
        // read data as unsigned int
        unsigned int total = target.getRowNum() * target.getColNum();
        unsigned int* array = new unsigned int [total];
        for (unsigned int i = 0; i < target.getColNum(); i++) {
            getline(file, a_line); stringstream ss (a_line);
            for (unsigned int j = 0; j < target.getRowNum(); j++) {
                ss >> target[j][i];
            }
        }
        return 0;
    }
    template <class T> int read_image(Matrix<T> &target, ifstream &file) {
        if (!file.is_open()) {
            fprintf(stderr, "Error detected in read_image, your provided a un-opened file stream");
            return -1;
        }
        string a_line; getline(file, a_line);
        // check mode
        if (!check_mode(a_line)) return -1;
        // read matrix size
        unsigned int num; 
        file >> num; target.setRowNum(num);
        file >> num; target.setColNum(num);
        // read data as unsigned int
        unsigned int total = target.getRowNum() * target.getColNum();
        unsigned int* array = new unsigned int [total];
        for (unsigned int i = 0; i < target.getColNum(); i++) {
            getline(file, a_line); stringstream ss (a_line);
            for (unsigned int j = 0; j < target.getRowNum(); j++) {
                ss >> target[j][i];
            }
        }
        return 0;
    }
    template <class T> int read_image(Matrix<T> &target, fstream &file) {
        if (!file.is_open()) {
            fprintf(stderr, "Error detected in read_image, your provided a un-opened file stream");
            return -1;
        }
        string a_line; getline(file, a_line);
        // check mode
        if (!check_mode(a_line)) return -1;
        // read matrix size
        unsigned int num; 
        file >> num; target.setRowNum(num);
        file >> num; target.setColNum(num);
        // read data as unsigned int
        unsigned int total = target.getRowNum() * target.getColNum();
        unsigned int* array = new unsigned int [total];
        for (unsigned int i = 0; i < target.getColNum(); i++) {
            getline(file, a_line); stringstream ss (a_line);
            for (unsigned int j = 0; j < target.getRowNum(); j++) {
                ss >> target[j][i];
            }
        }
        return 0;
    }

    template <class T> int write_image(Matrix<T> &target, string filename) {
        if (!target.initialized()) {
            fprintf(stderr, "Error detected, you let me write a matrix that has no data");
            return -1;
        }
        // Write basic information first
        ofstream file; file.open(filename.c_str(), ios_base::out);
        file << "P2\n" << target.getRowNum() << " " << target.getColNum();
        // detect the greatest value
        T greatest; T* pVal = target.get_data();
        greatest = *pVal;
        for (unsigned int i = 1; i < target.getRowNum() * target.getColNum(); i++) {
            greatest = (greatest < pVal[i])? pVal[i]: greatest;
        }
        // set the greatest value manually, in case the greatest value is too large to diaplay.
        unsigned int set_great = 1024;
        if (greatest <= set_great) {
            file << endl << greatest;
            for (int i = target.getColNum()-1; i >= 0; i--) {
                file << endl << ((target[0][i] > 0) ? (target[0][i]) : 0);
                for (unsigned int j = 1; j < target.getRowNum(); j++) {
                    file << "\t" << ((target[j][i] > 0) ? (target[j][i]) : 0);
                }
            }
            return 0;
        } else {
            file << endl << set_great;
            for (int i = target.getColNum()-1; i >= 0; i--) {
                file << endl << ((target[0][i] > 0) ? (target[0][i] * set_great / greatest) : 0);
                for (unsigned int j = 1; j < target.getRowNum(); j++) {
                    file << "\t" << ((target[j][i] > 0) ? (target[j][i] * set_great / greatest) : 0);
                }
            }
            return 0;
        }
    }

}