#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
void FormMas(int *a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand() % 200;
}
void PrintMas(int *a, int n)
{
    for (int i = 0; i < n; i++)
        cout<<a[i]<<" ";
}
int FormSteps(int *h, int l, int n)
{
    int c = 0, step;
    for (int i = 0; i < l; i++)
    {
        if (i % 2 == 0)
            step = 9*pow(2, i) - 9*pow(2, (i/2)) + 1;
        else
            step = 8*pow(2, i) - 6*pow(2,((i+1)/2)) + 1;
        if (step > n)  break;
        h[c] = step;
        c++;
    }
    return c;
}
void SortShella (int* a, int n)
{
    int l = 10, c;
    int *h = new int [l];
    c = FormSteps(h, l, n);
    for (int i = c-1; i>=0; i--)
    {
        int s = h[i], b;
        for (b = 0; b < s; b++)
            for (int j = b+s; j < n; j+=s)
            {
                int x = a[j];
                int k;
                for (k = j - s; k >= 0 && a[k] > x; k -= s)
                    a[k+s] = a[k];
                a[k+s] = x;
            }
    }
    delete[] h;
}
int main()
{
    srand(time(NULL));
    int* a = new int [200];
    int n;
    cout<<"enter the length of array: ";
    cin>>n;
    FormMas(a, n);
    cout<<"a = ";
    PrintMas(a, n);
    cout<<endl;
    SortShella(a, n);
    cout<<"a(sorted) = ";
    PrintMas(a, n);
    delete[] a;
}
