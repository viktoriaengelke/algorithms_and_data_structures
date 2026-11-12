#include "Graph.h"
void Lider::ReduceCount()
{
    Trailer* t = tr;
    while (t != nullptr)
    {
        t->Pointer->count--;
        t = t->next;
    }
}
void Lider::IncreaseCount()
{
    Trailer* t = tr;
    while (t != nullptr)
    {
        t->Pointer->count++;
        t = t->next;
    }
}
void Lider::DelTrailer()
{
    Trailer* t = tr;
    while (t != nullptr)
    {
        Trailer* p = t -> next;
        delete t;
        t = p;
    }
    tr = nullptr;
}
void Lider::AddTrailer(Lider* p)
{
    Trailer *q = new Trailer(p, tr); 
    tr = q;
}

Graph::Graph(int K, int C, Lider* N, Trailer* T)
{
    head = new Lider(K, C, N, T);
}
Graph::~Graph()
{
    Clear();
    delete head;
}
void Graph::AddToHead(int x)
{
    Lider* p = new Lider(x, 0, head->next, nullptr);
    head->next = p;
}
void Graph::AddToTail(Lider* p)
{
    Lider* t = head;
    while (t->next != nullptr)
        t = t->next;
    t->next = p;
    p->next = nullptr;
}
void Graph::Del(Lider* p)
{
    if (p == nullptr) return;

    Lider* prev = head;
    while (prev->next != nullptr && prev->next != p)
        prev = prev->next;

    if (prev->next == p)
    {
        prev->next = p->next;
        p->DelTrailer();
        delete p;
    }
}
void Graph::Exclude(Lider* p)
{
    if (p == nullptr) return;

    Lider* prev = head;
    while (prev->next != nullptr && prev->next != p)
        prev = prev->next;

    if (prev->next == p)
    {
        prev->next = p->next;
        p->next = nullptr;  
    }
}
Lider* Graph::FindKey(int x)
{
    Lider* p = head->next;
    while (p != nullptr)
    {
        if (p->key == x)
            return p;
        p = p->next;
    }
    return nullptr;
}
Lider* Graph::FindCount(int c)
{
    Lider* p = head->next;
    while (p != nullptr)
    {
        if (p->count == c)
            return p;
        p = p->next;
    }
    return nullptr;
}
int Graph::FormGraph()
{
    int n = 0, x, y;
    Lider *px, *py;
    cout<<"enter x and y: ";
    cin>>x>>y;
    while (x&&y)
    {
        if (FindKey(x) == nullptr)
        {
            AddToHead(x);
            px = head->next;
            n++;
        }
        else px = FindKey(x);
        if (FindKey(y) == nullptr)
        {
            AddToHead(y);
            py = head->next;
            n++;
        }
        else py = FindKey(y);
             
        py->count++;
        px->AddTrailer(py);
        
        cout<<"enter x and y: ";
        cin>>x>>y;
    }
    return n;
}
void Graph::SortGraph(Graph& newLD)
{
    Lider *p;
    while(NotEmpty())
    {
        p = FindCount(0);
        Exclude(p);
        newLD.AddToTail(p);
        p->ReduceCount();
    }
    p = newLD.head->next;
    while (p != nullptr)
    {
        p->IncreaseCount();
        p = p->next;
    }
}
bool Graph::NotEmpty()
{
    if (head->next == nullptr) return false;
    return true;
}
void Graph::Clear()
{
    Lider* p = head->next;
    while (p != nullptr)
    {
        Lider* q = p->next;
        p->DelTrailer();
        delete p;
        p = q;
    }
    head->next = nullptr;
}
void Graph::Res(int* a)
{
    Lider *t = head->next;
    int i = 0;
    while (t != nullptr)
    {
        a[i] = t->key;
        i++;
        t = t->next;
    }
}
