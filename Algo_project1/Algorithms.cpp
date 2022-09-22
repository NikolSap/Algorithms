#include "Algorithms.h"
#include "Heap.h"

int kruskal(Graph& graph, vector<Edge>& edgeList, vector<Edge>& F, bool isEdgeListSorted)
{
    F.clear();
    int n = graph.getNumVertices();
    int pu, pv;
    DisjointSets UF(n);
    int weightSum = 0;
    if (!isEdgeListSorted)
        quickSort(edgeList, 0, edgeList.size() - 1);

    for (int i = 0; i < n; i++)
    {
        UF.MakeSet(i + 1);
    }

    for (int i = 0; i < edgeList.size(); i++)
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


int Prim(Graph& graph, int* parnetArry)
{

    Heap minHeap;
    int currentVertx, treeWeight;
    int VertxNum = graph.getNumVertices();

    treeWeight = 0;
    int* vertexIndexInHeap = new int[VertxNum];
    bool* inTree = new bool[VertxNum];
    int* minWeightEdges = new int[VertxNum];
    parnetArry = new int[VertxNum];
    if (parnetArry == nullptr || minWeightEdges == nullptr || inTree == nullptr || vertexIndexInHeap == nullptr)
    {
        throw("ERROR:memory allocation failed!!");
    }
    inTree[0] = false;
    minWeightEdges[0] = 0;
    parnetArry[0] = NOT_INIT;
    vertexIndexInHeap[0] = NOT_INIT;
    for (int i = 1; i < VertxNum; i++)
    {
        inTree[i] = false;
        minWeightEdges[i] = inf;
        parnetArry[i] = NOT_INIT;
    }
    minHeap.Build(minWeightEdges, VertxNum, vertexIndexInHeap);

    while (minHeap.isEmpty() == false)
    {
        currentVertx = minHeap.DeleteMin();
        inTree[currentVertx - 1] = true;
        Graph::AdjList currVertexAdj = graph.GetAdjList(currentVertx);
        for (Graph::AdjListNode* currNode = currVertexAdj.head; currNode != nullptr; currNode = currNode->getNext())
        {
            int VertxAdjName = currNode->getEdge().getDest() ;
            if (inTree[VertxAdjName - 1] == false && currNode->getEdge().getWeight() < minWeightEdges[VertxAdjName - 1])
            {
                minWeightEdges[VertxAdjName - 1] = currNode->getEdge().getWeight();
                parnetArry[VertxAdjName - 1] = currentVertx;
                minHeap.DecreaseKey(vertexIndexInHeap[VertxAdjName - 1], currNode->getEdge().getWeight());
            }
        }

    }


    for (int i = 0; i < VertxNum; i++)
        treeWeight += minWeightEdges[i];


    delete[] vertexIndexInHeap;
    delete[] inTree;
    delete[] minWeightEdges;

    return treeWeight;
}

int FindNewMSTAfterRemoveEdge(Graph& graph,vector<Edge>& MST_List,Edge& edgeToRemove,vector<Edge>& sortedList)
{
    bool foundEdgeInMST = false;
    int sumMSTWeight=0;
    int ind;
    for (ind = 0; ind < MST_List.size()&& !foundEdgeInMST; ind++)
    {
        if (MST_List[ind] == edgeToRemove)
            foundEdgeInMST = true;
    }
    if (foundEdgeInMST)
    {
        for (ind = 0; ind < sortedList.size(); ind++)
        {
            if (sortedList[ind] == edgeToRemove)
                sortedList.erase(sortedList.begin() + ind);
        }
        graph.RemoveEdge(edgeToRemove.getSrc(), edgeToRemove.getDest());
        if (CheckIfGraphConnected(graph))
        {
            kruskal(graph, sortedList, MST_List, true);
        }
        else
        {
            cerr<<"No MST";
            exit(1);
        }
   
    }
    for (int ind = 0; ind < MST_List.size(); ind++)
    {
        sumMSTWeight += MST_List[ind].getWeight();
    }
  


    return sumMSTWeight;
    
}



bool CheckIfGraphConnected(Graph& graph)
{

    int VertxNum = graph.getNumVertices();
    int* colorArry = new int[VertxNum];
    if (!colorArry)
        exit(1);
    for (int i = 0; i < VertxNum; i++)
        colorArry[i] = graph.Color::WHITE;

    Visit(graph, 1, colorArry);
    for (int i = 0; i < VertxNum; i++)
        if (colorArry[i] != graph.Color::BLACK)
			 return false;
    return true;
}
void Visit(Graph& graph, int vertex, int* ColorArr)
{
    ColorArr[vertex - 1] = graph.Color::GRAY;
    Graph::AdjList currVertexAdj = graph.GetAdjList(vertex);
    for (Graph::AdjListNode* currNode = currVertexAdj.head; currNode != nullptr; currNode = currNode->getNext())
    {
        if (ColorArr[currNode->getEdge().getDest() - 1] == graph.Color::WHITE)
            Visit(graph, currNode->getEdge().getDest(), ColorArr);

    }
    ColorArr[vertex - 1] = graph.Color::BLACK;

}



