#include "BinTree.h"

Node* BinTree::Tree(int n, Node *p)
{
    if (n < 0)
    {
        cout<<"error!"<<endl;
        return NULL;
    }
    if (n == 0) return NULL;
    Node* q = new Node(rand()%50);
    q->parent = p;
    int nL = (n-1)/2;
    int nR = n - 1 - nL;
    q->left = Tree(nL, q);
    q->right = Tree(nR, q);
    return q;
}
void BinTree::Copy(Node *q, Node *p, int k)
{
    if (q == NULL) return;
    Node* t = new Node(q->key);
    t->parent = p;
    if (k == 0) p->left = t;
    else p->right = t;
    Copy(q->left, t, 0);
    Copy(q->right, t, 1);
}
BinTree::BinTree(int n)
{
    root = Tree(n, NULL);
}
BinTree::BinTree(int *a, int n)
{
    root = NULL;
        for (int i = 0; i < n; i++)
            Add(a[i], root);
}
BinTree::BinTree(const BinTree& X)
{
    if (X.root == NULL) root = NULL;
    else
    {
        root = new Node(X.root->key);
        Copy(X.root->left, root, 0);
        Copy(X.root->right, root, 1);
    }
}
BinTree::BinTree(BinTree&& X) noexcept
{
    root = X.root;
    X.root = NULL;
}
BinTree::~BinTree()
{
    Clear();
}
BinTree& BinTree::operator= (const BinTree& X)
{
    if (this == &X) return *this;
       Clear();
       if (X.root == NULL)
       {
           root = NULL;
           return *this;
       }
       root = new Node(X.root->key);
       Copy(X.root->left, root, 0);
       Copy(X.root->right, root, 1);
       return *this;
}
BinTree& BinTree::operator= (BinTree&& X) noexcept
{
    if (this == &X) return *this;
        Clear();
        root = X.root;
        X.root = NULL;
        return *this;
}

void BinTree::Add(int k, Node* p)
{
    if (p == root && p == NULL)
    {
        root = new Node(k);
        return;
    }
    if (p == NULL)
    {
        cout<<"error in add!"<<endl;
        return;
    }
    if (p->left == NULL)
    {
        Node *q = new Node(k);
        q->parent = p;
        p->left = q;
        return;
    }
    if (p->right == NULL)
    {
        Node *q = new Node(k);
        q->parent = p;
        p->right = q;
        return;
    }
    if (rand()%2) Add(k, p->left);
    else Add(k, p->right);
}
void BinTree::Del(Node *p)
{
    if (p == NULL) return;
    if (p == root)
    {
        DelRoot();
        return;
    }
    Node *q = p->parent;
    if (p->left == NULL && p->right == NULL)
    {
        if (q->left == p) q->left = NULL;
        else q->right = NULL;
        delete p;
        return;
    }
    if (p->left == NULL)
    {
        if (q->left == p) q->left = p->right;
        else q->right = p->right;
        p->right->parent = q;
        delete p;
        return;
    }
    if (p->right == NULL)
    {
        if (q->left == p) q->left = p->left;
        else q->right = p->left;
        p->left->parent = q;
        delete p;
        return;
    }
    Node *t = p;
    while (t->left != NULL) t = t->left;
    if (t->right == NULL) t->parent->left = NULL;
    else
    {
        t->parent->left = t->right;
        t->right->parent = t->parent;
    }
    
    p->key = t->key;
    delete t;
    return;
/*
 вместо последнего фрагмента (если информационное поле большое)
 if (q->left == p) q->left = t;
 else q->right = t;
 t->parent = q;
 
 t->left = p->left;
 t->right = p->right;
 
 if (p->left != NULL) p->left->parent = t;
 p->right->parent = t;
 delete p;
 return;
*/
}
void BinTree::DelRoot()
{
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL)
    {
        delete root;
        root = NULL;
        return;
    }
    Node* t;
    if (root->left != NULL)
    {
        t = root->left;
        while (t->right != NULL)
            t = t->right;
    }
    else
    {
        t = root->right;
        while (t->left != NULL)
            t = t->left;
    }
    root->key = t->key;
    Del(t);
}
//обходы в глубину
void BinTree::TreeTraversal_LCR(Node *p, int* a, int &n)
{
    if (p == NULL) return;
    TreeTraversal_LCR(p->left, a, n);
    a[n] = p->key;
    n++;
    TreeTraversal_LCR(p->right, a, n);
}
void BinTree::TreeTraversal_LRC(Node *p, int* a, int &n)
{
    if (p == NULL) return;
    TreeTraversal_LRC(p->left, a, n);
    TreeTraversal_LRC(p->right, a, n);
    a[n] = p->key;
    n++;
}
void BinTree::TreeTraversal_RLC(Node *p, int* a, int &n)
{
    if (p == NULL) return;
    TreeTraversal_RLC(p->right, a, n);
    TreeTraversal_RLC(p->left, a, n);
    a[n] = p->key;
    n++;
}
//обход в ширину через очередь
void BinTree::WidthTraversal(Node *p, int *a, int &n)
{
    if (p == NULL) return;
    int size = Count(p);
    Node** queue = new Node*[size];
    int f = 0, r = 0; //индекс первого в очереди и индекс куда добавлять новых
    queue[r++] = p;
    while (f < r)
    {
        Node* curr = queue[f++];
        a[n] = curr->key;
        n++;
        
        if (curr->left != NULL)
            queue[r++] = curr->left;
        if (curr->right != NULL)
            queue[r++] = curr->right;
    }
    
    delete[] queue;
}
/*
 второй более простой вараинт - вывод ключей не в массив, а на консоль
 //обходы в глубину
 void TreeTraversal_LCR(Node *p)
 {   if (p == NULL) return;
     TreeTraversal_LCR(p->left);
     cout<<p->key<<" ";
     TreeTraversal_LCR(p->right);
 }
 void TreeTraversal_LRC(Node *p); //обход лево-право-корень
 void TreeTraversal_RLC(Node *p); //обход право-лево-корень
 //обход в ширину
 void WidthTraversal(Node *p);
 */

