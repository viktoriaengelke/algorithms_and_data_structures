#include "Code.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    
    char text[50];
    
    cout << "Введите фразу: ";
    cin.getline(text, 50);
    
    cout << "\nИсходный текст: " << text << endl << endl;
    Code c(text);
    
    cout << "Список частот:" << endl;
    c.PrintList();
    cout << endl;
    
    c.FormTree();
    cout << endl;
    
    cout << "Дерево Хаффмана:" << endl;
    c.PrintTree(0, c.GetHead());
    cout << endl;
    
    char encoded[500];
    c.CodeText(text, encoded);
    cout << "Закодированный текст: " << encoded << endl << endl;
    
    char decoded[500];
    c.DecodeText(encoded, decoded);
    cout << "Декодированный текст: " << decoded << endl;
    
    return 0;
}
