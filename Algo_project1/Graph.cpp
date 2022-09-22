#include  "Graph.h"

Graph::Graph(int n)
{
    MakeEmptyGraph(n);
}


void Graph::MakeEmptyGraph(int n)
{
    if (n < 1)
        throw("invalid number on vertex in graph");

    deleteGraph();
    numVertices = n;
    int i;
    adjLists = new AdjList[numVertices];
    if (!adjLists)
        exit(1);

    for (i = 0; i < numVertices; i++)
    {
        adjLists[i].head = new AdjListNode(i + 1, i + 1, 0);//edge of u->u with wegith 0;
    }
}

bool Graph::IsAdjacent(int u, int v)
{
    AdjList uAdjList = adjLists[u - 1];
    AdjListNode* currAdjNode = uAdjList.head;
    while (currAdjNode->getNext() != nullptr)
    {
       
        if (currAdjNode->edge.getDest() == v)
        {
            return true;
        }
        currAdjNode = currAdjNode->next;
    }

    return false;
}

Graph::AdjList Graph::GetAdjList(int u)
{
    return adjLists[u - 1];
}

void Graph::AddEdge(int u, int v, int c)
{
    // Add edge from u to v
    AdjListNode* newNode = new AdjListNode(u, v, c);
    newNode->next = adjLists[u - 1].head;
    adjLists[u - 1].head->prev = newNode;
    adjLists[u - 1].head = newNode;

    // Add edge from v to u
    newNode = new AdjListNode(v, u, c);
    newNode->next = adjLists[v - 1].head;
    adjLists[v - 1].head->prev = newNode;
    adjLists[v - 1].head = newNode;

    adjLists[v - 1].head->edge.setOppositeDirectionEdge(&(adjLists[u - 1].head->edge));
    adjLists[u - 1].head->edge.setOppositeDirectionEdge(&(adjLists[v - 1].head->edge));
}

void Graph::RemoveEdge(int u, int v)
{
    if (IsAdjacent(u, v))
    {
        AdjListNode* currAdjNode = adjLists[u - 1].head;
        while (currAdjNode != nullptr && currAdjNode->edge.getDest() != v)
        {
            currAdjNode = currAdjNode->next;

        }
        removeNodeFromAdjList(&adjLists[u - 1], currAdjNode->prev);

        currAdjNode = adjLists[v - 1].head;
        while (currAdjNode != nullptr && currAdjNode->edge.getDest() != u)
        {
            currAdjNode = currAdjNode->next;
        }
        removeNodeFromAdjList(&adjLists[u - 1], currAdjNode->prev);
    }
    else
    {
        throw("Edge not exist in graph");
    }
}
void Graph::deleteGraph()
{
    AdjListNode* currNode;
    AdjListNode* tempNode;
    for (int i = 0; i < numVertices; i++)
    {
        currNode = adjLists[i].head;
        while (currNode != nullptr)
        {
            tempNode = currNode;
            currNode = currNode->next;
            delete tempNode;
        }
    }
    delete[] adjLists;
    numVertices = 0;
}
void Graph::removeNodeFromAdjList(AdjList* adjList, AdjListNode* nodePrev)
{
    if (nodePrev == nullptr)/*there are not prev cell because the yCell if the head of the list*/
        deleteNodeFromHead(adjList);
    else
        deleteNodeFromInnerPlace(nodePrev);/*prev is inner cell on the list*/
}

void Graph::deleteNodeFromHead(AdjList* adjList)
{
  
    adjList->head = adjList->head->next;
    delete adjList->head->prev;
    adjList->head->prev = nullptr;
}

void Graph::deleteNodeFromInnerPlace(AdjListNode* nodePrev)
{
    AdjListNode* cellToDel = nodePrev->next;
    nodePrev->next = cellToDel->next;
    delete cellToDel;
}
Graph::~Graph()
{
    
    deleteGraph();
}

