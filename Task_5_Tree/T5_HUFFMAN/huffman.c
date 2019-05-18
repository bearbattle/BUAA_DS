/*************************
*   Title:  Huffman
*   Author: BearHuchao
*   Data:   2019.5.18
*   Note:   Compress File
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree
{
    char data;
    int wei;
    struct Tree *left, *right;
} tree;

typedef struct Node
{
    tree *data;
    struct Node *next;
} node;

typedef unsigned char u8;

tree *calc[128];
node *head;
char code[128][130];
int flag[128];

int cmp(const void *p, const void *q); //比较函数
void Init();                           //初始化，统计词频
void Trans();                          //转化为链表
node *Find(node *p);                   //查找插入位置
void Insert(node *x, node *p);         //插入操作
void Select();                         //选择算法
void Dfs(tree *des, const char *ans);
void Encode();

int main()
{
    Init();
    Trans();
    while (head->next->next != NULL)
    {
        Select();
    }
    Dfs(head->next->data, "");
    Encode();
    return 0;
}

void Init()
{
    FILE *IN;
    int i;
    char c;
    IN = fopen("input.txt", "r");
    for (i = 0; i < 128; i++)
    {
        calc[i] = (tree *)malloc(sizeof(tree));
        calc[i]->data = (char)i;
        calc[i]->wei = 0;
        calc[i]->left = NULL;
        calc[i]->right = NULL;
    }
    calc[0]->wei = 1;
    while ((c = fgetc(IN)) != EOF)
    {
        if (c != '\n')
            calc[c]->wei++;
    }
    qsort(calc, 128, 8, cmp);
    fclose(IN);
}

void Trans()
{
    int beg = 0;
    tree *tt;
    node *pos;
    node *tmp;
    int i;

    while (calc[beg]->wei == 0)
        flag[beg++] = 1;

    head = (node *)malloc(sizeof(node));
    tt = (tree *)malloc(sizeof(tree));
    tt->wei = -1;
    tt->data = -1;
    tt->left = NULL;
    tt->right = NULL;
    head->data = tt;
    pos = head;
    for (i = beg; i < 128; i++)
    {
        tmp = (node *)malloc(sizeof(node));
        pos->next = tmp;
        tmp->data = calc[i];
        tmp->next = NULL;
        pos = pos->next;
    }
    return;
}

void Insert(node *x, node *p) //在 p 后面插入一个 *x 节点
{
    x->next = p->next;
    p->next = x;
}

node *Find(node *p) //查找插入位置
{
    node *ans, *pre;
    ans = head;
    pre = head;
    while (ans != NULL)
    {
        pre = ans;
        ans = ans->next;
        if (ans == NULL || p->data->wei < ans->data->wei)
            break;
    }
    return pre;
}

void Select()
{
    node *n1, *n2, *nt;
    tree *t1, *t2, *tt;
    n1 = head->next;
    n2 = n1->next;
    t1 = n1->data;
    t2 = n2->data;
    tt = (tree *)malloc(sizeof(tree));
    tt->data = -1;
    tt->left = t1;
    tt->right = t2;
    tt->wei = (tt->left->wei) + (tt->right->wei);
    nt = (node *)malloc(sizeof(tree));
    nt->data = tt;
    head->next = n2->next; //删除前两个节点
    Insert(nt, Find(nt));
}

void Dfs(tree *des, const char *ans)
{
    char tmp[130];
    if (des->data != -1)
    {
        strcpy(code[des->data], ans);
        return;
    }
    strcpy(tmp, ans);
    if (des->left != NULL)
    {
        strcat(tmp, "0");
        Dfs(des->left, tmp);
    }
    strcpy(tmp, ans);
    if (des->right != NULL)
    {
        strcat(tmp, "1");
        Dfs(des->right, tmp);
    }
}

void Encode()
{
    FILE *IN, *OUT;
    char c;
    u8 block = 0; //写入块
    int dig = 0;  //第几位
    int pos;
    IN = fopen("input.txt", "r");
    OUT = fopen("output.txt", "w");
    while ((c = fgetc(IN)) != EOF)
    {
        if (c == '\n')
        {
            fputc(c, OUT);
            continue;
        }
        pos = 0;
        while (code[c][pos] != '\0')
        {
            block = (block << 1) | (code[c][pos++] & 1);
            dig++;
            if (dig == 8)
            {
                fputc(block, OUT);
                printf("%x", block);
                dig = 0;
            }
        }
    }
    pos = 0;
    while (code[0][pos] != '\0')
    {
        block = (block << 1) | (code[0][pos++] & 1);
        dig++;
        if (dig == 8)
        {
            fputc(block, OUT);
            printf("%x", block);
            dig = 0;
        }
    }
    while (dig > 0 && dig < 8)
    {
        block = (block << 1) | 0;
        dig++;
        if (dig == 8)
        {
            fputc(block, OUT);
            printf("%x", block);
            dig = 0;
        }
    }
}

int cmp(const void *p, const void *q)
{
    tree *a, *b;
    a = *(tree **)p;
    b = *(tree **)q;
    if (a->wei != b->wei)
        return a->wei > b->wei ? 1 : -1;
    return a->data > b->data ? 1 : -1;
}