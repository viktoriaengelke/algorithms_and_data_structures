#pragma once
using namespace std;

//метод внутренних цепочек
class Usel
{
    int key, next;
public:
    Usel(int k = -1, int n = -1): key(k), next(n) {};
    void Print()
    {
        cout<<key<<"<-->"<<next<<endl;
    }
    friend class Hash;
};
class Hash
{
    int dim; //размер хэш-таблицы
    int p; //хэш-функция h(x) = x % p
    Usel *TAB;
public:
    Hash();
    Hash(int *a, int n, int P); //dim = n * 1,2
    Hash(const Hash&);
    Hash(Hash&&) noexcept;
    Hash& operator= (const Hash&);
    Hash& operator= (Hash&&) noexcept;
    ~Hash();
    
    void Add(int k);
    int FindKey(int k);
    void Del(int pos);
    void Print();
};

