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
int used[110];
int n;

void Init();
void CheckLeak();
void CheckRepeat();
void Out();
int cmp(const void *p, const void *q);
int outcmp(const void *p, const void *q);

int main()
{
    Init();
    CheckLeak();
    CheckRepeat();
    Out();
    return 0;
}

void Init()
{
    int i;
    FILE *IN;
    scanf("%d", &n);
    IN = fopen("in.txt", "r");
    for (i = 0; i < n; i++)
    {
        fscanf(IN, "%d%s%d", &list[i].num, list[i].name, &list[i].seat);
        used[list[i].seat] = 1;
    }
    qsort(list, n, sizeof(list[0]), cmp);
}

void CheckLeak()
{
    int i, j = n;
    int q = n < list[n - 1].seat ? n : list[n - 1].seat;
    for (i = 1; i <= q; i++)
    {
        if (!used[i])
        {
            list[--j].seat = i;
            q = list[j - 1].seat < q ? list[j - 1].seat : q;
        }
    }
    qsort(list, n, sizeof(list[0]), cmp);
}

void CheckRepeat()
{
    int i;
    int m = list[n - 1].seat;
    memset(used, 0, sizeof(used));
    for (i = 0; i < n; i++)
    {
        if (!used[list[i].seat])
        {
            used[list[i].seat] = 1;
        }
        else
        {
            list[i].seat = ++m;
        }
    }
    qsort(list, n, sizeof(list[0]), outcmp);
}

void Out()
{
    int i;
    FILE *OUT;
    OUT = fopen("out.txt", "w");
    for (i = 0; i < n; i++)
        fprintf(OUT, "%d %s %d\n", list[i].num, list[i].name, list[i].seat);
}

int cmp(const void *p, const void *q)
{
    student a, b;
    a = *(student *)p;
    b = *(student *)q;
    if (a.seat != b.seat)
    {
        return a.seat > b.seat ? 1 : -1;
    }
    return a.num > b.num ? 1 : -1;
}

int outcmp(const void *p, const void *q)
{
    student a, b;
    a = *(student *)p;
    b = *(student *)q;
    return a.num > b.num ? 1 : -1;
}