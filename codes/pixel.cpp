#include <iostream>
#include <string>
#include <fstream>

using namespace std;
/* Type could be double or int, double for gps, int for map */
template <class Type>
class point{
public:
	Type longitude;
	Type latitude;
};
/* lo1/lo2 is longitude, lo1<lo2; la1/la2 is latitude, la1<la2*/
/* return a point in map*/ 
point<int>* location(double lo1,double lo2,double la1, double la2, int pixelx,int pixely,point<double> p){
	int x;
	int y;
	point<int>* Pmap;
	x=(int)(((p.longitude-lo1)/(lo2-lo1))*pixelx);
	y=(int)(((p.latitude-la1)/(la2-la1))*pixely);
	Pmap=new point<int> [1];
	Pmap->longitude=x;
	Pmap->latitude=y;
	return Pmap;
}

string read_a_line(fstream& file) {
    if (!file.is_open()) {
        fprintf(stderr, "Error detected, in read_a_line(): the fstream to read is not open yet\n");
    }
    string one_line;
    getline(file, one_line);
    return one_line;
}
/* sw-- south west point; se-- south east point; nw-- north west point; pixelx/pixely is the pixel informarion(x*y) */
int * pixel(fstream& file,point<double> sw, point<double> se,point<double> nw,int pixelx,int pixely){
	int* map;
	int i=0;
	string lo;
	string la;
	string one_line;
	point<int>* P;
	point<double> L;
	map=new int [pixelx*pixely];
	for (i=0;i< pixelx*pixely;i++){
		map[i]=0;
	}
	one_line=read_a_line(file);
	while(one_line!=""){
		lo=one_line.substr(77,9);la=one_line.substr(87,8);
		L.longitude=stod(lo);
		L.latitude=stod(la);
		P=location(sw.longitude,se.longitude,sw.latitude,nw.latitude,pixelx,pixely,L);
		map[P->longitude*pixely+P->latitude]++;
		delete P;
		one_line=read_a_line(file);
	}
	return map;

}
int main(){
	return 0;
}
/*int main(){
	int * map;
	point<double> sw;
	point<double> se;
	point<double> nw;
	int c;
	fstream gps_file; gps_file.open("../data/gps_20161101", ios_base::in);
	sw.longitude=104.042140;
	sw.latitude=30.652940;
	se.longitude=104.129580;
	se.latitude=30.652940;
	nw.longitude=104.042140;
	nw.latitude=30.727750;
	map=pixel(gps_file,sw,se,nw,1024,1024);
	for (int i=0;i<1024*1024;i++){
		printf("%d\n",map[i] );
	}
	return 0;
}*/