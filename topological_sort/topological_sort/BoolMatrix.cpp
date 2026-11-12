#include "BoolMatrix.h"
int BoolMatrix::Max (char** s, int m)
{
    if (s == nullptr || m <= 0)  return -1;
    int i, max;
    max = strlen(s[0]);
    for (i = 1; i < m; i++)
        if (max < strlen(s[i])) max = strlen(s[i]);
    return max;
}
BoolMatrix::BoolMatrix (int M, int N)
{
    if (M <= 0 || N <= 0)
    {
        cout<<"error! incorrect size. we replace it with default size"<<endl;
        M = 1;
        N = 1;
    }
    m = M;
    n = N;
    BM = new BoolVector[m];
    for (int i = 0; i < m; i++)
        BM[i] = BoolVector(n); //в явном виде вызываем конструктор
}
BoolMatrix::BoolMatrix (char** s, int M)
{
    int max = Max(s, M);
    if (max == -1)
    {
        cout<<"error! incorrect data. we replace it with default data"<<endl;
        m = 1;
        n = 1;
        BM = new BoolVector;
    }
    else
    {
        m = M;
        n = max;
        BM = new BoolVector[m];
        for (int i = 0; i < m; i++)
            BM[i] = BoolVector(s[i], n);
    }
}
BoolMatrix::BoolMatrix (const BoolMatrix& X)
{
    m = X.m;
    n = X.n;
    BM = new BoolVector[m];
    for (int i = 0; i < m; i++)
        BM[i] = X.BM[i];
}
BoolMatrix::BoolMatrix (BoolMatrix&& X) noexcept
{
    m = X.m;
    n = X.n;
    BM = X.BM;
    X.BM = nullptr;
}
BoolMatrix& BoolMatrix::operator= (const BoolMatrix& X)
{
    delete []BM;
    n = X.n;
    m = X.m;
    BM = new BoolVector[m];
    for (int i = 0; i<m; i++)
        BM[i] = X.BM[i];
    return (*this);
}
BoolMatrix& BoolMatrix::operator= (BoolMatrix&& X) noexcept
{
    if (this != &X)
    {
        delete []BM;
        n = X.n;
        m = X.m;
        BM = X.BM;
        X.BM = nullptr;
    }
    return *this;
}
void BoolMatrix::Scan(int M, int N)
{
    if (M <= 0 || N <= 0)
    {
        cout<<"error! incorrect size. we replace it with default size"<<endl;
        M = 1;
        N = 1;
    }
    if (m != M)
    {
        delete []BM;
        BM = new BoolVector[M];
    }
    m = M;
    n = N;
    cout<<"enter "<<M<<" lines of matrix:"<<endl;
    while (cin.get() != '\n');
    char *s = new char[N+1];
    for (int i = 0; i < M; i++)
    {
        cin.getline(s, N+1);
        BM[i] = BoolVector(s); //вызван конструктор в явном виде
    }
    n = N;
    delete []s;
}
void BoolMatrix::Print()
{
    for (int i = 0; i < m; i++)
        cout<<BM[i]<<endl;
}
BoolVector& BoolMatrix::operator[] (int pos)
// первый вариант
{
    if (pos<0)
        {
            cout<<"incorrect line number (<0)"<<endl;
            return BM[0];
        }
    if (pos >= m)
        {
            cout<<"incorrect line number (>="<<m<<")"<<endl;
            return BM[m-1];
        }
    return BM[pos];
}
/* второй вариант
 {
    try
     {
         if (pos<0) throw 0;
         if (pos >= m) throw m-1;
     }
    catch (int i)
     {
        cout<<"incorrect line number, return line number"<<i<<endl;
        return BM[i];
     }
    return BM[pos];
 }
 */
bool BoolMatrix::operator== (const BoolMatrix &X)
{
    if (m != X.m || n != X.n) return false;
    for (int i = 0; i < m; i++)
        if (BM[i] != X.BM[i]) return false;
    return true;
}
bool BoolMatrix::operator!= (const BoolMatrix &X)
{
    if (m != X.m || n != X.n) return true;
    for (int i = 0; i < m; i++)
        if (BM[i] != X.BM[i]) return true;
    return false;
}
BoolMatrix& BoolMatrix::SetUp1 (int i, int j)
{
    if (i < 0 || i >= m)
    {
        cout<<"incorrect line number, matrix without changes"<<endl;
        return *this;
    }
    if (j < 0 || j >= n)
    {
        cout<<"incorrect column number, matrix without changes"<<endl;
        return *this;
    }
    BM[i].SetUp1(j);
    return *this;
}
BoolMatrix& BoolMatrix::SetUp0 (int i, int j)
{
    if (i < 0 || i >= m)
    {
        cout<<"incorrect line number, matrix without changes"<<endl;
        return *this;
    }
    if (j < 0 || j >= n)
    {
        cout<<"incorrect column number, matrix without changes"<<endl;
        return *this;
    }
    BM[i].SetUp0(j);
    return *this;
}
BoolMatrix& BoolMatrix::Invert (int i, int j)
{
    if (i < 0 || i >= m)
    {
        cout<<"incorrect line number, matrix without changes"<<endl;
        return *this;
    }
    if (j < 0 || j >= n)
    {
        cout<<"incorrect column number, matrix without changes"<<endl;
        return *this;
    }
    BM[i].Invert(j);
    return *this;
}

