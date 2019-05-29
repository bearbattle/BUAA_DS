/*************************
*   Title:  Sort
*   Author: BearHuchao
*   Data:   2019.5.24-25
*   Note:   Lots of sort method
*************************/

#include <stdio.h>
#include <stdlib.h>

void SelectSort(int a[], int n, int *cnt);

void BubbleSort(int a[], int n, int *cnt);

void HeapSort(int a[], int n, int *cnt);

void Adjust(int a[], int i, int n, int *cnt);

void MergeSort(int a[], int n, int *cnt);

void mSort(int a[], int tmp[], int left, int right, int *cnt);

void merge(int x[], int tmp[], int left, int leftend, int rightend, int *cnt);

void QuickSort(int a[], int left, int right, int *cnt);

void Swap(int *a, int *b);

int main()
{
    int a[100], method, n, cnt = 0;
    scanf("%d%d", &n, &method);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    switch (method)
    {
        case 1:
            SelectSort(a, n, &cnt);
            break;
        case 2:
            BubbleSort(a, n, &cnt);
            break;
        case 3:
            HeapSort(a, n, &cnt);
            break;
        case 4:
            MergeSort(a, n, &cnt);
            break;
        default:
            QuickSort(a, 0, n - 1, &cnt);
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    puts("");
    printf("%d", cnt);
    return 0;
}

void Swap(int *a, int *b)
{
    int t = *b;
    *b = *a;
    *a = t;
}


void SelectSort(int a[], int n, int *cnt)
{
    int i, j, d;
    for (i = 0; i < n - 1; i++)
    {
        d = i;
        for (j = i + 1; j < n; j++)
        {
            (*cnt)++;
            if (a[j] < a[d])
                d = j;
        }
        if (d != i)
            Swap(&a[d], &a[i]);
    }
}

void BubbleSort(int a[], int n, int *cnt)
{
    int i, j, flag = 1;
    i = n;
    while (i > 0 && flag == 1)
    {
        flag = 0;
        for (j = 0; j < i - 1; j++)
        {
            (*cnt)++;
            if (a[j] > a[j + 1])
            {
                Swap(&a[j], &a[j + 1]);
                flag = 1;
            }
        }
        i--;
    }
}

void HeapSort(int a[], int n, int *cnt)
{
    int i;
    for (i = (n - 1) / 2; i >= 0; i--)
        Adjust(a, i, n, cnt);
    for (i = n - 1; i >= 0; i--)
    {
        Swap(&a[i], &a[0]);
        Adjust(a, 0, i, cnt);
    }
}

void Adjust(int a[], int i, int n, int *cnt)
{
    int j, temp;
    temp = a[i];
    j = 2 * i + 1;
    while (j < n)
    {
        if (j < n - 1 && a[j] < a[j + 1])
            j++;
        (*cnt)++;
        if (temp >= a[j])
            break;
        a[(j - 1) / 2] = a[j];
        j = 2 * j + 1;
    }
    a[(j - 1) / 2] = temp;
}

void MergeSort(int k[], int n, int *cnt)
{
    int *tmp;
    tmp = (int *) malloc(sizeof(int) * n);
    if (tmp != NULL)
    {
        mSort(k, tmp, 0, n - 1, cnt);
        free(tmp);
    } else
        printf("No space for tmp array!!!\n");
}

void mSort(int k[], int tmp[], int left, int right, int *cnt)
{
    int center;
    if (left < right)
    {
        center = (left + right) / 2;
        mSort(k, tmp, left, center, cnt);
        mSort(k, tmp, center + 1, right, cnt);
        merge(k, tmp, left, center, right, cnt);
    }
}

void merge(int x[], int tmp[], int left, int leftend, int rightend, int *cnt)
{
    int i = left, j = leftend + 1, q = left;
    while (i <= leftend && j <= rightend)
    {
        (*cnt)++;
        if (x[i] <= x[j])
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
}

void QuickSort(int a[], int left, int right, int *cnt)
{
    int i, last;
    if (left < right)
    {
        last = left;
        for (i = left + 1; i <= right; i++)
        {
            (*cnt)++;
            if (a[i] < a[left])
                Swap(&a[++last], &a[i]);
        }
        Swap(&a[left], &a[last]);
        QuickSort(a, left, last - 1, cnt);
        QuickSort(a, last + 1, right, cnt);
    }
}
