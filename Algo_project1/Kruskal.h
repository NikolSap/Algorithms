#pragma once
#include "Graph.h"
#include "Edge.h"
#include "QuickSort.h"
#include "UnionFind.h"

int kruskal(Graph& graph, vector<Edge>& edgeList, int sizeOfEdges, vector<Edge>& F, bool isSorted);