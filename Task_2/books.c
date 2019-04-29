#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[55], author[25], press[35], date[15];
    struct Node *next;
} node;
node *head;

void InitTable(FILE *IN);
node *Find(node *p);
void Insert(node *x, node *p);
void Delete(char *str);
void Print(char *str);

int main()
{
    int mode;
    char str[100];
    node *tmp;
    node *pos;
    FILE *IN, *OUT;
    IN = fopen("books.txt", "r");
    InitTable(IN);
    fclose(IN);
    while (1)
    {
        scanf("%d", &mode);
        getchar();
        if (mode == 0)
        {
            break;
        }
        switch (mode)
        {
        case 1: //录入新书
            tmp = malloc(sizeof(node));
            scanf("%s %s %s %s", tmp->name, tmp->author, tmp->press, tmp->date);
            //Lower(tmp->nameA,tmp->name);
            pos = Find(tmp);
            Insert(tmp, pos);
            break;
        case 2: //查找
            scanf("%s", str);
            Print(str);
            break;
        case 3: //删除
            scanf("%s", str);
            Delete(str);
            break;
        }
    }
    OUT = fopen("ordered.txt", "w");
    tmp = head->next;
    while (tmp != NULL)
    {
        fprintf(OUT, "%-49s %-19s %-29s %-9s\n", tmp->name, tmp->author, tmp->press, tmp->date);
        tmp = tmp->next;
    }
    fclose(OUT);
    return 0;
}

void InitTable(FILE *IN)
{
    node *tmp;
    node *pos;
    //表头初始化
    head = malloc(sizeof(node));
    memset(head->name, 0, sizeof(head->name));
    memset(head->author, 0, sizeof(head->author));
    memset(head->press, 0, sizeof(head->press));
    memset(head->date, 0, sizeof(head->date));
    head->next = NULL;
    //读入初始书库
    tmp = malloc(sizeof(node));
    while (fscanf(IN, "%s %s %s %s", tmp->name, tmp->author, tmp->press, tmp->date) != EOF)
    {
        pos = Find(tmp);
        Insert(tmp, pos);
        tmp = malloc(sizeof(node));
    }
    return;
}

void Insert(node *x, node *p) //在 p 后面插入一个 *x 节点
{
    node *tmp;
    tmp = p->next;
    p->next = x;
    x->next = tmp;
}

node *Find(node *p) //查找插入位置
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
    return pre;
}

void Print(char *str)
{
    node *p;
    p = head->next;
    while (p != NULL)
    {
        if (strstr(p->name, str) != NULL)
        {
            printf("%-49s %-19s %-29s %-9s\n", p->name, p->author, p->press, p->date);
        }
        p = p->next;
    }
    return;
}

void Delete(char *str)
{
    node *p;
    node *pre;
    p = head->next;
    pre = head;
    while (p != NULL)
    {
        if (strstr(p->name, str) != NULL)
        {
            pre->next = p->next;
            free(p);
            p = pre->next;
            continue;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
    return;
}
