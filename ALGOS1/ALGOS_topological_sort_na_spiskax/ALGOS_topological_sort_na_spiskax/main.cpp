#include <iostream>
#include "Graph.h"
using namespace std;
void PrintMas(int *a, int n)
{
    for (int i = 0; i < n; i++)
        cout<<a[i]<<" ";
}

int main()
{
    int n;
    int *res;
    
    Graph LD, newLD;
    n = LD.FormGraph();
    
    LD.SortGraph(newLD);
    
    res = new int[n];
    newLD.Res(res);
    
    PrintMas(res, n);
}
/*
 enter x and y: 1 4
 enter x and y: 1 6
 enter x and y: 2 1
 enter x and y: 2 3
 enter x and y: 2 7
 enter x and y: 3 4
 enter x and y: 5 3
 enter x and y: 6 5
 enter x and y: 7 8
 enter x and y: 8 5
 enter x and y: 9 4
 enter x and y: 9 5
 enter x and y: 9 6
 enter x and y: 0 0
 */
