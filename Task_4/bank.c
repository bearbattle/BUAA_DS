#include <stdio.h>

int rem = 0, cnt = 0;
int win = 3;
int add[200];
int queue[1000], user[1000];
int head = 0, tail = 0;

int main()
{
    int n, t;
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &add[i]);
    }
    t = 0;
    while (t <= n || tail != head)
    {
        if (t <= n)
        {
            for (i = 0; i < add[t]; i++)
            {
                cnt++;
                queue[tail++] = cnt; //进队
                user[cnt] = t;       //进队时间
                rem++;
            }
        }
        while (rem >= 7 * win && win < 5 && add[t] != 0 && t <= n) //窗户++
        {
            win++;
        }
        for (i = 0; i < win; i++)
        {
            if (rem != 0)
            {
                user[queue[head]] = t - user[queue[head]]; //等待时间=出队时间-入队时间
                head++;                                    //出队
                rem--;
            }
        }
        while (rem < 7 * win && win > 3)
        {
            win--;
        }
        t++;
    }
    for (i = 1; i <= cnt; i++)
    {
        printf("%d : %d\n", i, user[i]);
    }
    return 0;
}