#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[30];
    char num[15];
    struct Node *next;
} node;

node *head;
int sum;

node *Find(node *p);
void Insert(node *x, node *p, int mode);
void Print();

int main()
{
    int n;
    scanf("%d", &n);
    head = malloc(sizeof(node));
    memset(head->name, 0, sizeof(head->name));
    head->next = NULL;
    node *tmp;
    node *pos;
    while (n--)
    {
        tmp = malloc(sizeof(node));
        scanf("%s %s", tmp->name, tmp->num);
        pos = Find(tmp);
        if (pos == NULL)
            continue;
        Insert(tmp, pos, sum);
    }
    Print();
    return 0;
}

void Insert(node *x, node *p, int mode)
{
    node *tmp;
    tmp = p->next;
    p->next = x;
    x->next = tmp;
}

node *Find(node *p)
{
    node *ans, *pre;
    int flag;
    ans = head;
    pre = head;
    while (ans != NULL)
    {
        flag = strcmp(ans->name, p->name);
        if (flag <= 0)
        {
            pre = ans;
            ans = ans->next;
            continue;
        }
        if (flag > 0)
        {
            break;
        }
    }
    if (strcmp(pre->num, p->num) == 0)
    {
        return NULL;
    }
    return pre;
}

void Print()
{
    node *p;
    node *pre;
    p = head->next;
    pre = head;
    while (p != NULL)
    {
        if (strcmp(pre->name, p->name) == 0)
        {
            printf("%s_%d %s\n", p->name, ++sum, p->num);
        }
        else
        {
            sum = 0;
            printf("%s %s\n", p->name, p->num);
        }
        pre = p;
        p = p->next;
    }
    return;
}
