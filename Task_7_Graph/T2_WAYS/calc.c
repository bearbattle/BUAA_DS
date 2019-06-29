#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int beg, end, num;
} node;

node E[2000];
int visited[1001];
int routine[1001];
int n, e;

void Dfs(int now, int count);

void Init();

int main()
{
    Init();
    Dfs(0, 0);
    return 0;
}

void Init()
{
    int i;
    int head, tail, num;
    scanf("%d%d", &n, &e);
    for (i = 0; i < e; i++)
    {
        scanf("%d%d%d", &num, &head, &tail);
        E[num].num = num;
        E[num].beg = head;
        E[num].end = tail;
    }
}

void Dfs(int now, int count)
{
    int i;
    if (now == n - 1)
    {
        for (i = 0; i < count; i++)
        {
            printf("%d ", routine[i]);
        }
        puts("");
        return;
    }
    if (visited[now] == 1)
    {
        return;
    }
    for (i = 0; i <= e; i++)
    {
        if (E[i].beg == now)
        {
            routine[count] = E[i].num;
            visited[now] = 1;
            Dfs(E[i].end, count + 1);
            visited[now] = 0;
        }
        if (E[i].end == now)
        {
            routine[count] = E[i].num;
            visited[now] = 1;
            Dfs(E[i].beg, count + 1);
            visited[now] = 0;
        }
    }
}