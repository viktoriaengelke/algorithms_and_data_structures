#pragma once
//#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#include "BoolVector.h"

class BoolMatrix
{
    BoolVector* BM;
    int m, n; //m - количество строк, n - количество столбцов
    
    int Max (char** s, int m);
public:
    BoolMatrix (int M = 1, int N = 1);
    BoolMatrix (char** s, int m);
    BoolMatrix (const BoolMatrix&); //конструктор копирования
    BoolMatrix (BoolMatrix&&) noexcept; //конструктор перемещения
    ~BoolMatrix() {delete [] BM;}
    
    BoolMatrix& operator= (const BoolMatrix&);
    BoolMatrix& operator= (BoolMatrix&&) noexcept;
    
    void Scan(int, int); //ввод, вывод
    void Print();
    
    BoolVector& operator[] (int pos);
    bool operator== (const BoolMatrix&); //можно и без ссылки, тогда создается копия
    bool operator!= (const BoolMatrix&);
    
    BoolMatrix& SetUp1 (int i, int j); //элемент матрицы [i][j]=1
    BoolMatrix& SetUp0 (int i, int j); //[i][j]=0
    BoolMatrix& Invert (int i, int j); //[i][j] - инвертировать
    
    BoolMatrix& SetUp1 (int i, int pos, int kol); //установить kol элементов i-ой строки начиная с позиции pos в 1
    BoolMatrix& SetUp0 (int i, int pos, int kol);
    BoolMatrix& Invert (int i, int pos, int kol);
    
    BoolMatrix operator& (BoolMatrix); //должны быть матрицы одинакового размера
    BoolMatrix& operator&= (BoolMatrix);
    
    BoolMatrix operator| (BoolMatrix);
    BoolMatrix& operator|= (BoolMatrix);
    
    BoolMatrix operator^ (BoolMatrix);
    BoolMatrix& operator^= (BoolMatrix);
    
    BoolMatrix& operator~ (); //изменяется *this
    BoolMatrix operator! (); //создается новая матрица
    
    BoolMatrix ShiftLeft (int i, int kol); //номер строки и на сколько сдвинуть
    BoolMatrix& ShiftLeftEq (int i, int kol);
    
    BoolMatrix ShiftRight (int i, int kol); //номер строки и на сколько сдвинуть
    BoolMatrix& ShiftRightEq (int i, int kol);
    
    BoolVector Conj(); //конъюнкция всех строк
    BoolVector Disj(); //дизъюнкция всех строк
    BoolVector Xor(); //xor всех строк
    
    friend ostream& operator<< (ostream& os, BoolMatrix& X);
    friend istream& operator>> (istream& is, BoolMatrix& X);
};
