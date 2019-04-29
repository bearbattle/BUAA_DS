#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num[10], flag[10]; //排列数组与被占用数组
int n;                 //全排列的数目

void Dfs(int dep);
void Out();

int main()
{
    scanf("%d", &n);
    Dfs(0);
    return 0;
}

void Dfs(int dep)
{
    int i;
    if (dep == n)
    {
        Out();
        return;
    }
    for (i = 0; i < n; i++)
    {
        if (!flag[i])
        {
            num[dep] = i + 1;
            flag[i] = 1;
            Dfs(dep + 1);
            num[dep] = 0;
            flag[i] = 0;
        }
    }
}

void Out()
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", num[i]);
    }
    puts("");
}