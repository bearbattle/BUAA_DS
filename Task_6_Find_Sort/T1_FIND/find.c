/*************************
*   Title:  Find
*   Author: BearHuchao
*   Data:   2019.5.20
*   Note:   Several Ways to Find String
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NHASH 3001
#define MULT 37

typedef struct Node
{
    int n;
    char *list;
    struct Node *next;
} node;

typedef struct Answer
{
    int res; //Result
    int cnt; //Times Count
} ans;

node hash[3000];     //Hash Table
int ind[26][2];      //Index
char word[3500][25]; //Word List
int wc;              //Word Count

int Init();

unsigned int Hash(char *str);

void SetAns(ans *des);

ans Find(char *des);

ans Half(char *str, int l, int r);

ans QHash(char *str);

int main()
{
    ans out;
    char query[30];
    int method;
    wc = Init();
    while (scanf("%s%d", query, &method) != EOF)
    {
        SetAns(&out);
        switch (method)
        {
        case 1:
            out = Find(query);
            break;
        case 2:
            out = Half(query, 0, wc - 1);
            break;
        case 3:
            out = Half(query, ind[*query - 'a'][0], ind[*query - 'a'][0] + ind[*query - 'a'][1] - 1);
            break;
        default:
            out = QHash(query);
        }
        printf("%d %d\n", out.res, out.cnt);
    }
    return 0;
}

int Init()
{
    FILE *IN;
    int i = 0;
    int val;
    node *pos, *tmp;

    IN = fopen("dictionary3000.txt", "r");
    while (fscanf(IN, "%s", word[i]) != EOF)
    {
        /*****Hash Build Start*****/
        val = Hash(word[i]);
        hash[val].n++;
        if (hash[val].n > 1)
        {
            pos = &hash[val];
            while (pos->next != NULL)
            {
                pos = pos->next;
            }
            tmp = (node *)malloc(sizeof(node));
            pos->next = tmp;
            tmp->n = pos->n - 1;
            tmp->list = word[i];
            tmp->next = NULL;
        }
        else
        {
            hash[val].list = word[i];
        }
        /*****Hash Build End*****/

        /*****Index Build Start*****/
        if (ind[*word[i] - 'a'][1] == 0)
        {
            ind[*word[i] - 'a'][0] = i;
        }
        ind[*word[i] - 'a'][1]++;
        /*****Index Build End*****/
        i++;
    }
    return i;
}

void SetAns(ans *des)
{
    des->res = 0;
    des->cnt = 0;
}

ans Find(char *des)
{
    ans tmp;
    int i = 0;
    while (i++ < wc)
    {
        if (strcmp(word[i], des) == 0)
        {
            tmp.res = 1;
            tmp.cnt = i + 1;
            return tmp;
        }
        if (strcmp(word[i], des) > 0)
        {
            tmp.res = 0;
            tmp.cnt = i + 1;
            return tmp;
        }
    }
    tmp.res = 0;
    tmp.cnt = i + 1;
    return tmp;
}

unsigned int Hash(char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)

        h = MULT * h + *p;
    return h % NHASH;
}

ans Half(char *str, int l, int r)
{
    ans tmp;
    int flag, mid;
    tmp.cnt = 0;
    while (l <= r)
    {
        mid = (l + r) / 2;
        flag = strcmp(word[mid], str);
        tmp.cnt++;
        if (flag == 0)
        {
            tmp.res = 1;
            return tmp;
        }
        if (flag > 0)
        {
            r = mid - 1;
        }
        if (flag < 0)
        {
            l = mid + 1;
        }
    }
    tmp.res = 0;
    return tmp;
}

ans QHash(char *str)
{
    ans tmp;
    node *pos;
    int flag = Hash(str);
    int cmp;
    if (hash[flag].n == 0)
    {
        tmp.res = 0;
        tmp.cnt = 0;
        return tmp;
    }
    pos = &hash[flag];
    tmp.cnt = 0;
    while (pos != NULL)
    {
        cmp = strcmp(pos->list, str);
        tmp.cnt++;
        if (cmp == 0)
        {
            tmp.res = 1;
            return tmp;
        }
        if (cmp > 0)
        {
            tmp.res = 0;
            return tmp;
        }
        pos = pos->next;
    }
    tmp.res = 0;
    return tmp;
}