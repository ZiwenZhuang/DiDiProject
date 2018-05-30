/* This headfile defines the basic method to write to pgm file basd on given 
ray scale matrix.
    In the given matrix, you don't have to normalize it, just give the greatest
and the smallest value of the matrix.
*/
#include <fstream>
#include <string>

using namespace std;

#include "matrix.h"

/* This method will read the gray scale image into the defined matrix object.
    You can either provide the filename (including directory) or the opened
filestream.
    Be sure to provided the target matrix instance to store the information.
    The return value indicates whether the read process is sucessful.
*/
int read_image(Matrix& target, string filename);
int read_image(Matrix& target, ifstream file);
int read_image(Matrix& target, fstream file);