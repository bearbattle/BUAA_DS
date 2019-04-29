#include <stdio.h>

int n, m, q;

int Solve(int x)
{
    if (x == n)
        return (m - 1) % n;
    return (Solve(x + 1) + (m - 1) % x + 1) % (x+1);
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    int i;
    for (i = n; i >= 1; i--)
    {
        printf("%d\n", Solve(i));
    }
    return 0;
}