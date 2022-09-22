#pragma once
#include <vector>
using namespace std;
#include "Edge.h"

void quickSort(vector<Edge>& list, int start, int end);
void swap(Edge* edge1, Edge* edge2);
int partition(vector<Edge>& list, int low, int high);
