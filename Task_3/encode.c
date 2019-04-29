#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char c;
    struct Node *next;
} node;

char _key[96];
char key[96];
node head;
node *last;

void PreGen();
void KeyGen();
void Encode();
void InitList();

int main()
{
    PreGen();
    KeyGen();
    Encode();
    return 0;
}

void PreGen()
{
    char s[1000];
    char used[95];
    char *p;
    char i = 0, j;
    memset(_key, 0, sizeof(_key));
    memset(used, 0, sizeof(used));
    fgets(s, 1000, stdin);
    for (p = s; *p != '\0'; p++)
    {
        if ((*p > 31) && (*p < 127) && (!used[*p - 32]))
        {
            used[*p - 32] = 1;
            _key[i++] = *p;
        }
    }
    j = i;
    for (i = 32; i < 127; i++)
    {
        if (!used[i - 32])
            _key[j++] = (char)i;
    }
    return;
}

void KeyGen()
{
    node *pre;
    node *now;
    int i;
    char c;
    InitList(); //形成环
    pre = &head;
    while (head.next != head.next->next)
    {
        now = pre->next;
        c = now->c;
        if (now == head.next) //删除第一个：头节点换位置，尾节点更新
        {
            head.next = now->next;
            last->next = head.next;
        }
        else
        {
            pre->next = now->next;
        }
        if (now == last)
            last = pre;
        free(now);
        for (i = 1; i < c; i++)
        {
            pre = pre->next;
        }
        key[c - 32] = pre->next->c;
    }
    key[head.next->c-32] = _key[0];
    return;
}

void Encode()
{
    FILE *IN, *OUT;
    char c;
    IN = fopen("in.txt", "r");
    OUT = fopen("in_crpyt.txt", "w");
    while ((c = fgetc(IN)) != EOF)
    {
        if (c > 31 && c < 127)
            fputc(key[c - 32], OUT);
        else
            fputc(c, OUT);
    }
    return;
}

void InitList()
{
    node *p, *q;
    int i;
    p = (node *)malloc(sizeof(node));
    head.next = p;
    for (i = 0; i < 95; i++)
    {
        p->c = _key[i];
        q = (node *)malloc(sizeof(node));
        p->next = q;
        last = p;
        p = q;
    }
    p = last;
    p->next = head.next;
    return;
}
