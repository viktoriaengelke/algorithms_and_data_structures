#include <iostream>
using namespace std;
struct Trailer;

struct Lider
{
    int key, count;
    Lider* next;
    Trailer* tr;
    
    Lider(int K = 0, int C = 0, Lider* N = nullptr, Trailer* T = nullptr): key(K), count(C), next(N), tr(T) {};
    
    void DelTrailer(); //удаляем список всех трейлеров для деструктора
    void AddTrailer(Lider*); //добавление узла в список трейлеров
    
    void ReduceCount(); //уменьшение count
    void IncreaseCount(); //увеличение count
};

struct Trailer
{
    Lider* Pointer; //указатель на вершину
    Trailer* next;
    
    Trailer(Lider* P = nullptr, Trailer* N = nullptr): Pointer(P), next(N) {};
};

class Graph //однонаправленный список с фиктивной головой
{
    Lider* head;
    
public: //по идее еще нужен конструктор копирования и операция присвоения, но для задачи это не нужно => не пишем
    Graph(int K = 0, int C = 0, Lider* N = nullptr, Trailer* T = nullptr);
    ~Graph();
    
    void AddToHead(int x); //формируем узел
    void AddToTail(Lider*); //добавляем готовый узел
    
    void Del(Lider*); //удаление узла для деструктора (сначала DelTrailer, а потом сам узел удаляем)
    void Exclude(Lider*); //исключение узла из списка без его удаления (для формирования нового списка)
    
    Lider* FindKey(int); //запускаем перед формированием узла
    Lider* FindCount(int); //поиск узлов с полем каунт 0
    
    int FormGraph(); //формирование первоначального списка, возвращает количество узлов в графе
    
    void SortGraph(Graph&); //граф по ссылке будет отсортирован как нужно, по ссылке отправляем => не нужен конструктор копирования
    
    void Clear(); //для деструктора, удаляет всве кроме фиктивной головы
    
    bool NotEmpty();
    
    void Res(int* a);
};
