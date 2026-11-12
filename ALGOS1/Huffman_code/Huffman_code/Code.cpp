#include "Code.h"
using namespace std;

Code::Code(char s[])
{
    type = 0;
    int i, TAB[256] = {0};
    
    for (i = 0; s[i] != '\0'; i++)
        TAB[(unsigned char)s[i]]++;
    
    char p[2];
    p[1] = '\0';
    
    for (i = 0; i < 256 && TAB[i] == 0; i++);
    
    if (i == 256)
        head = NULL;
    else
    {
        p[0] = (char)i;
        head = new Node(p, TAB[i], NULL, NULL, NULL);
        i++;
        
        while(i < 256)
        {
            if(TAB[i] != 0)
            {
                p[0] = (char)i;
                Node* newNode = new Node(p, TAB[i], NULL, NULL, NULL);
                
                if(TAB[i] < head->freq)
                    AddToHead(newNode);
                else
                {
                    Node* t = head;
                    while(t->next != NULL && t->next->freq <= TAB[i])
                        t = t->next;
                    
                    if(t->next == NULL)
                        AddToTail(newNode);
                    else
                        AddAfter(t, newNode);
                }
            }
            i++;
        }
    }
}

Code::Code(const Code& other)
{
    type = other.type;
    head = NULL;
    
    if(other.head == NULL)
        return;
    
    if(type == 0)
    {
        Node* current = other.head;
        while(current != NULL)
        {
            AddToTail(current->str, current->freq);
            current = current->next;
        }
    }
    else
    {
        Copy(other.head, NULL, 0);
    }
}

void Code::Copy(Node *q, Node *p, int k)
{
    if(q == NULL) return;
    
    Node* newNode = new Node(q->str, q->freq, NULL, NULL, NULL);
    
    if(p == NULL)
        head = newNode;
    else
    {
        if(k == 0)
            p->left = newNode;
        else
            p->right = newNode;
    }
    
    Copy(q->left, newNode, 0);
    Copy(q->right, newNode, 1);
}

Code::Code(Code&& other) noexcept
{
    head = other.head;
    type = other.type;
    other.head = NULL;
    other.type = 0;
}

Code::~Code()
{
    Clear(head);
}

Code& Code::operator= (const Code& other)
{
    if(this == &other)
        return *this;
    
    Clear(head);
    head = NULL;
    type = other.type;
    
    if(other.head == NULL)
        return *this;
    
    if(type == 0)
    {
        Node* current = other.head;
        while(current != NULL)
        {
            AddToTail(current->str, current->freq);
            current = current->next;
        }
    }
    else
    {
        Copy(other.head, NULL, 0);
    }
    
    return *this;
}

Code& Code::operator= (Code&& other) noexcept
{
    if(this == &other)
        return *this;
    
    Clear(head);
    head = other.head;
    type = other.type;
    other.head = NULL;
    other.type = 0;
    
    return *this;
}

void Code::AddToTail(char s[], int f)
{
    Node* newNode = new Node(s, f, NULL, NULL, NULL);
    AddToTail(newNode);
}

void Code::AddToTail(Node* p)
{
    if(head == NULL)
        head = p;
    else
    {
        Node* t = head;
        while(t->next != NULL)
            t = t->next;
        t->next = p;
    }
}

void Code::AddToHead(char s[], int f)
{
    Node* newNode = new Node(s, f, NULL, NULL, NULL);
    AddToHead(newNode);
}

void Code::AddToHead(Node * p)
{
    p->next = head;
    head = p;
}

void Code::AddAfter(Node* pos, char s[], int f)
{
    Node* newNode = new Node(s, f, NULL, NULL, NULL);
    AddAfter(pos, newNode);
}

void Code::AddAfter(Node* pos, Node * p)
{
    if(pos == NULL)
    {
        AddToHead(p);
        return;
    }
    p->next = pos->next;
    pos->next = p;
}

void Code::DelHead()
{
    if(head == NULL) return;
    Node* t = head;
    head = head->next;
    delete t;
}

