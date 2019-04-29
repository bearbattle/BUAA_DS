#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int neg;        //正负判断，0为正，1为负
char s[110];    //输入
char base[110]; //底数
int ind;      //指数

void Init(char num[]);
int Digit(char num[]);
void Base(char num[]);
void Out(char num[]);

int main()
{
    scanf("%s", s);
    Init(s);
    ind = Digit(s);
    Base(s);
    Out(base);
    return 0;
}

void Init(char num[])
{
    char tmp[110];
    memset(tmp, 0, 110);
    neg = 0;
    if (num[0] == '-')
    {
        neg = 1;
        strcpy(tmp, num + 1);
        strcpy(num, tmp);
        return;
    }
    return;
}

int Digit(char num[]) //e上的指数
{
    char *dot = strstr(num, ".");
    char *flag = num;
    for (;; flag++)
    {
        if ((*flag != '0') && (flag != dot))
            break;
    }
    if (dot - flag > 0)
    {
        return dot - flag - 1;
    }
    return dot - flag;
}

void Base(char num[])
{
    char tmp[110];
    int i;
    int j;
    for (i = 0, j = 0; num[i] != '\0'; i++)
    {
        if (num[i] != '.')
        {
            tmp[j++] = num[i];
        }
    }
    tmp[j] = '\0';
    for (i = 0; tmp[i] == '0'; i++)
        ;
    sprintf(base, "%s", tmp + i);
}

void Out(char num[])
{
    int len = strlen(num);
    if (neg)
        putchar('-');
    if (len == 1)
    {
        printf("%se%d", num, ind);
        return;
    }
    printf("%c.%se%d", num[0], num + 1, ind);
    return;
}