#pragma once

class DisjointSets {
    int* parent;
    int* rank;

public:

    DisjointSets(int n);

    void MakeSet(int v);

    int find(int v);

    void Union(int u, int v);
};
