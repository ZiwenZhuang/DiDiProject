#include <string>
#include <iostream>


using namespace std;

template<class T>
void graph<T>::create_node(T la, T lo){
	node<T> *new_n = new node<T>(la,lo,10);
	adj_l[now_i]=new_n;
	now_i++;
}

template<class T>
void graph<T>::create_road(T la1,T lo1, T la2, T lo2){
	int i;
	int index1,index2,count=0;
	printf("%d\n",now_i);
	for(i=0;i<now_i;i++){
		if(count==2){break;}
		if(equal(adj_l[i]->pos.first,la1) && equal(adj_l[i]->pos.second,lo1)){
			count++;
			index1=i;
		}
		if(equal(adj_l[i]->pos.first,la2) && equal(adj_l[i]->pos.second,lo2)){
			count++;
			index2=i;
		}
	}
	if(count!=2){return;}
	adj_l[index1]->neighbor[adj_l[index1]->neighbor_num]=index2;
	adj_l[index2]->neighbor[adj_l[index2]->neighbor_num]=index1;
	adj_l[index1]->neighbor_num++;
	adj_l[index2]->neighbor_num++;
}

/*bool graph::is_connected(T la1, T lo1, T la2, T lo2){
	int i;
	for(i=0;i<now_i;i++){
		if(adj_l[i]->neighbor){}
		
	}
}*/

template<class T>
bool graph<T>::equal(T a, T b){
	if(a+diff<=b && b<=a+diff){
		return true;
	}else{return false;}
}

template<class T>
std::pair<node<T>**,int> graph<T>::find_neighbor(T la, T lo){
	int i,neighbor_num,j;
	int* temp_l;
	node<T>** neighbor_l;
	for(i=0;i<now_i;i++){
		if(equal(adj_l[i]->pos.first,la) && equal(adj_l[i]->pos.second,lo)){
			temp_l=adj_l[i]->neighbor;
			neighbor_num=adj_l[i]->neighbor_num;
			neighbor_l=new node<T>*[neighbor_num];
			for(j=0;j<neighbor_num;j++){
				neighbor_l[j]=adj_l[temp_l[j]];
			}
			return std::pair<node<T>**,int>(neighbor_l,neighbor_num);
		}
	}
	return std::pair<node<T>**,int>(nullptr,0);
}