#include "BoolVector.h"
//#include <iostream>
//using namespace std;
typedef unsigned char UC;
//найти 2 некорректных метода и исправить ошибку

int BoolVector::Input(char* s, int i_s, int i_bv, int k) //проверка строки s на пустоту - в конструкторе
{
    bv[i_bv] = 0; //установили все биты в 0
    UC mask = 1;
    mask <<= (k - 1);
    for (int i = 0; i < k; i++, i_s++, mask>>=1)
        if (s[i_s] == '1')
            bv[i_bv] |= mask;
    return i_s;
        
}
void BoolVector::Output(int i_bv, int k)
{
    UC mask = 1;
    mask<<=(k-1);
    for (int i = 0; i < k; i++, mask>>=1)
        if ((bv[i_bv] & mask) != 0)
            cout<<'1';
        else cout<<'0';
}
BoolVector::BoolVector(int N)
{
    if (N<=0)
    {
        cout<<"error! incorrect value. replace value by n = 1"<<endl;
        N = 1;
    }
    n = N;
    m = N/8;
    int k = N%8;
    if (k != 0) m++;
    
    bv = new UC[m];
    for (int i = 0; i < m; i++)
        bv[i] = 0;
}
BoolVector::BoolVector(char* s)
{
    if (s == nullptr)
    {
        cout<<"error! incorrect value. we set bool vector by 0"<<endl;
        n = 1;
        m = 1;
        bv = new UC[1];
        bv[0] = 0;
    }
    else
    {
        n = strlen(s);
        m = n/8;
        int k = n%8;
        if (k != 0) m++;
        bv = new UC[m];
        
        int i_s = 0, i_bv = 0;
        if (k != 0)
        {
            i_s = Input(s, i_s, i_bv, k);
            i_bv++;
        }
        while (i_bv < m)
        {
            i_s = Input(s, i_s, i_bv, 8);
            i_bv++;
        }
    }
}
BoolVector::BoolVector(char* s, int N)
{
    if (N<=0)
    {
        cout<<"error! incorrect size of bv. we set size = 1"<<endl;
        N = 1;
    }
    int s_len = strlen(s);
    n = N;
    m = n/8;
    int k = n%8;
    if (k != 0) m++;
    bv = new UC [m];
    
    char* temp = new char[N+1];
    int i, j;
    if (N > s_len)
    {
        temp[N] = '/0';
        for (i = N-1, j = s_len - 1; j >= 0; i--, j--)
            temp[i] = s[j];
    }
    else if (s_len > n)
    {
        temp[N] = '/0';
        for (i = N-1, j = s_len - 1; i >= 0; i--, j--)
            temp[i] = s[j];
    }
    else
    {
        strcpy(temp, s);
    }
    int i_s = 0, i_bv = 0;
    if (k != 0)
    {
        i_s = Input(temp, i_s, i_bv, k);
        i_bv++;
    }
    while (i_bv < m)
    {
        i_s = Input(temp, i_s, i_bv, 8);
        i_bv++;
    }
}
BoolVector::BoolVector(const BoolVector &X)
{
    n = X.n;
    m = X.m;
    bv = new UC[m];
    for (int i = 0; i < m; i++)
        bv[i] = X.bv[i];
}
BoolVector& BoolVector::operator= (const BoolVector& X)
{
    n = X.n;
    m = X.m;
    delete []bv;
    bv = new UC[m];
    for (int i = 0; i < m; i++)
        bv[i] = X.bv[i];
    return (*this);
}
BoolVector::BoolVector(BoolVector&& X) noexcept
{
    n = X.n;
    m = X.m;
    bv = X.bv;
    X.bv = nullptr;//отобрали ресурсы у X и сделали нулевой массив, чтобы компилятор не ругался
}
BoolVector& BoolVector::operator= (BoolVector&& X) noexcept
{
    if ((*this) != X)
    {
        m = X.m;
        n = X.n;
        bv = X.bv;
        X.bv = nullptr;
    }
    return (*this);
}
int BoolVector::Weight()
{
    UC mask = 1;
    int w = 0;
    for (int i = 0; i < m; i++, mask = 1)
    {
        mask<<=7;
        while (mask != 0)
        {
            if ((bv[i] & mask) != 0)
                w++;
            mask>>=1;
        }
    }
    return w;
}
/* Другой вариант кода
 {
    UC mask = 1;
     int w = 0;
     for (int i = 0; i < m; i++, mask = 1)
        for (mask<<=7; mask!=0; mask>>=1)
             if ((bv[i] % mask) != 0)
                 w++;
     return w;
 }
 Третий вариант кода:
 {
    int w = 0;
    for (int i = 0; i < n; i++)
        if (this->operator[](i) == '1')     // if ((*this)[i]) w++;
            w++;
    return w;
 }
 */
