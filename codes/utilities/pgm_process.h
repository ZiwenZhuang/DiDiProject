/* This headfile defines the basic method to write to pgm file basd on given 
ray scale matrix.
    And for the simplicity of the project, we process only the ASCII mode of pgm
file, where the mode has to be "P2".
    In the given matrix, you don't have to normalize it, just give the greatest
and the smallest value of the matrix.
*/
#ifndef pgm_ASCII_H
#define pgm_ASCII_H

#include <fstream>
#include <string>
#include <sstream>

#include "matrix.h"

using namespace std;

namespace pgm_ASCII {

    /* This method will read the gray scale image into the defined matrix object.
        You can either provide the filename (including directory) or the opened
    filestream.
        Be sure to provided the target matrix instance to store the information.
        The return value indicates whether the read process is sucessful,
            0 is sucessful; -1 is error occurred;
    */
    template <class T> int read_image(Matrix<T> &target, string &filename);
    template <class T> int read_image(Matrix<T> &target, ifstream &file);
    template <class T> int read_image(Matrix<T> &target, fstream &file);

    /* This methods will write the given matrix into the file once.
        Also, it returns 0 on sucess; -1 on failed;
        And you are only allowed to provide the file name instead of any form of
    file stream.
    */
    template <class T> int write_image(Matrix<T> &target, string filename);

    /* Write a 3 channel ppm file, which requires three matrix as three channel.
        Three types has to be number type such as int/float/double.
    */
    template <class T, class U, class Y> int write_image_3C(Matrix<T> &targetR\
		, Matrix<T> &targetG, Matrix<T> &targetB, string filename);
}

#include "pgm_process.tpp"

#endif