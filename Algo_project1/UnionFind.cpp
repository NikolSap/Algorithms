#include "UnionFind.h"

DisjointSets::DisjointSets(int n)
{
    parent = new int[n];
    rank = new int[n];
    if (!parent || !rank)
        throw("allocation failed");
}

void DisjointSets::MakeSet(int v)
{
    parent[v - 1] = -1;
    rank[v - 1] = 1;
}


int DisjointSets::find(int v)
{
    if (parent[v - 1] == -1)
        return v;

    return parent[v - 1] = find(parent[v - 1]);
}

void DisjointSets::Union(int u, int v)
{
    int s1 = find(u);
    int s2 = find(v);

    if (s1 != s2)
    {
        if (rank[s1-1] < rank[s2-1]) {
            parent[s1-1] = s2;
            rank[s2-1] += rank[s1-1];
        }
        else
        {
            parent[s2-1] = s1;
            rank[s1-1] += rank[s2-1];
        }
    }
}