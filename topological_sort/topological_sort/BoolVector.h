#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h> //для размера строки
using namespace std;
typedef unsigned char UC;

class BoolVector
{
    UC *bv;
    int n, m; //n - длина булева вектора, m - размер массива bv
    int Input(char* s, int i_s, int i_bv, int k); //k - количество значащих бит в bv[i_bv],возвращаем индекс где остановились
    void Output(int i_bv, int k); //k - количество значащих бит в bv[i_bv]
public:
    BoolVector(int N = 1); //конструктор - создаем булев вектор со всеми 0
    BoolVector(char*);
    BoolVector(char* s, int N); //N!=strlen(s); какую то часть строки откидываем (если N меньше длины) или недостающие позиции = 0 (если N больше длины)
    BoolVector(const BoolVector&); //конструктор копирования
    ~BoolVector() {delete []bv;}
    BoolVector& operator= (const BoolVector&);
    
    BoolVector(BoolVector&&) noexcept; // возврат временного объекта
    BoolVector& operator= (BoolVector&&) noexcept;
    
    int Weight(); //количество единиц
    UC operator[] (int); //смотрим значение бита
    
    bool operator== (BoolVector&);
    bool operator!= (BoolVector&);
    bool operator< (BoolVector&);
    bool operator> (BoolVector&);
    
    BoolVector operator& (BoolVector); //создаем новый вектор (обрываем больший вектор)
    BoolVector& operator&= (BoolVector); //изменяем вызываемый булев вектор
    
    BoolVector operator| (BoolVector); //донаращиваем меньший вектор нулями
    BoolVector& operator|= (BoolVector);
    
    BoolVector operator^ (BoolVector); //берем длину большего вектора
    BoolVector& operator^= (BoolVector);
    
    BoolVector operator~ (); //инверсия битов, создаем новый булев вектор
    BoolVector operator! ();
    
    BoolVector operator<< (int); // битовый сдвиг влево
    BoolVector& operator<<= (int);
    
    BoolVector operator>> (int); // битовый сдвиг вправо
    BoolVector& operator>>= (int);
    
    BoolVector& SetUp1(int); //устанавливаем 1 в какой-то позиции
    BoolVector& SetUp0(int);
    BoolVector& Invert(int);
    
    BoolVector& SetUp1(int k, int pos); //установить 1 в k компонентах, начиная с позиции p
    BoolVector& SetUp0(int k, int pos);
    BoolVector& Invert(int k, int pos); //меняем исходный вектор
    
    friend ostream& operator<< (ostream& r, BoolVector& X); //потоковый вывод
    friend istream& operator>> (istream& r, BoolVector& X); //потоковый ввод
};
