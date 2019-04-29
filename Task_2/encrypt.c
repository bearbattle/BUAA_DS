#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitKey(char *s);

int main()
{
    char key[60];
    char str[1010];
    int i;
    FILE *IN;
    FILE *OUT;
    IN = fopen("encrypt.txt", "r");
    OUT = fopen("output.txt", "w");
    fgets(key, 51, stdin);
    InitKey(key);
    while(fgets(str,1000,IN)!=NULL)
    {
        for (i = 0; str[i] != '\0';i++)
        {
            if(islower(str[i]))
                str[i] = key[str[i] - 'a'];
        }
        fprintf(OUT, "%s", str);
    }
    fclose(IN);
    fclose(OUT);
    return 0;
}

void InitKey(char *s)
{
    short used[26];
    int i = 0, j = 0;
    char *c;
    memset(used, 0, sizeof(used));
    for (c = s; *c != '\0'; c++)
    {
        if (islower(*c))
        {
            if (!used[*c - 'a'])
            {
                s[i++] = *c;
                used[*c - 'a'] = 1;
            }
        }
    }
    for (j = 25; j >= 0; j--)
    {
        if (!used[j])
        {
            s[i++] = j + 'a';
        }
    }
    s[i] = '\0';
    return;
}