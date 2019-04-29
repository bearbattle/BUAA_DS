#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char A[100], B[100];

void Init(char big[]);
void Sub(char a[], char b[]);
void Out(char big[]);

int main()
{
    int flag;
    scanf("%s", A);
    scanf("%s", B);
    Init(A);
    Init(B);
    flag = strcmp(A, B);
    if (flag == 0)
    {
        printf("0");
    }
    if (flag > 0)
    {
        Sub(A, B);
        Out(A);
        printf("%s", A);
    }
    if (flag < 0)
    {
        Sub(B, A);
        Out(B);
        printf("-%s", B);
    }
    return 0;
}

void Init(char big[])
{
    int len = strlen(big);
    char tmp[100];
    memset(tmp, 0, 100);
    memset(tmp, '0', 99);
    strcpy(tmp, big);
    memset(big, '0', 99);
    strncpy(big + 99 - len, tmp, len);
    return;
}

void Sub(char a[], char b[])
{
    int i;
    for (i = 98; i >= 0; i--)
    {
        a[i] = a[i] - b[i] + '0';
    }
    for (i = 98; i >= 0; i--)
    {
        if (a[i] < '0')
        {
            a[i] += 10;
            a[i - 1]--;
        };
    }
}

void Out(char big[])
{
    char *c;
    char tmp[100];
    memset(tmp, 0, sizeof(tmp));
    for (c = big; *c == '0'; c++)
        ;
    strcpy(tmp, c);
    strcpy(big, tmp);
    return;
}