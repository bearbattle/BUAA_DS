#include <stdio.h>
#include <stdlib.h>

#define INF 0x7FFFFFFF

typedef struct Edge
{
    int num, weight;
} edge;

int n;
edge G[1001][1001];

void Init();

int main()
{
    Init();
}

void Init()
{
    int i;
    int e;
    int num, beg, end, wei;
    scanf("%d%d", &n, &e);
    for (i = 0; i < e; i++)
    {
        scanf("%d%d%d%d", &num, &beg, &end, &wei);
        G[beg][end].num = num;
        G[beg][end].weight = wei;
        G[end][beg].num = num;
        G[end][beg].weight = wei;
    }
}