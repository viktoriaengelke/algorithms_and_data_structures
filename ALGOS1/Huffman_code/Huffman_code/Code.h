#pragma once
#include <iostream>
using namespace std;

class Node
{
    char* str;
    int freq; //частота
    Node* next;
    Node *left, *right;

public:
    Node()
    {
        str = new char[1];
        str[0]='\0';
        freq = 0;
        next = left = right = NULL;
    }
    Node(char s[], int Fr, Node* N, Node *L, Node *R): freq(Fr), next(N), left(L), right(R)
    {
        str = new char[strlen(s)+1];
        strcpy(str, s);
    };
    ~Node() {delete [] str;}
    friend class Code;
};

class Code
{
    Node *head;
    int type; //класс хранит либо список, либо дерево, деструктор работает по разному => понимаем какой деструктор вызывать. если type = 0 - список, если type = 1 - дерево
    void Copy(Node *q, Node *p, int k); //копирование дерева с корнем q, p - предок корня нового дерева, k = 0 - копируем как левого потомка, k = 1 - копируем как правого потомка //нужно убрать поле родитель
    bool Find(char ch, char p[]); //поиск буквы в строке: узнаем куда идти направо или налево
public:
    Code() {head = NULL; type = NULL;}
    Code(char s[]);
    ~Code();
    Code(const Code&);
    Code(Code&&) noexcept;
    Code& operator= (const Code&);
    Code& operator= (Code&&) noexcept;
    
    void AddToTail(char s[], int f); //передаем букву и частоту
    void AddToTail(Node* p);
    
    void AddToHead(char s[], int f); //передаем букву и частоту
    void AddToHead(Node * p);
    
    void AddAfter(Node* pos, char s[], int f); //передаем букву и частоту
    void AddAfter(Node* pos, Node * p);
  
    void DelHead();
    void Clear(Node* p);
    //void Clear(Node* pr, Node* t) //pr - родитель, t - удаляемый узел (возможно можно без нее обойтись)
    
    bool Empty(); //проверка на пустоту
    void PrintList(); //вывод на консоль списка (вместе с частотами)
    void PrintTree(int k, Node* p); //как в бинтри
    Node* GetHead() {return head;} //для печати дерева
    
    void FormTree(); //преобразование списка в дерево
    void CodeText(char s[], char code[]); //кодирование текста 
    void DecodeText(char code[], char s[]); //декодирование текста
    
};