UC BoolVector::operator[] (int pos)
{
    int M = pos/8; // m-1-M - номер элемента в массиве bv
    int k = pos%8;
    UC mask = 1;
    mask <<= k;
    if ((bv[m-1-M] & mask) != 0)
        return '1';
    return '0';
}
bool BoolVector::operator== (BoolVector& X)
{
    if (n != X.n) return false;
    for (int i = 0; i < m; i++)
        if (bv[i] != X.bv[i]) return false;
    return true;
}
bool BoolVector::operator!= (BoolVector& X)
{
    if (n != X.n) return true;
    for (int i = 0; i < m; i++)
        if (bv[i] != X.bv[i]) return true;
    return false;
}
bool BoolVector::operator< (BoolVector& X)
{
    if (n != X.n) return false;
    bool f = false;
    for (int i = 0; i < n; i++)
    {
        int a = (*this)[i] - '0';
        int b = X[i] - '0';
        if (a > b) return false;
        if (a < b) f = true;
    }
    return f;
}
bool BoolVector::operator> (BoolVector& X)
{
    if (n != X.n) return false;
    bool f = false;
    for (int i = 0; i < n; i++)
    {
        int a = (*this)[i] - '0';
        int b = X[i] - '0';
        if (a < b) return false;
        if (a > b) f = true;
    }
    return f;
}
BoolVector BoolVector::operator& (BoolVector X)
{
    int N = n, i_res = m - 1;
    if (N > X.n)
    {
        N = X.n;
        i_res = X.m - 1;
    }
    BoolVector Res(N);
    int i, i_X;
    for (i = m - 1, i_X = X.m - 1; i_res >= 0; i--, i_X--, i_res--)
        Res.bv[i_res] = (bv[i] & X.bv[i_X]);
    return Res;
}
BoolVector& BoolVector::operator&= (BoolVector X)
{
    BoolVector Res = ((*this) & X);
    *this = Res;
    return *this;
}
BoolVector BoolVector::operator| (BoolVector X)
{
    int k;
    if (n > X.n) k = n;
    else k = X.n;
    BoolVector Res(k);
    int d = Res.m - m;
    int d_X = Res.m - X.m;
    for (int i = 0; i < Res.m; i++)
    {
        UC a = 0, b = 0;
        if (i - d >= 0) a = bv[i - d];
        if (i - d_X >= 0) b = X.bv[i - d_X];
        Res.bv[i] = a | b;
    }
    return Res;
}
BoolVector& BoolVector::operator|= (BoolVector X)
{
    (*this) = (*this)|X;
    return (*this);
}
BoolVector BoolVector::operator^ (BoolVector X)
{
    int k;
    if (n > X.n) k = n;
    else k = X.n;
    BoolVector Res(k);
    int i, j, t;
    for (i = m-1, j = X.m -1, t = Res.m - 1; i >= 0 && j>=0; i--, j--, t--)
    {
        Res.bv[t] = bv[i] ^ X.bv[j];
    }
    while (i >= 0)
    {
        Res.bv[t] = bv[i];
        t--;
        i--;
    }
    while (j >= 0)
    {
        Res.bv[t] = X.bv[j];
        t--;
        j--;
    }
    return Res;
}
BoolVector& BoolVector::operator^= (BoolVector X)
{
    (*this) = (*this)^X;
    return (*this);
}
BoolVector BoolVector::operator~ ()
{
    BoolVector Res(n);
    for (int i = 0; i < m; i++)
        Res.bv[i] = ~bv[i];
    int t = n % 8;
    if (t != 0)
    {
        UC mask = 0;
        for (int i = 0; i < t; i++)
        {
            mask <<= 1;
            mask |= 1;
        }
        Res.bv[0] &= mask;
    }
    return Res;
}
BoolVector BoolVector::operator! ()
{
    (*this) = ~(*this);
    return (*this);
}
BoolVector BoolVector::operator<< (int k)
{
    if (k<0)
    {
        cout<<"incorrect data"<<endl;
        return *this;
    }
    BoolVector Res(*this);
    for (int s = 0; s < k; s++)
    {
        UC c = 0, new_c, mask = (1<<7);
        for (int i = m-1; i >= 0; i--)
        {
            if (Res.bv[i] & mask) new_c = 1;
            else new_c = 0;
            Res.bv[i] <<= 1;
            Res.bv[i] |= c;
            c = new_c;
        }
    }
    return Res;
}
BoolVector& BoolVector::operator<<= (int k)
{
    *this = (*this << k);
    return *this;
}
BoolVector BoolVector::operator>> (int k)
{
    if (k<0)
    {
        cout<<"incorrect data"<<endl;
        return *this;
    }
    BoolVector Res(n);
    if (k>=n)
    {
        return Res;
    }
    for (int i = n-1; i>=k; i--)
//        if ((*this)[i] == '1') Res.SetUp1(i-k);
        if (this->operator[](i) == '1')
        {
            Res.SetUp1(i-k);
        }
    return Res;
}
BoolVector& BoolVector::operator>>= (int k)
{
    BoolVector T = ((*this) >> k);
    (*this) = T;
    return *this;
}
BoolVector& BoolVector::SetUp1(int pos)
{
    int M = pos/8;
    int k = pos%8;
    UC mask = 1;
    mask <<= k;
    bv[m-1-M] |= mask;
    return *this;
}
BoolVector& BoolVector::SetUp0(int pos)
{
    int M = pos/8;
    int k = pos%8;
    UC mask = 1;
    mask <<= k;
    bv[m-1-M] &= (~mask);
    return *this;
}
BoolVector& BoolVector::Invert(int pos)
{
    int M = pos/8; // m-1-M - номер элемента в массиве bv
    int k = pos%8;
    UC mask = 1;
    mask <<= k;
    bv[m-1-M] ^= mask;
    return *this;
}
BoolVector& BoolVector::SetUp1(int k, int pos)
{
    for (int i = 0; i < k; i++)
        (*this).SetUp1(pos+i);
    return *this;
}
BoolVector& BoolVector::SetUp0(int k, int pos)
{
    for (int i = 0; i < k; i++)
        (*this).SetUp0(pos+i);
    return *this;
}
BoolVector& BoolVector::Invert(int k, int pos)
{
    for (int i = 0; i < k; i++)
        (*this).Invert(pos+i);
    return *this;
}
ostream& operator<< (ostream& r, BoolVector& X)
{
    int c = X.m*8 - X.n;
    X.Output(0, 8 - c);
    for (int i = 1; i < X.m; i++)
        X.Output(i, 8);
    return r;
}
istream& operator>> (istream& r, BoolVector& X)
{
    cout<<"enter the length of boolean vector: ";
    int N;
    cin>>N;
    char* s = new char[N+1];
    //gets_s(s, N+1); //освобождаем буфер данных (в нем хранится enter)
    while (cin.get()!='\n'); //второй варинат осбождения буфера
    cout<<"enter the boolean vector of length "<<N<<": ";
    fgets(s, N+1, stdin);
    BoolVector Temp(s);
    X = Temp;
    delete []s;
    return r;
}
