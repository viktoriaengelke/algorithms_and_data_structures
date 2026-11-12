#include <iostream>
#include "BoolMatrix.h"
using namespace std;

void PrintMas(int *a, int n)
{
    for (int i = 0; i < n; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
int Count(int *Res, int n)
{
    for (int i = 0; i<n; i++)
        if (Res[i] == 0) return i;
    return n;
}
int main()
{
    int n;
    cout<<"enter the number of graph vertices: ";
    cin>>n;
    cout<<endl;
    BoolMatrix M(n, n);
    cout<<"enter the bool matrix: "<<endl;
    cin>>M;
    BoolVector v0(n);
    BoolVector v1(n);
    BoolVector w(n);
    BoolVector d(n);
    
    BoolVector k0(n);

    int Res[n];
    for (int i = 0; i < n; i++)
        Res[i] = 0;
    int l = 0;
    
    while (Count(Res, n) != n)
    {
        d = M.Disj();
        w = !d;
        v1 = w ^ v0;
        for (int i = n-1; i >= 0; i--)
            if (v1[i] == '1')
            {
                Res[l] = n - i;
                l++;
                M.SetUp0(n - i - 1, 0, n);
            }
        v0 = w;
    }
    PrintMas(Res, n);
}

/*
000101000
101000100
000100000
000000000
001000000
000010000
000000010
000010000
000111000
 
res={2,9,1,7,6,8,5,3,4}
*/

