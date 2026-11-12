#include <iostream>
using namespace std;

void FormMas(int *a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand()%200;
}
void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void PrintMas(int *a, int n)
{
    for (int i = 0; i < n; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
int IsSorted(int *a, int n)
{
    int c = 1;
    for (int i = 1; i < n; i++)
        if (a[i-1] <= a[i]) c++;
        else return -1;
    return c;
}
void Sift2(int *a, int n, int i)
{
    int j = 2*i + 1;
    int x = a[i], f = 1;
    while ((j<n) && f)
    {
        if ((j+1<n) && (a[j+1] > a[j]))
            j = j+1;
        if (a[j] > x)
        {
            a[i] = a[j];
            i = j;
            j = 2*i + 1;
        }
        else f = 0;
    }
    a[i] = x;
}
void SortHeap(int *a, int n)
{
    for (int i = n/2-1; i >= 0; i--)
        Sift2(a, n, i);
    for (int i = n-1; i>0; i--)
    {
        Swap(&a[0], &a[i]);
        Sift2(a, i, 0);
    }
}
int main()
{
    srand(time(0));
    int n;
    cout<<"введите количество элементов массива: ";
    cin>>n;
    int *a = new int[n];
    FormMas(a, n);
    PrintMas(a, n);
    SortHeap(a, n);
    PrintMas(a, n);
    int k = IsSorted(a, n);
    cout<<k;
}
