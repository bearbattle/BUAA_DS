#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *word;
    int sum;
    struct Node *next;
} node;

node *head;
FILE *IN;

void InitTable();
node *Find(node *p);
void Insert(node *x, node *p);
void Print();
int GetWord();

int main()
{
    InitTable();
    Print();
    return 0;
}

void InitTable()
{
    node *tmp;
    node *pos;
    char *s;
    //表头初始化
    head = (node *)malloc(sizeof(node));
    head->word = "\0";
    head->sum = 0;
    head->next = NULL;

    IN = fopen("article.txt", "r");
    tmp = (node *)malloc(sizeof(node));
    s = (char *)malloc(1000);
    while (GetWord(s) != 0)
    {
        tmp->word = s;
        pos = Find(tmp);
        if (pos != NULL)
        {
            tmp->sum = 1;
            Insert(tmp, pos);
        }
        tmp = (node *)malloc(sizeof(node));
        s = (char *)malloc(1000);
    }
    return;
}

void Insert(node *x, node *p) //在 p 后面插入一个 *x 节点
{
    x->next = p->next;
    p->next = x;
    return;
}

node *Find(node *p) //查找插入位置
{
    node *now, *pre;
    long long flag;
    now = head->next;
    pre = head;
    if (head->next == NULL)
    {
        return head;
    }
    while (now != NULL)
    {
        flag = strcmp(now->word, p->word);
        if (flag < 0)
        {
            pre = now;
            now = now->next;
            continue;
        }
        if (flag == 0)
        {
            now->sum++;
            return NULL;
        }
        if (flag > 0)
        {
            break;
        }
    }
    return pre;
}

void Print()
{
    node *p;
    p = head->next;
    while (p != NULL)
    {
        printf("%s %d\n", p->word, p->sum);
        p = p->next;
    }
    return;
}

int GetWord(char *s)
{
    char c;
    while (!isalpha(c = fgetc(IN)))
        if (c == EOF)
            return 0;
    do
    {
        *(s++) = tolower(c);
    } while (isalpha(c = fgetc(IN)));
    *s = '\0';
    return 1;
}