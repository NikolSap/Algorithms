#pragma once
#include "Edge.h"
#include <iostream>
using namespace std;
#define inf INT32_MAX




class Graph
{

public:


    class AdjListNode
    {
        Edge edge;
        //  int vertex;
          //int weight;
        AdjListNode* next = nullptr;
        AdjListNode* prev = nullptr;
        friend class Graph;
    public:
        AdjListNode(int srcV, int dstV, int weight) :edge(srcV, dstV, weight) {}
        AdjListNode* getNext() { return next; }
        const Edge& getEdge() { return edge; }
    };

    struct AdjList
    {
        AdjListNode* head=nullptr;
    };

private:

    int numVertices=0;
    AdjList* adjLists=nullptr;
    int numberOfEdges;
public:
    Graph(int n);
    Graph() {}
    ~Graph();
    enum Color { WHITE = -1, GRAY, BLACK };
    void MakeEmptyGraph(int n);
    bool IsAdjacent(int u, int v);
    AdjList GetAdjList(int u);
    void AddEdge(int u, int v, int c);
    void RemoveEdge(int u, int v);
    //   AdjListNode* createNode(int v);
    //   void printGraph();
    int getNumVertices() { return numVertices; }
    void setNumberOfEdges(int numEdges) { numberOfEdges = numEdges; }
    int getNumOfEdges() { return numberOfEdges; }
private:
    void deleteGraph();
    void removeNodeFromAdjList(AdjList* adjList, AdjListNode* nodePrev);
    void deleteNodeFromHead(AdjList* adjList);
    void deleteNodeFromInnerPlace(AdjListNode* nodePrev);

};