#include <ctype.h>
#include <stdio.h>

char OPstack[100];
int NUMStack[100];     //计算符栈和数字栈
int OP = -1, NUM = -1; //初始化

void Calc();         //计算
void Check(char op); //检查计算优先级

int main()
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
    while (OP != -1)
    {
        Calc();
    }
    printf("%d", NUMStack[0]);
    return 0;
}

void Calc()
{
    char op = OPstack[OP--];
    int p, q;
    p = NUMStack[NUM--];
    q = NUMStack[NUM--];
    //这个地方需要注意，对两个数进行操作的时候，两个数的顺序，后面的数其实应该在前面
    switch (op)
    {
    case '+':
        NUMStack[++NUM] = q + p;
        break;
    case '-':
        NUMStack[++NUM] = q - p;
        break;
    case '*':
        NUMStack[++NUM] = q * p;
        break;
    case '/':
        NUMStack[++NUM] = q / p;
        break;
    case '%':
        NUMStack[++NUM] = q % p;
        break;
    }
}

void Check(char op) //优先级检查与计算
{
    /********************************
    符号    优先级，大的先算，小的先进栈
    (       0
    + -     1
    * / %   2
    )       3
    ********************************/

    switch (op)
    {
    case '(':
        if (OP == -1)
        {
            OPstack[++OP] = op;
            return;
        }
        OPstack[++OP] = op;
        return;
        break;
    case '+':
    case '-':
        if (OP == -1)
        {
            OPstack[++OP] = op;
            return;
        }
        while (OPstack[OP] == '+' || OPstack[OP] == '-' || OPstack[OP] == '*' || OPstack[OP] == '/' || OPstack[OP] == '%')
        {
            Calc();
        }
        OPstack[++OP] = op;
        return;
        break;
    case '*':
    case '/':
    case '%':
        if (OP == -1)
        {
            OPstack[++OP] = op;
            return;
        }
        while (OPstack[OP] == '*' || OPstack[OP] == '/' || OPstack[OP] == '%')
        {
            Calc();
        }
        OPstack[++OP] = op;
        return;
        break;
    case ')':
        if (OP == -1)
        {
            OPstack[++OP] = op;
            return;
        }
        while (OPstack[OP] != '(')
        {
            Calc();
        }
        OP--;
        break;
    }
}