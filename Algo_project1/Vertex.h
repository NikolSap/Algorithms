#pragma once
#include <string>
#include <iostream>
using std::ostream;
using std::string;

class Vertex
{
	int _indexHeap=-1;
	int _name=-1;

//	int _priority=-1;
//	string _value="";

public:
	Vertex(){}
	Vertex(int name): _name(name) {}
	int getHeapIndex()const { return _indexHeap; }
	int getName()const { return _name; }
	
	friend ostream& operator<<(ostream& os, const Vertex& item){
		os << item._name;
		return os;
	}
	void setHeapIndex(int index){ _indexHeap=index; }
};


