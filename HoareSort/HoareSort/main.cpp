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

struct elem{int L, R;};

void Hoar3(int* A, int n)
{
    elem *S = new elem[n];
    int k = 0, l, r, i, j, x; //k - вешина стека
    S[0].L = 0;
    S[0].R = n-1;
    while (k >= 0)
    {
        l = S[k].L;
        r = S[k].R;
        k--;
        if (l < r)
        {
            i = l;
            j = r;
            x = A[(l+r)/2];
            while (i <= j)
            {
                while (A[i] < x) i++;
                while (A[j] > x) j--;
                if (i <= j)
                {
                    Swap(&A[i], &A[j]);
                    i++;
                    j--;
                }
            }
            k++;
            S[k].L = i;
            S[k].R = r;
            k++;
            S[k].L = l;
            S[k].R = j;
        }
    }
    delete[] S;
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
    Hoar3(A, n);
    int p = IsSorted(A, n);
    cout<<p<<endl;
    PrintMas(A, n);
}