void Code::Clear(Node* p)
{
    if(p == NULL) return;
    
    if(type == 0)
    {
        Node* current = p;
        while(current != NULL)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    else
    {
        Clear(p->left);
        Clear(p->right);
        delete p;
    }
}

bool Code::Empty()
{
    return head == NULL;
}

void Code::PrintList()
{
    if(type != 0)
    {
        cout << "Это не список!" << endl;
        return;
    }
    
    Node* t = head;
    while(t != NULL)
    {
        cout << "Символ: '" << t->str << "', частота: " << t->freq << endl;
        t = t->next;
    }
}

void Code::PrintTree(int k, Node *p)
{
    if (p == NULL) return;
    PrintTree(k+5, p->right);
    for (int i = 0; i < k; i++) cout << ' ';
    cout << p->freq << endl;
    PrintTree(k+5, p->left);
}

bool Code::Find(char ch, char p[])
{
    for(int i = 0; p[i] != '\0'; i++)
        if(p[i] == ch)
            return true;
    return false;
}

void Code::FormTree()
{
    if(head == NULL)
    {
        cout << "Список пуст" << endl;
        return;
    }
    
    while(head->next != NULL)
    {
        Node* p1 = head;
        Node* p2 = head->next;
        
        head = p2->next;
        p1->next = NULL;
        p2->next = NULL;
        
        int newFreq = p1->freq + p2->freq;
        char* newStr = new char[strlen(p1->str) + strlen(p2->str) + 1];
        strcpy(newStr, p1->str);
        strcat(newStr, p2->str);
        
        Node* parent = new Node(newStr, newFreq, NULL, p1, p2);
        delete[] newStr;
        
        if(head == NULL || newFreq < head->freq)
            AddToHead(parent);
        else
        {
            Node* t = head;
            while(t->next != NULL && t->next->freq <= newFreq)
                t = t->next;
            
            if(t->next == NULL)
                AddToTail(parent);
            else
                AddAfter(t, parent);
        }
    }
    
    type = 1;
}

void Code::CodeText(char s[], char code[])
{
    if(type == 0)
    {
        cout << "Кодирование невозможно: это список, а не дерево!" << endl;
        return;
    }
    
    if(head == NULL)
    {
        cout << "Дерево пусто!" << endl;
        code[0] = '\0';
        return;
    }
    
    int TAB[256] = {0};
    for(int i = 0; s[i] != '\0'; i++)
        TAB[(unsigned char)s[i]]++;
    
    char CodeTAB[256][100];
    
    for(int i = 0; i < 256; i++)
        CodeTAB[i][0] = '\0';
    
    for(int i = 0; i < 256; i++)
    {
        if(TAB[i] != 0)
        {
            Node* t = head;
            char tempCode[100] = "";
            
            while(t->left != NULL || t->right != NULL)
            {
                if(t->left != NULL && Find((char)i, t->left->str))
                {
                    strcat(tempCode, "0");
                    t = t->left;
                }
                else if(t->right != NULL)
                {
                    strcat(tempCode, "1");
                    t = t->right;
                }
            }
            strcpy(CodeTAB[i], tempCode);
        }
    }
    
    code[0] = '\0';
    int maxSize = strlen(s) * 20;
    
    for(int i = 0; s[i] != '\0'; i++)
        strcat(code, CodeTAB[(unsigned char)s[i]]);
}

void Code::DecodeText(char code[], char s[])
{
    if(type == 0)
    {
        cout << "Декодирование невозможно: это список, а не дерево!" << endl;
        s[0] = '\0';
        return;
    }
    
    if(head == NULL)
    {
        cout << "Дерево пусто!" << endl;
        s[0] = '\0';
        return;
    }
    
    s[0] = '\0';
    Node* current = head;
    
    for(int i = 0; code[i] != '\0'; i++)
    {
        if(code[i] == '0')
            current = current->left;
        else
            current = current->right;
        
        if(current->left == NULL && current->right == NULL)
        {
            char temp[2];
            temp[0] = current->str[0];
            temp[1] = '\0';
            strcat(s, temp);
            current = head;
        }
    }

}
