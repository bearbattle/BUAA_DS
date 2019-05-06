#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree
{
    struct Tree *left, *right;
    int data, type; //type:0 for num; 1 for operator
} tree;

tree *stack[1024];

void Build();

int main()
{
    Build();
}

void Build()
{
    char Buf[1024];
    char *s;
    int num;
    fgets(Buf, 1000, stdin);
    for (s = Buf;; s++)
    {
        if (isdigit(*s))
        {
            num = num * 10 + *s - '0';
            continue;
        }
        if (num != 0)
        {
            NUMStack[++NUM] = num;
        }
        num = 0;
        Check(*s);
        if (*s == '\0')
            break;
    }
}