#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s0[10001]; //输入字符串
char p, q;      //前后两个字符
int l = 0, r;   //保留区间左右端点
int mid;        //-点

int check(int index); //检查扩展合法性
void option(int x);   //字符串替换操作

int main()
{
    int i;

    scanf("%s", s0);

    for (i = 0; s0[i] != '\0'; i++)
    {
        if (s0[i] == '-')
        {
            mid = i;
            option(check(mid));
        }
    }
    printf("%s", s0 + l);
    return 0;
}

int check(int index)
{
    p = s0[index - 1];
    q = s0[index + 1];
    if (q <= p)
        return 0;
    if ((p >= 'a' && p <= 'z') && (q >= 'a' && q <= 'z'))
    {
        r = index - 1;
        return 1;
    }
    if ((p >= 'A' && p <= 'Z') && (q >= 'A' && q <= 'Z'))
    {
        r = index - 1;
        return 2;
    }
    if ((p >= '0' && p <= '9') && (q >= '0' && q <= '9'))
    {
        r = index - 1;
        return 3;
    }
    return 0;
}

void option(int x)
{
    char AZ[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
         az[] = "abcdefghijklmnopqrstuvwxyz",
         num[] = "0123456789";
    if (x == 0)
        return;

    //前字符串输出
    printf("%.*s", r - l + 1, s0 + l);
    //扩展号
    switch (x)
    {
    case 1: //小写字母
        printf("%.*s", q - p - 1, az + (p - 'a' + 1));
        break;
    case 2: //大写字母
        printf("%.*s", q - p - 1, AZ + (p - 'A' + 1));
        break;
    case 3: //数字
        printf("%.*s", q - p - 1, num + (p - '0' + 1));
        break;
    }
    l = mid + 1;
    return;
}
