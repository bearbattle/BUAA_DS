#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char strIN[1010], strin[1010];        //strIN:原始输入; strin:小写转化
char strA[100], stra[100], strb[100]; //strA:原始输入; stra:小写转化; strb:替换字符串
char *now;                            //当前位置
FILE *OUT;

void MidReplace(char *s);
void Lower(char *des, char *source);

int main()
{
    char *c;
    FILE *IN;
    IN = fopen("filein.txt", "r+");
    OUT = fopen("fileout.txt", "w");
    gets(strA);
    gets(strb);
    Lower(stra, strA);
    while (fgets(strIN, 1000, IN) != NULL)
    {
        Lower(strin, strIN);
        now = strin;
        while ((c = strstr(now, stra)) != NULL)
        {
            now = strIN + (c - strin);
            MidReplace(now);          //中部替换
            now = now + strlen(strb); //位置更新
            Lower(strin, strIN);      //string更新
            now = strin + (now - strIN);
        }
        fputs(strIN, OUT);
    }
    fclose(IN);
    fclose(OUT);
    return 0;
}

void Lower(char *des, char *source) //字符串转小写
{
    char *c;
    int i = 0;
    for (c = source; *c != '\0'; c++)
    {
        des[i++] = tolower(*c);
    }
    des[i] = '\0';
    return;
}

void MidReplace(char *s)
{
    char tmp[1010];
    strcpy(tmp, strIN);
    tmp[now - strIN] = '\0';
    strcat(tmp, strb);
    strcat(tmp, now + strlen(strA));
    strcpy(strIN, tmp);
    return;
}
