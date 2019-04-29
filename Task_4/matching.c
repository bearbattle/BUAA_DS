#include <stdio.h>
#include <string.h>
#define MAX 300

char stack[MAX], stack1[MAX];
int cline[MAX], cline1[MAX];
int top, top1;

FILE *IN;

void InitStack();
int IsEmpty();
int IsFull();
void Push(char c, int x);
void Push1(char c, int x)
{
    ++top1;
    stack1[top1] = c;
    cline1[top1] = x;
}
char Pop();
int Check(char c);

int main()
{
    int line = 0;
    char s[210], *p;
    int flag = 0;
    InitStack();
    IN = fopen("example.c", "r");
    while (fgets(s, 205, IN) != NULL)
    {
        line++;
        for (p = s; *p != '\0'; p++)
        {
            if (flag)
            {
                while (*p != '*' && *p != '\0')
                    p++;
                if (*p == '*' && *(p + 1) == '/')
                    flag = 0;
            }
            else
            {
                switch (*p)
                {
                case '{':
                    if (stack[top] == '(')
                    {
                        printf("without maching \'(\' at line %d", cline[top]);
                        return 0;
                    }
                case '(':
                    Push(*p, line);
                    Push1(*p, line);
                    break;
                case ')':
                case '}':
                    Push1(*p, line);
                    if (!Check(*p))
                    {
                        printf("without maching \'%c\' at line %d", *p, line);
                        return 0;
                    }
                    break;
                case '\'':
                    p++;
                    while (*p != '\'')
                        p++;
                    break;
                case '\"':
                    p++;
                    while (*p != '\"')
                        p++;
                    break;
                case '/':
                    if (*(p + 1) == '/')
                    {
                        while (*p != '\0')
                            p++;
                        break;
                    }
                    if (*(p + 1) == '*')
                    {
                        flag = 1;
                        p += 2;
                        while (*p != '*' && *p != '\0')
                            p++;
                        if (*p == '*' && *(p + 1) == '/')
                            flag = 0;
                        break;
                    }
                    break;
                }
                if (*p == '\0')
                    break;
            }
        }
    }
    fclose(IN);
    if (!IsEmpty())
    {
        printf("without maching \'%c\' at line %d", stack[top], cline[top]);
        return 0;
    }
    puts(stack1);
    return 0;
}

void InitStack()
{
    top = -1;
    top1 = -1;
}

int IsEmpty()
{
    return top == -1;
}

int IsFull()
{
    return top == (MAX - 1);
}

void Push(char c, int x)
{
    ++top;
    stack[top] = c;
    cline[top] = x;
}

char Pop()
{
    if (IsEmpty())
        return -1;
    return stack[top--];
}

int Check(char c)
{
    switch (c)
    {
    case ')':
        if (stack[top] == '(')
        {
            Pop();
            return 1;
        }
        break;
    case '}':
        if (stack[top] == '{')
        {
            Pop();
            return 1;
        }
        break;
    }
    return 0;
}