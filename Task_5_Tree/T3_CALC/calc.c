/*************************
*   Title:  calc - Calculator
*   Author: BearHuchao
*   Data:   2019.4.26-5.7
*   Note:   Achieved by Tree
*************************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1024

typedef struct Tree
{
    int data;
    int type; //0 for number, 1 for operator
    struct Tree *left, *right;
} tree;

tree *root;
tree *stack[MAXN];
int top = -1;

tree *Pop();

void Push(tree *src);

void TreeSet(char *s);

void Transform(char *des, const char *src);

int Calc(tree *des);

void Print();

int main()
{
    char src[1024], post[1024];
    memset(src, 0, sizeof(src));
    gets(src);
    Transform(post, src);
    TreeSet(post);
    Print();
    printf("%d", Calc(root));
    return 0;
}

void TreeSet(char *s)
{
    int num = 0;
    tree *p, *q;
    tree *new;

    while (*s)
    {
        switch (*s)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            new = (tree *)malloc(sizeof(tree));
            p = Pop();
            q = Pop();
            new->type = 1;
            new->data = *s;
            new->left = q;
            new->right = p;
            Push(new);
            break;

        default:
            while (isdigit(*s))
            {
                num = num * 10 + *s - '0';
                s++;
            }
            if (num != 0)
            {
                new = (tree *)malloc(sizeof(tree));
                new->type = 0;
                new->data = num;
                new->left = NULL;
                new->right = NULL;
                Push(new);
                num = 0;
                s--;
            }
        }
        s++;
    }
    root = stack[0];
};

tree *Pop()
{
    if (top != -1)
        return stack[top--];
    return NULL;
}

void Push(tree *src)
{
    stack[++top] = src;
}

void Transform(char *des, const char *src)
{
    char OPStack[MAXN];
    int num = 0, OP = -1;
    memset(des, 0, MAXN);
    memset(OPStack, 0, sizeof(OPStack));
    while (*src)
    {
        /********************************
        符号    优先级，大的先算，小的先进栈
        (       0
        + -     1
        * / %   2
        )       3
        ********************************/
        switch (*src)
        {
        case ' ':
            break;

        case '+':
        case '-':
            while ((OPStack[OP] == '+' || OPStack[OP] == '-' || OPStack[OP] == '*' || OPStack[OP] == '/') &&
                   OP != -1)
            {
                sprintf(des + strlen(des), "%c", OPStack[OP--]);
            }
            OPStack[++OP] = *src;
            break;

        case '*':
        case '/':
            while ((OPStack[OP] == '*' || OPStack[OP] == '/') && OP != -1)
            {
                sprintf(des + strlen(des), "%c", OPStack[OP--]);
            }
            OPStack[++OP] = *src;
            break;

        case '(':
            OPStack[++OP] = *src;
            break;

        case ')':
            while (OPStack[OP] != '(')
            {
                sprintf(des + strlen(des), "%c", OPStack[OP--]);
            }
            OP--;
            break;

        default:
            while (isdigit(*src))
            {
                num = num * 10 + *src - '0';
                src++;
            }
            if (num != 0)
            {
                sprintf(des + strlen(des), "%d ", num);
                num = 0;
                src--;
            }
        }
        src++;
    }
    while (OP != -1)
    {
        sprintf(des + strlen(des), "%c", OPStack[OP--]);
    }
}

int Calc(tree *des)
{
    if (des->type == 0)
        return des->data;
    if (des->type == 1)
    {
        switch (des->data)
        {
        case '+':
            return Calc(des->left) + Calc(des->right);

        case '-':
            return Calc(des->left) - Calc(des->right);

        case '*':
            return Calc(des->left) * Calc(des->right);

        case '/':
            return Calc(des->left) / Calc(des->right);

        default:
            return 0;
        }
    }
    return 0;
}

void Print()
{
    tree *tmp;
    tmp = root;
    switch (tmp->type)
    {
    case 0:
        printf("%d ", tmp->data);
        break;
    case 1:
        printf("%c ", tmp->data);
        break;
    }
    tmp = root->left;
    switch (tmp->type)
    {
    case 0:
        printf("%d ", tmp->data);
        break;
    case 1:
        printf("%c ", tmp->data);
        break;
    }
    tmp = root->right;
    switch (tmp->type)
    {
    case 0:
        printf("%d\n", tmp->data);
        break;
    case 1:
        printf("%c\n", tmp->data);
        break;
    }
}