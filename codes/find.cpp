#include <string>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
	ifstream fin;
	string input,lo,la;
	//int i=0;
	double se_lo,se_la,ne_lo,ne_la,sw_lo,sw_la,nw_lo,nw_la;
	double longitude,latitude;
	fin.open("/home/wangyh/proj/DiDiProject/data/gps_20161101");
	getline(fin,input);
	lo=input.substr(77,9);la=input.substr(87,8);
	//printf("%s %s\n",lo.c_str(),la.c_str());
	longitude=stod(lo);latitude=stod(la);
	//istringstream convert(lo);convert>>longitude;
	//istringstream convert2(la);convert2>>latitude;
	se_lo=longitude;ne_lo=longitude;sw_lo=longitude;nw_lo=longitude;
	se_la=latitude;ne_la=latitude;sw_la=latitude;nw_la=latitude;
	//printf("%s %f \n \n",lo,longitude);
	while(getline(fin,input)){
		lo=input.substr(77,9);la=input.substr(87,8);
		longitude=stod(lo);latitude=stod(la);
		//istringstream convert3(lo);convert3>>longitude;
		//istringstream convert4(la);convert4>>latitude;
		//printf("%s %f\n",la.c_str(),latitude);
		//printf("`````%f \n",longitude);
		if(latitude>ne_la){ne_la=latitude;nw_la=latitude;}
		if(latitude<se_la){se_la=latitude;sw_la=latitude;}
		if(longitude<nw_lo){nw_lo=longitude;sw_lo=longitude;}
		if(longitude>ne_lo){ne_lo=longitude;se_lo=longitude;}
		//i++;
		//if(i>=30){printf("sss\n"); break;}
	}
	printf("northwest:longitude %f,latitude %f\n",nw_lo,nw_la);
	printf("northeast:longitude %f,latitude %f\n",ne_lo,ne_la);
	printf("southwest:longitude %f,latitude %f\n",sw_lo,sw_la);
	printf("southeast:longitude %f,latitude %f\n",se_lo,se_la);
	return 0;
}