#include "QuickSort.h"

int partition(vector<Edge>& list, int low, int high)
{
    int pivot = list[high].getWeight();
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++)
    {
        if (list[j].getWeight() < pivot)
        {
            i++; 
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i + 1], &list[high]);
    return (i + 1);
}

void quickSort(vector<Edge>& list, int start, int end)
{
    if (start >= end)
        return;

    int p = partition(list, start, end);
    quickSort(list, start, p - 1);
    quickSort(list, p + 1, end);
}

void swap(Edge* edge1, Edge* edge2)
{
    Edge temp = *edge1;
    //temp = *edge1;
    *edge1 = *edge2;
    *edge2 = temp;
}