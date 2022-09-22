#pragma once
#include "Edge.h"
#include "Vertex.h"
#include <vector>
using std::vector;
 class Heap
{
	 
	 class Item {
		 int vertex;
		 int key;
	 public:
		 Item(int _vertex, int _key) :vertex(_vertex), key(_key) {}
		 friend class Heap;
	 };

private:


	vector<Item> heapVector;
	int* vertexIndexInHeap = nullptr;
	static int Left(int node);
	static int Right(int node);
	static int Parent(int node);
	void fixHeapDown(int node);
	void fixHeapUp(int node);
	void swapItems(int index1, int index2);
	//void saveHeapIndexInVertex(Item& item, int index);
	int DeleteItem(int index);
public:
	//void createEmptyHeap(const bool& freeMemory);
	Heap(){}
	void Build(int* keys,int size,int* vertexIndexArry);
	bool isEmpty() { return heapVector.empty(); }
	int DeleteMin();
	
	void DecreaseKey(int place, int newKey);


	/*for debug purpose ,no need to check!*/
	int getSize()const { return heapVector.size(); }
	void print();
	bool isHeap();
	bool isHeap(int i, int n);
	
};

