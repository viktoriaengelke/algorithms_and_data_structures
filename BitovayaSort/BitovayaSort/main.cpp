#include <iostream>
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
int IsSorted(int *a, int n)
{
    int c = 1;
    for (int i = 1; i < n; i++)
        if (a[i-1] <= a[i]) c++;
        else return -1;
    return c;
}
void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int HighBit(int *a, int n)
{
    int MaxPos = -1;
    for (int i = 0; i < n; i++)
    {
        int x = a[i];
        for (int j = 10; j >= 0; j--)
        {
            if (x & (1 << j))
            {
                if (j > MaxPos) MaxPos = j;
                break;
            }
        }
    }
    return MaxPos;
}
void BitSort(int* a, int l, int r, int k)
{
    if (l >= r || k < 0) return;
    int i = l;
    int j = r;
    int mask = 1<<k;
    while (i <= j)
    {
        while ((i<=j) && ((a[i] & mask) == 0)) i++;
        while ((i<=j) && ((a[j] & mask) != 0)) j--;
        if (i<j)
        {
            Swap(&a[i], &a[j]);
            i++;
            j--;
        }
    }
    BitSort(a, l, j, k-1);
    BitSort(a, i, r, k-1);
}

int main()
{
    int n;
    cout<<"enter the length of array: ";
    cin>>n;
    int *A = new int[n];
    FormMas(A, n);
    PrintMas(A, n);
    cout<<endl;
    int k = HighBit(A, n);
    BitSort(A, 0, n-1, k);
    int p = IsSorted(A, n);
    cout<<p<<endl;
    PrintMas(A, n);
}