BoolMatrix& BoolMatrix::SetUp1 (int i, int pos, int kol)
{
    if (i < 0 || i >= m)
    {
        cout<<"incorrect line number, matrix without changes"<<endl;
        return *this;
    }
    if (pos < 0 || pos >= n)
    {
        cout<<"incorrect column number, matrix without changes"<<endl;
        return *this;
    }
    BM[i].SetUp1(kol, pos);
    return *this;
}
BoolMatrix& BoolMatrix::SetUp0 (int i, int pos, int kol)
{
    if (i < 0 || i >= m)
    {
        cout<<"incorrect line number, matrix without changes"<<endl;
        return *this;
    }
    if (pos < 0 || pos >= n)
    {
        cout<<"incorrect column number, matrix without changes"<<endl;
        return *this;
    }
    BM[i].SetUp0(kol, pos);
    return *this;
}
BoolMatrix& BoolMatrix::Invert (int i, int pos, int kol)
{
    if (i < 0 || i >= m)
    {
        cout<<"incorrect line number, matrix without changes"<<endl;
        return *this;
    }
    if (pos < 0 || pos >= n)
    {
        cout<<"incorrect column number, matrix without changes"<<endl;
        return *this;
    }
    BM[i].Invert(kol, pos);
    return *this;
}
BoolMatrix BoolMatrix::operator& (BoolMatrix X)
{
    if (X.m != m || X.n != n)
    {
        cout<<"incorrect dimension, return first operand without changes"<<endl;
        return *this;
    }
    BoolMatrix Res(m, n);
    for (int i = 0; i < m; i++)
        Res.BM[i] = BM[i] & X.BM[i];
    return Res;
}
BoolMatrix& BoolMatrix::operator&= (BoolMatrix X)
{
    (*this) = (*this) & X;
    return *this;
}
BoolMatrix BoolMatrix::operator| (BoolMatrix X)
{
    if (X.m != m || X.n != n)
    {
        cout<<"incorrect dimension, return first operand without changes"<<endl;
        return *this;
    }
    BoolMatrix Res(m, n);
    for (int i = 0; i < m; i++)
        Res.BM[i] = BM[i] | X.BM[i];
    return Res;
}
BoolMatrix& BoolMatrix::operator|= (BoolMatrix X)
{
    (*this) = (*this) | X;
    return *this;
}
BoolMatrix BoolMatrix::operator^ (BoolMatrix X)
{
    if (X.m != m || X.n != n)
    {
        cout<<"incorrect dimension, return first operand without changes"<<endl;
        return *this;
    }
    BoolMatrix Res(m, n);
    for (int i = 0; i < m; i++)
        Res.BM[i] = BM[i] ^ X.BM[i];
    return Res;
}
BoolMatrix& BoolMatrix::operator^= (BoolMatrix X)
{
    (*this) = (*this) & X;
    return *this;
}
BoolMatrix& BoolMatrix::operator ~()
{
    (*this) = !(*this);
    return (*this);
}
BoolMatrix BoolMatrix::operator! ()
{
    BoolMatrix Res = (*this);
    for (int i = 0; i < m; i++)
        Res.BM[i] = ~Res.BM[i];
    return Res;
}
BoolMatrix BoolMatrix::ShiftRight (int i, int kol)
{
    if (i < 0 || i >= m)
    {
        cout<<"incorrect line numder, return matrix copy without changes"<<endl;
        return *this;
    }
    BoolMatrix Res = *this;
    Res.BM[i] >>= kol; //проверка корректности kol в boolvector
    return Res;
}
BoolMatrix& BoolMatrix::ShiftRightEq (int i, int kol)
{
    if (i < 0 || i >= m)
        cout<<"incorrect line numder, return matrix without changes"<<endl;
    else BM[i] >>= kol;
    return *this;
}
BoolMatrix BoolMatrix::ShiftLeft (int i, int kol)
{
    BoolMatrix Res = (*this);
    Res.ShiftLeftEq(i, kol);
    return Res;
}
BoolMatrix& BoolMatrix::ShiftLeftEq (int i, int kol)
{
    if (i < 0 || i >= m)
        cout<<"incorrect line numder, return matrix without changes"<<endl;
    else BM[i] <<= kol;
    return *this;
}

BoolVector BoolMatrix::Conj()
{
    BoolVector Res = BM[0];
    for (int i = 1; i < m; i++)
        Res &= BM[i];
    return Res;
}
BoolVector BoolMatrix::Disj()
{
    BoolVector Res = BM[0];
    for (int i = 1; i < m; i++)
        Res |= BM[i];
    return Res;
}
BoolVector BoolMatrix::Xor()
{
    BoolVector Res = BM[0];
    for (int i = 1; i < m; i++)
        Res ^= BM[i];
    return Res;
}
istream& operator>> (istream& is, BoolMatrix& X)
{
    int M, N;
    cout<<"enter the number of line and column: ";
    cin>>M>>N;
    if (X.m != M)
    {
        delete []X.BM;
        X.m = M;
        X.BM = new BoolVector[M];
    }
    cout<<"enter "<<M<<" lines of matrix:"<<endl;
    while (cin.get() != '\n');
    char *s = new char[N+1];
    for (int i = 0; i < M; i++)
    {
        cin.getline(s, N+1);
        X.BM[i] = BoolVector(s); //вызван конструктор в явном виде
    }
    X.n = N;
    delete []s;
    return is;
}
ostream& operator<< (ostream& os, BoolMatrix& X)
{
    for (int i = 0; i < X.m; i++)
        os << X.BM[i] << endl;
    return os;
}
