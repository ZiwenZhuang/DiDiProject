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

template<class Type>
class Heap{
	
  public:
  	int Heap_Size;
	int Heap_Capacity;
	Type * array;
	int mode;				/* mode is 0 for MinHeap, 1 for MaxHeap */

  	Heap(int n, int mode);
  	~Heap();
  	Type top() const;
  	Type pop();
  	void push(Type const a);
  	bool IsFull() const;
  	void PrintHeap() const;
};
template <class Type>
Heap<Type>::Heap( int n ,int b){
	Heap_Size = 0;
	Heap_Capacity=n;
	array=new (nothrow) Type [n+1];
	array[0]=Node(0,0);
	mode = b;
}
template <class Type>
Heap<Type>::~Heap(){
	delete[] array;
}

template <class Type>
Type Heap<Type>::top() const{
	return array[1];
}
template<class Type>
bool Heap<Type>::IsFull() const{
	return(Heap_Size == Heap_Capacity);
}
template<class Type>
Type Heap<Type>::pop(){
	Type pop;
	int i=1;						/*index*/
	Type temp;
	pop=array[1];
	array[1]=array[Heap_Size];
	Heap_Size--;
	while (2*i <= Heap_Size){		/* left child is in the heap */
		if (2*i + 1 <= Heap_Size){	/* right child is in the heap */
			if (mode == 0){			/* MinHeap */
				if(array[2*i + 1].GetKey()>array[2*i].GetKey()){	/*Left child is smaller */
					if (array[i].GetKey()> array[2*i].GetKey()){	/* array[i] is not the smallest, change*/
						temp= array[i];
						array[i]=array[2*i];
						array[2*i]=temp;
						i = 2*i;
					}else{						
						break;					/* array[i] is already the smallest. break*/
					}
				}else{							/* Right child is smaller */
					if(array[i].GetKey()> array[2*i+1].GetKey()){	/* array[i] is not the smallest, change*/
						temp= array[i];
						array[i]=array[2*i+1];
						array[2*i+1]=temp;
						i = 2*i+1;
					}else{
						break;
					}
				}
			}else{								/* MaxHeap*/
				if(array[2*i + 1].GetKey()>array[2*i].GetKey()){	/*Right child is larger */
					if (array[i].GetKey() < array[2*i +1].GetKey()){	/* array[i] is not the largest, change*/
						temp= array[i];
						array[i]=array[2*i+1];
						array[2*i+1]=temp;
						i = 2*i + 1;
					}else{						
						break;					/* array[i] is already the largest. break*/
					}
				}else{							/* Left child is larger */
					if(array[i].GetKey()<= array[2*i].GetKey()){	/* array[i] is not the largest, change*/
						temp= array[i];
						array[i]=array[2*i];
						array[2*i]=temp;
						i = 2*i;
					}else{
						break;
					}
				}
			}
		}else{									/* Left child is in the array, right child is missing*/
			if (mode == 0){
				if (array[i].GetKey()< array[2*i].GetKey()){
					break;
				}else{
					temp=array[i];
					array[i]=array[2*i];
					array[2*i]=temp;
					break;
				}
			}else{
				if(array[i].GetKey()>array[2*i].GetKey()){
					break;
				}else{
					temp=array[i];
					array[i]=array[2*i];
					array[2*i]=temp;
					break;
				}
			}
		}	
	}
	return pop;
}
template <class Type>
void Heap<Type>::push(Type const a){
	int i;
	Type temp;
	Heap_Size++;
	array[Heap_Size]=a;
	i = Heap_Size;
	while (i>1){
		if(mode == 0){
			if (array[i].GetKey() < array[i/2].GetKey()){
				temp=array[i];
				array[i]=array[i/2];
				array[i/2]=temp;
				i=i/2;
			}else{
				break;
			}
		}else{
			if(array[i].GetKey() > array[i/2].GetKey()){
				temp = array[i];
				array[i]=array[i/2];
				array[i/2]=temp;
				i=i/2;
			}else{
				break;
			}
		}
	}
}

template <class Type>
void Heap<Type>::PrintHeap() const{
	int i=1;
	int j=0;
	while ((1<< j) < Heap_Size +1){
		printf("(%d, %d)",array[i].priority, array[i].least_char);
		i++;
		while (i >= (1<< j) && i <(1<< (j+1))){
			if(i <= Heap_Size){
				printf(" (%d, %d)", array[i].priority, array[i].least_char);
			}else{
				printf(" S");
			}
			i ++;
		}
		printf("\n");
		j++;
	}
}
