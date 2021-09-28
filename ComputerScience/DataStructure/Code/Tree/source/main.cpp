#include<iostream>
#include<iomanip>
using namespace std;

struct BTNode
{
    //二叉树结点结构体,包含值 左子结点指针 右子结点指针
    char data;
    struct BTNode* lchild;
    struct BTNode* rchild;
    BTNode()
    {
        lchild = NULL;
        rchild = NULL;
    }
};

void printTree(BTNode* p,int h = 0)
{
    if (p == NULL)
    {
        cout << endl;
        return;
    }
    cout << setw(4) << setiosflags(ios::left) << p->data;
    printTree(p->lchild,h+1);
    for (int i = 0; i < h+1; i++)
    {
        cout << setw(4) << setiosflags(ios::left) << ' ';
    }
    printTree(p->rchild,h+1);
}

void preorder(BTNode* p)
{
    if (p == NULL)
        return;
    cout << p->data << ' ';
    preorder(p->lchild);
    preorder(p->rchild);
}

BTNode* createtree(char pre[], char in[], int L1, int R1, int L2, int R2)
{
    BTNode* s;
    int i;
    if (L1 > R1)
    {
        return NULL;
    }
    s = new BTNode;
    for (i = L2; i <= R2 && in[i] != pre[L1]; ++i)
    {
    }
    s->data = in[i];

    s->lchild = createtree(pre, in, L1 + 1, L1 + i - L2, L2, i - 1);
    s->rchild = createtree(pre, in, L1 + i - L2 + 1, R1, i + 1, R2);
    return s;
}

void test1()
{
    //前序中序遍历结果构造二叉树
    char pre[8] = { 'A','B','C','D','E','F','G','H' };
    char in[8] = { 'C','B','E','D','F','A','H','G' };
    BTNode* p = createtree(pre, in, 0, 7, 0, 7);
    //输出二叉树
    cout << p->data;
    cout << p->lchild->data;
    cout << p->rchild->data;

    cout << p->lchild->lchild->data;
    cout << p->lchild->rchild->data;

    cout << p->lchild->rchild->lchild->data;
    cout << p->lchild->rchild->rchild->data;

    cout << p->rchild->lchild->data;
}
void test2()
{
    //打印二叉树
    char pre[8] = { 'A','B','C','D','E','F','G','H' };
    char in[8] = { 'C','B','E','D','F','A','H','G' };
    BTNode* p = createtree(pre, in, 0, 7, 0, 7);
    printTree(p);
}
int main()
{
    //test1();
    test2();
    return 0;

}