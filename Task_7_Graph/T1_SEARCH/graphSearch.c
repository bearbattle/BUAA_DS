#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int G0[100][100];
int G[100][100];
int visited[100];

void Dfs(int pos);
void Bfs(int pos);
void Del(int num);

int e, v;

int main()
{
    int beg, end;
    int i;
    scanf("%d%d", &v, &e);
    memset( G0, 0, sizeof(G0));
    for(i = 0; i < e; i++)
    {
        scanf("%d%d", &beg, &end);
        G0[beg][end] = 1;
        G0[end][beg] = 1;
    }
    memcpy(G, G0, sizeof(G));
    memset(visited, 0, sizeof(visited));
    Dfs(0);
    puts("");
    memcpy(G, G0, sizeof(G));
    memset(visited, 0, sizeof(visited));
    Bfs(0);
    puts("");
    scanf("%d", &beg);
    Del(beg);
    memcpy(G, G0, sizeof(G));
    memset(visited, 0, sizeof(visited));
    Dfs(0);
    puts("");
    memcpy(G, G0, sizeof(G));
    memset(visited, 0, sizeof(visited));
    Bfs(0);
    puts("");
    return 0;
}

void Dfs(int pos)
{
    int i, j;
    printf("%d ", pos);
    visited[pos] = 1;
    for(i = 0; i < v; i++)
    {
        if(G[pos][i])
        {
            G[pos][i] = 0;
            G[i][pos] = 0;
            if(!visited[i])
            {
                Dfs(i);
            }
        }
    }
}

void Bfs(int pos)
{
    int queue[200];
    int head = 0, tail = 0;
    int i, now;
    now = pos;
    printf("%d ", now);
    visited[now] = 1;
    for(i = 0; i < v; i++)
    {
        if(G[now][i])
        {
            G[now][i] = 0;
            G[i][now] = 0;
            queue[tail++] = i;
        }
    }
    while(head < tail)
    {
        now = queue[head++];
        if(!visited[now])
        {
            ;
            printf("%d ", now);
            visited[now] = 1;
        }

        for(i = 0; i < v; i++)
        {
            if(G[now][i])
            {
                G[now][i] = 0;
                G[i][now] = 0;
                if(!visited[i])
                {
                    queue[tail++] = i;
                }
            }
        }
    }
}

void Del(int num)
{
    int i;
    for(i = 0; i < v; i++)
        G0[i][num] = 0;
    memset(G0[i], 0, sizeof(G0[i]));
}

