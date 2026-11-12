#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char s[80], p[40];
    int TAB[256], m, n;
    
    cout<<"vvedi s: ";
    fgets(s, 80, stdin);
    cout<<"vvedi p: ";
    fgets(p, 40, stdin);
    
    if (s[strlen(s)-1] == '\n') s[strlen(s)-1] = '\0';
    if (p[strlen(p)-1] == '\n') p[strlen(p)-1] = '\0';
    
    n = strlen(s);
    m = strlen(p);
    if (m == 0)
    {
        cout<<"pattern is empty"<<endl;
        return 0;
    }
    for (int i = 0; i < 256; i++)
        TAB[i] = m; // инициализировали длиной образа
    
    for (int i = 0; i < m - 1; i++)
        TAB[p[i]] = m - 1 - i; // заменили значениями смещения
    
    int i = m - 1, j = m - 1;
    while (i < n)
    {
        int k = i;
        j = m - 1;
        while (j >= 0 && s[k] == p[j])
        {
            k -= 1;
            j -= 1;
        }
        if (j < 0)
        {
            k += 1;
            cout<<"index nachala: "<< k <<endl;
            return 0;
        }

        i += TAB[s[i]];
    }
    
    cout<<"net vhojdenia"<<endl;
}

