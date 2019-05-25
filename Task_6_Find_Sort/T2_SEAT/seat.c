/*************************
*   Title:  Seat
*   Author: BearHuchao
*   Data:   2019.5.24-25
*   Note:   Seat Arrange
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    int num;
    char name[25];
    int seat;
} student;

student list[110];

void Init();
int cmp(const void *p, const void *q);

int main()
{
    Init();
}

void Init()
{
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%s%d", &list[i].num, list[i].name, &list[i].seat);
    }
}

int cmp(const void *p, const void *q)
{
    student a, b;
    a = *(student *)p;
    b = *(student *)q;
    if (a.seat != b.seat)
    {
        return a.seat > b.seat ? a.seat : b.seat;
    }
    return a.num > b.num ? a.num : b.num;
}