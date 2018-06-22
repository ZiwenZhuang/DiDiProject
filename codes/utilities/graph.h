#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <fstream>

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
	void create_node(T lo, T la);
	bool equal(T a, T b);
	int find_node(T a,T b);
	void create_road(T lo1,T la1, T lo2, T la2);
	//bool is_connected(T la1, T lo1, T la2, Tlo2);
	double distance(int a, int b);
	int Min(bool*& visited, double*& distance);
	std::pair<std::pair<T,T>*,int> path(std::pair<T,T> a,std::pair<T,T> b);
	std::pair<node<T>**,int> find_neighbor(T lo, T la);
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
	node(T la, T lo,int num):pos(std::pair<T,T>(lo,la)),neighbor_num(0){
		neighbor=new int[num];
	};
	node():neighbor_num(0){};
	~node(){delete[] neighbor;};
};

/* This method read from file and returns a list of pairs that
contains each of the node that recognized by python program.
	Be sure to free the returned pointer when the list of nodes
are no longer in use.
*/
std::pair<int, int>* acquire_node_list(string filename, int &node_number);


#include "graph.hpp"

#endif


