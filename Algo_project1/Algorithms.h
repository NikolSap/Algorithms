#pragma once
#include "Graph.h"
#include "QuickSort.h"
#include "UnionFind.h"


int kruskal(Graph& graph, vector<Edge>& edgeList, vector<Edge>& F, bool isEdgeListSorted = false);
const int NOT_INIT = -1;
void Visit(Graph& graph, int vertex, int* ColorArr);
bool CheckIfGraphConnected(Graph& graph);
int Prim(Graph& graph, int* parnetArry);

int FindNewMSTAfterRemoveEdge(Graph& graph, vector<Edge>& MST_List, Edge& edgeToRemove, vector<Edge>& sortedList);