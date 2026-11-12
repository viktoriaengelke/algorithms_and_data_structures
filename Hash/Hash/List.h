#pragma once
using namespace std;

// 1 Метод внешних цепочек

class Node
{
    int key;
    Node *next;
public:
    Node(int k = -1, Node *N = NULL): key(k), next(N) {};
    friend class List;
};

class List
{
    Node *head;
public:
    List(): head(NULL) {};
    List(int *a, int n); //построение списка из массива
    List(int n); //случайный массив
    
    List(const List&);
    List(List&&) noexcept;
    List& operator= (const List&);
    List& operator= (List&&) noexcept;
    ~List();
    
    void AddAfter(Node *p, int k);
    void AddToTail(int k);
    void AddToHead(int k);
    
    void DelAfter(Node *p);
    void DelHead();
    void DelTail();
    
    Node* FindKey(int k); //возвращает указатель на узел который предшествует k (или -1), а если голова, то возвр указатель на голову (для удаления нужно проверить ключ в следующем и в самом узле)
    bool Empty();
    Node* FindPos(int pos); // поиск по позиции
    void Clear(); // для перегрузки =
    void PrintList();
};
