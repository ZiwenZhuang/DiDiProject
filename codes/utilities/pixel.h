#ifndef PIXEL_DEF
#define PIXEL_DEF

#include <iostream>
#include <string>
#include <fstream>

template <class Type>
class point{
public:
	Type longitude;
	Type latitude;
};
int * pixel(fstream& file,int pixelx,int pixely);


#endif