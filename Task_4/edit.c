#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word
{
    int opt;
    int pos;
    char *str;
} word;

word stack[200];
int OpCnt = -1;

void Insert(char *src, int pos, char *str);
void Delete(char *src, int pos, char *str);

int main()
{
    int n, opt, cnt;
    int i;
    char line[600];
    gets(line);
    scanf("%d", &n);
    stack[0].opt = 0;
    OpCnt = n;
    for (i = 1; i <= n; i++)
    {
        stack[i].str = (char *)malloc(600);
        scanf("%d%d%s", &stack[i].opt, &stack[i].pos, stack[i].str);
    }
    scanf("%d", &opt);
    while (opt != -1)
    {
        switch (opt)
        {
        case 1:
            OpCnt++;
            stack[OpCnt].opt = opt;
            stack[OpCnt].str = (char *)malloc(600);
            scanf("%d%s", &stack[OpCnt].pos, stack[OpCnt].str);
            Insert(line, stack[OpCnt].pos, stack[OpCnt].str);
            break;
        case 2:
            OpCnt++;
            stack[OpCnt].opt = opt;
            stack[OpCnt].str = (char *)malloc(600);
            scanf("%d%d", &stack[OpCnt].pos, &cnt);
            if (stack[OpCnt].pos + cnt > strlen(line))
            {
                strcpy(stack[OpCnt].str, line + stack[OpCnt].pos);
            }
            else
            {
                strncpy(stack[OpCnt].str, line + stack[OpCnt].pos, cnt);
                *(stack[OpCnt].str + cnt) = '\0';
            }
            Delete(line, stack[OpCnt].pos, stack[OpCnt].str);
            break;
        case 3:
            switch (stack[OpCnt].opt)
            {
            case 0:
                break;
            case 1:
                Delete(line, stack[OpCnt].pos, stack[OpCnt].str);
                OpCnt--;
                break;
            case 2:
                Insert(line, stack[OpCnt].pos, stack[OpCnt].str);
                OpCnt--;
                break;
            }
            break;
        }
        scanf("%d", &opt);
    }
    puts(line);
    return 0;
}

void Insert(char *src, int pos, char *str)
{
    char *p, q[600];
    if (pos == 0)
    {
        strcpy(q, str);
        strcat(q, src);
        strcpy(src, q);
        return;
    }
    p = src + pos;
    strcpy(q, p);
    *p = 0;
    strcat(src, str);
    strcat(src, q);
    return;
}

void Delete(char *src, int pos, char *str)
{
    char *p, q[600];
    if (pos == 0)
    {
        strcpy(q, src + strlen(str));
        strcpy(src, q);
        return;
    }
    p = src + pos;
    strcpy(q, p + strlen(str));
    *p = 0;
    strcat(src, q);
    return;
}
