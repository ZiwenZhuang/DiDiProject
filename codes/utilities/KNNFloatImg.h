#ifndef KNNFLOAT_H
#define KNNFLOAT_H

#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

#include <math.h>
#include <chrono>
#include <omp.h>

using namespace std;

void KNN_removal(const float * imgIn, int * imgOut, const unsigned int &width, const unsigned int &height, const unsigned int &kernelSize, const unsigned int k, const float distance_thr);


#endif