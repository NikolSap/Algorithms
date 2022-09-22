#include "Kruskal.h"

int kruskal(Graph& graph, vector<Edge>& edgeList,int sizeOfEdges, vector<Edge>& F,bool isSorted)
{
	F.clear();
	int n = graph.getNumVertices();
	int pu, pv;
	DisjointSets UF(n);
	int weightSum = 0;
	if(!isSorted)
		quickSort(edgeList, 0, sizeOfEdges -1);

	for (int i = 0; i < n; i++)
	{
		UF.MakeSet(i + 1);
	}

	for (int i = 0; i < sizeOfEdges; i++)
	{
		pu = UF.find(edgeList[i].getSrc());
		pv = UF.find(edgeList[i].getDest());
		if (pu != pv)
		{
			F.push_back(edgeList[i]);
			UF.Union(pu, pv);
			weightSum += edgeList[i].getWeight();
		}
	}
	return weightSum;
}
