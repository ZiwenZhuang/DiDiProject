#include <string>
#include <iostream>
#include <math.h>

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
	printf("Requested to generate roads on graph with %i nodes\n",now_i);
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
std::pair<node<T>**,int> graph<T>::find_neighbor(T lo, T la){
	int i,neighbor_num,j;
	int* temp_l;
	node<T>** neighbor_l;
	for(i=0;i<now_i;i++){
		if(equal(adj_l[i]->pos.first,lo) && equal(adj_l[i]->pos.second,la)){
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

template<class T>
int graph<T>::find_node(T a,T b){
	int i;
	for(i=0;i<now_i;i++){
		if(equal(adj_l[i]->pos.first,a) && equal(adj_l[i]->pos.second,b)){
			return i;
		}
	}
	return -1;
}



static std::pair<int, int> extractNumbers(string str) {
	std::pair<int, int> to_return = std::pair<int, int>(0, 0);
	int flag = 0; // 0 for the previous char is not a number
	string::iterator it;
	for (it = str.begin(); it != str.end(); it++) {
		if (isdigit(*it) && flag == 0) {
			// start reading digits
			to_return.first = *it - 48;
			flag = 1;
		} else if (isdigit(*it) && flag != 0) {
			// in the middle of reading digits
			to_return.first = to_return.first * 10 + *it - 48;
		} else if (!isdigit(*it) && flag != 0) {
			flag = 0;
			break;
		}
	}
	for (; it != str.end(); it++) {
		if (isdigit(*it) && flag == 0) {
			// start reading digits
			to_return.second = *it - 48;
			flag = 1;
		} else if (isdigit(*it) && flag != 0) {
			// in the middle of reading digits
			to_return.second = to_return.second * 10 + *it - 48;
		} else if (!isdigit(*it) && flag != 0) {
			flag = 0;
			break;
		}		
	}
	return to_return;
}

std::pair<int, int>* acquire_node_list(string filename, int &node_number) {
	std::fstream node_file;
	node_file.open(filename, ios_base::in);
	if (!node_file.is_open()) {
		cerr << "Could not open the read file when try to read the node number.\n";
		cerr << "\tThe file name is " << filename << endl;
		exit(0);
	}

	// iterate through the file and get the number of nodes
	int count = 0; string line; std::getline(node_file, line);
	while (!(node_file.eof())) {
		count++;
		std::getline(node_file, line);
	}
	node_file.close();
	cout << "acquiring nodes: found " << count << " nodes in total\n";
	// Now 'count' contains the number of nodes

	node_number = count;
	node_file.open(filename, ios_base::in);
	if (!node_file.is_open()) {
		cerr << "Could not open the read file when try to extract nodes\n";
		exit(0);
	}
	// read the nodes one by one
	std::pair<int, int>* to_return = new std::pair<int, int> [count];
	for (int i = 0; i < count; i++) {
		getline(node_file, line);
		to_return[i] = extractNumbers(line);
	}

	return to_return;
}


template<class T>
double graph<T>::distance(int a, int b){
	T x1=adj_l[a]->pos.first;
	T y1=adj_l[a]->pos.second;
	T x2=adj_l[b]->pos.first;
	T y2=adj_l[b]->pos.second;
	return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}
template<class T>
std::pair<std::pair<T,T>*,int> graph<T>::path(std::pair<T,T> a,std::pair<T,T> b){
	bool visited[now_i];
	double dist[now_i];				/* distance*/
	int previous[now_i];
	int i=0;
	bool found=false;
	int neighbor_i;
	std::pair<T,T>* Path=new std::pair<T,T> [now_i];
	int length=0;
	int min;
	int start=find_node(a.first,a.second);
	int end = find_node(b.first,b.second);
	for (i=0;i<now_i;i++){
		visited[i]=false;
		dist[i]=std::numeric_limits<double>::infinity();
		previous[i]=-1;
	}
	dist[start]=distance(start,end);
	min=Find_Min(visited,dist,now_i);
	while(min!=std::numeric_limits<double>::infinity()){
		visited[min]=true;
		if (min == end){
			found=true;
			break;
		}
		for(i=0;i<adj_l[min]->neighbor_num;i++){
			neighbor_i=adj_l[min]->neighbor[i];
			if (visited[neighbor_i]==true){
				continue;
			}
			if (dist[neighbor_i] > distance(min,neighbor_i)+distance(neighbor_i,end)){
				dist[neighbor_i]=distance(min,neighbor_i)+distance(neighbor_i,end);
				previous[neighbor_i]=min;
			}
		}
		min=Find_Min(visited,dist,now_i);
	}
	if (found==false){
		return std::pair<std::pair<T,T>*,int>(nullptr,0);
	}
	length=0;
	while (previous[end]!=-1){
		Path[length]=adj_l[end]->pos;
		length++;
		end=previous[end];
	}
	return std::pair<std::pair<T,T>*,int>(Path,length);
}


int Find_Min(bool* V, double* L,int size){
	int i=0;
	double min_distance=std::numeric_limits<double>::infinity();
	int min_index;
	for (i=0;i<size;i++){
		if (V[i]==false && L[i]<min_distance){
			min_distance=L[i];
			min_index=i;
		}
	}
	return min_index;
}
