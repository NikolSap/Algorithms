#include "Heap.h"
#include <iostream>
using std::cout;
using std::endl;

int Heap::Left(int node)
{
	return (2*node + 1);
}

int Heap::Right(int node)
{
	return (2 * node + 2);
}

int Heap::Parent(int node)
{
	return (node-1)/2;
}

void Heap::fixHeapDown(int node)
{
	int head;
	int left = Left(node);
	int right = Right(node);

	if (left<heapVector.size() && heapVector[node].key > heapVector[left].key)
		head = left;
	else 
		head = node;

	if(right<heapVector.size() && heapVector[head].key>heapVector[right].key)
		head=right;

	if (head != node)
	{
		swapItems(node, head);
		fixHeapDown(head);
	}

}

void Heap::fixHeapUp(int node)
{
	int parent = Parent(node);
	
	while (node > 0 && heapVector[parent].key> heapVector[node].key)
	{

		if (parent != node)
		{
			swapItems(node, parent);

		}
		node = parent;
		parent = Parent(node);
	}
	
}

void Heap::swapItems(int index1, int index2)
{
	
		Item temp = heapVector[index1];
		heapVector[index1] = heapVector[index2];
		heapVector[index2] = temp;
		vertexIndexInHeap[heapVector[index1].vertex-1] = index1;
		vertexIndexInHeap[heapVector[index2].vertex - 1] = index2;
	//	heapVector[index1].edge.setHeapIndex(index1);
	//	heapVector[index2].edge.setHeapIndex(index2);
		//saveHeapIndexInEdge(data[index1], index1);
		//saveHeapIndexInEdge(data[index2], index2);

		
	

}





int Heap::DeleteItem(int index)
{
	if (heapVector.size() < 1)
	{
		throw("empty Heap!");
	}
	swapItems(index, heapVector.size() - 1);
	Item res = heapVector[heapVector.size() - 1];

	if (heapVector.size() > 1 && heapVector[Parent(index)].key>heapVector[index].key)
		fixHeapUp(index);
	else
		fixHeapDown(index);

	return res.vertex;

}

void Heap::Build(int* keys, int size,int* vertexIndexArry)
{
	/*if ( data.size() != key.size())
		throw("incomplete Keys or Data items");*/

	heapVector.reserve(size);//for efficiency,reserve capacity in vector
	vertexIndexInHeap = vertexIndexArry;//pointer to index arry outside the heap;
	for (int i = 0; i < size; i++)//data is between 1-n
	{
		vertexIndexInHeap[i] = i;
		heapVector.push_back({i+1,keys[i] });
	}


	for (int i = heapVector.size() / 2 - 1; i >= 0; i--)
			fixHeapDown(i);


}

int Heap::DeleteMin()
{

	if (heapVector.size() < 1)
	{
		throw("empty Heap!");
	}
	Item res= heapVector[0];
	heapVector[0] = heapVector[heapVector.size() - 1];
	vertexIndexInHeap[heapVector[0].vertex-1] = 0;
	heapVector.pop_back();
	fixHeapDown(0);
	return res.vertex;
}

void Heap::DecreaseKey(int place, int newKey)
{
	if (place > heapVector.size() - 1)
		throw("Exception:overflow heap memory!");

	if (heapVector[place].key < newKey)
		std::cout << "Error:the new key is greater than old key" << endl;
	else
	{
		heapVector[place].key = newKey;
		fixHeapUp(place);
	}

}







/*for debug purpose ,no need to check!*/
void Heap ::print()
{
	for (int i = 0; i < heapVector.size(); i++)
		cout << heapVector[i].key << " ";
	cout << endl;
}

bool Heap::isHeap()
{
		// Start from root and go till the last internal
		// node
		for (int i = 0; i <= (heapVector.size() - 2) / 2; i++)
		{
			// If left child is greater, return false
			if (2*i+1< heapVector.size() && heapVector[Left(i)].key< heapVector[i].key)
				return false;

			// If right child is greater, return false
			if (2 * i + 2 < heapVector.size() && heapVector[Right(i)].key < heapVector[i].key)
				return false;
		}
		return true;

	
}

bool Heap::isHeap(int i,int n)
{

	if (i >= (n - 2) / 2)
		return true;

	// If an internal node and is
	// greater than its children,
	// and same is recursively
	// true for the children
	if ((heapVector[Left(i)].key> heapVector[i].key  &&
		heapVector[Right(i)].key > heapVector[i].key)
		&& isHeap(Left(i), n)
		&& isHeap(Right(i), n))
		return true;
	else
	return false;
}