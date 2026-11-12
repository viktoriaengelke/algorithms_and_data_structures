#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int FormMatr(int** s, int n)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i != j)
                s[i][j] = 1 + rand() % 100;
            else
                s[i][j] = 0;
        }
    return 0;
}
int NewPerest(int* p, int n)
{
    int i_max = -1;
    int j_max = -1;
    for (int i = n - 2; i >= 1; i--)
    {
        if (p[i] < p[i + 1])
        {
            i_max = i;
            break;
        }
    }
    if (i_max == -1) return 0;

    for (int j = n - 1; j > i_max; j--)
    {
        if (p[i_max] < p[j])
        {
            j_max = j;
            break;
        }
    }
    int c = p[i_max];
    p[i_max] = p[j_max];
    p[j_max] = c;
    for (int i = i_max + 1, j = n - 1; i < j; i++, j--)
    {
        int c = p[i];
        p[i] = p[j];
        p[j] = c;
    }
    return 1;
}
void PrintMatr(int** s, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << s[i][j] << " ";
        }
        cout << "\n";
    }
}
int main()
{
    int n, g;
    cout << "vvedi kol-vo gorodov ";
    cin >> n;
    cout << "vvedi nachalniy gorod ";
    cin >> g;
    
    int** s = new int*[n];
    for (int i = 0; i < n; i++)
        s[i] = new int[n];
    
    FormMatr(s, n);
    PrintMatr(s, n);
    
    int* p = new int[n];
    p[0]=g-1;
    for (int i = 1; i < n; i++)
        if (i>=g)
            p[i] = i;

        else
            p[i]=i-1;
    
    int sum_min = 0;
    for (int i = 0; i < n - 1; i++)
        sum_min += s[p[i]][p[i + 1]];
    sum_min += s[p[n - 1]][p[0]];
    
    for (int i = 0; i < n; i++)
        cout << p[i]+1 << " ";
    cout << p[0] + 1 << " ";
    
    int* p_min = new int[n];
    for(int k = 0; k < n; k++)
        p_min[k] = p[k];
    
    cout << sum_min << endl;
    
        while (NewPerest(p, n))
        {
            int sum = 0;
            for (int i = 0; i < n; i++)
                cout << p[i]+1 << " ";
            cout << p[0] + 1 << " ";
            for (int i = 0; i < n - 1; i++)
                sum += s[p[i]][p[i + 1]];
            sum += s[p[n - 1]][p[0]];
            if (sum < sum_min)
            {
                sum_min = sum;
                for(int k = 0; k < n; k++)
                    p_min[k] = p[k];
            }
            cout << sum << endl;
        }
    
        cout << "minimum: " << endl;
        for (int i = 0; i < n; i++)
            cout << p_min[i] + 1 << " ";
        cout << p_min[0] + 1 << " ";
        cout << sum_min << endl;
    
        for (int i = 0; i < n; i++)
            delete[] s[i];
        delete[] s;
    
    }
