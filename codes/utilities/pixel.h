#ifndef PIXEL_DEF
#define PIXEL_DEF

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <class Type>
class point{
public:
	Type longitude;
	Type latitude;
};
int * pixel(fstream& file,int pixelx,int pixely);

#endif