#ifndef GRAPH_H
#define GRAPH_H

#include <utility>

template<class T>
class node;

template<class T>
class graph{
private:
	node<T>** adj_l;
	int now_i;
	T diff;
public:
	graph(int num,T dif=0.001):diff(dif),now_i(0){adj_l=new node<T>*[num];};
	~graph(){delete[] adj_l;};
	void create_node(T la, T lo);
	bool equal(T a, T b);
	void create_road(T la1,T lo1, T la2, T lo2);
	//bool is_connected(T la1, T lo1, T la2, Tlo2);
	std::pair<node<T>**,int> find_neighbor(T la, T lo);
};


template<class T>
class node{
private:
	std::pair<const T,const T> pos;
	int* neighbor;
	int neighbor_num;

	//template<typename T>
public:
	friend class graph<T>;
	node(T la, T lo,int num):pos(std::pair<T,T>(la,lo)),neighbor_num(0){
		neighbor=new int[num];
	};
	node():neighbor_num(0){};
	~node(){delete[] neighbor;};
};

#include "graph.hpp"

#endif


