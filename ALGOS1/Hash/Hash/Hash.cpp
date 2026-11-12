#include "Hash.h"

void Hash::Add(int k)
{
    int h = k % p;
    if (TAB[h].key == -1) TAB[h].key = k;
    else //возникла коллизиция
    {
        int j; //номер ячейки в которую разместим ключ
        for (j = dim - 1; j >= 0 && TAB[j].key != -1; j--);
        TAB[j].key = k;
        //поиск последнего элемента цепочки коллизий
        int t = h;
        while(TAB[t].next != -1) t = TAB[t].next;
        TAB[t].next = j;
    }
}
