#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct Node
{
    char name[25];
    int val;
} node;

node def[50], udef[50];
int Def_Cnt = 0, uDef_Cnt = 0;
char pre[300], s[300];
char *pos;

int GetName(char *name);
int GetVal(int *val);

int main()
{
    int i = 0;
    char t_name[25];
    int t_val;
    gets(s);
    for (pos = s; *pos != 0; pos++)
    {
        if (!isspace(*pos))
        {
            s[i++] = *pos;
        }
    }
    s[i] = 0;
    pos = strstr(s, "int") + 3;
    while (GetName(t_name))
    {
        if (GetVal(&t_val))
        {
            strcpy(def[Def_Cnt].name, t_name);
            def[Def_Cnt].val = t_val;
            Def_Cnt++;
        }
        else
        {
            strcpy(udef[uDef_Cnt].name, t_name);
            udef[uDef_Cnt].val = t_val;
            uDef_Cnt++;
        }
    }
    for (i = 0; i < Def_Cnt; i++)
    {
        printf("%s %d\n", def[i].name, def[i].val);
    }
    for (i = 0; i < uDef_Cnt; i++)
    {
        printf("%s %c\n", udef[i].name, udef[i].val);
    }
    return 0;
}

int GetName(char *name)
{
    int i = 0;
    if (*pos == ';'||*pos=='\0')
        return 0;
    while (*pos != ',' && *pos != '=' && *pos != ';')
    {
        name[i++] = *pos;
        pos++;
    }
    name[i] = 0;
    return 1;
}

int GetVal(int *val)
{
    int num = 0;
    if (*pos == ',' || *pos == ';')
    {
        *val = 'N';
        pos++;
        return 0;
    }
    if (*pos == '=')
    {
        pos++;
    }
    while (isdigit(*pos))
    {
        num = num * 10 + *pos - '0';
        pos++;
    }
    *val = num;
    pos++;
    return 1;
}