Node* BinTree::FindKey(Node *p, int k)
{
    if (p == NULL) return NULL;
    if (p->key == k) return p;
    
    Node* res = FindKey(p->left, k);
    if (res != NULL) return res;
    
    return FindKey(p->right, k);
}
Node* BinTree::FindMax(Node *p)
{
    if (p == NULL) return NULL;
    Node* maxNode = p;
    Node* leftMax = FindMax(p->left);
    if (leftMax != NULL && (leftMax->key > maxNode->key))
        maxNode = leftMax;
    
    Node* rightMax = FindMax(p->right);
    if (rightMax != NULL && (rightMax->key > maxNode->key))
        maxNode = rightMax;
    
    return maxNode;
}
Node* BinTree::FindMin(Node *p)
{
    if (p == NULL) return NULL;
    Node* minNode = p;
    Node* leftMin = FindMin(p->left);
    if (leftMin != NULL && (leftMin->key < minNode->key))
        minNode = leftMin;
    
    Node* rightMin = FindMin(p->right);
    if (rightMin != NULL && (rightMin->key < minNode->key))
        minNode = rightMin;
    
    return minNode;
}
int BinTree::Count(Node *p)
{
    if (p == NULL) return 0;
    return 1 + Count(p->left) + Count(p->right);
}
void BinTree::PrintTree(int k, Node *p)
{
    if (p == NULL) return;
    PrintTree(k+5, p->right);
    for (int i = 0; i < k; i++) cout<<' ';
    cout<<p->key<<endl ;
    PrintTree(k+5, p->left);
}
void BinTree::Clear()
{
    while (root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if (root->left != NULL)
            Del(root->left);
        else
            Del(root->right);
    }
}
int BinTree::FindHight(Node *p)
{
    if (p == NULL) return 0;
    
    int leftHight = FindHight(p->left);
    int rightHight = FindHight(p->right);
    if (leftHight > rightHight)
        return (leftHight + 1);
    return (rightHight + 1);
}


