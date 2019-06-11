#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define M 10000019

typedef struct Word
{
    char data[50];
    struct Word *next;
} word;

typedef struct Reference
{
    int index;
    word *list;
} ref;

typedef struct Error
{
    int pos[2001];
    int times;
    char *word;
} err;

ref WordList[M];
err ErrorList[25000];

int ErrCnt;
char *article, *dictionary;
char *pos;
char *WordPos;

unsigned int RSHash(char *str);

void Init(char **des, char *file);

void InitDic();

int GetWord(char *output);

void Check(char *str);

void AddError(char *str);

int cmp(const void *p, const void *q);

int main()
{
    char output[50];
    int i, j;
    Init(&article, "article.txt");
    Init(&dictionary, "dictionary.txt");
    InitDic();
    pos = article;
    while (GetWord(output))
    {
        Check(output);
    }
    qsort(ErrorList, ErrCnt, sizeof(ref), cmp);
    for (i = 0; i < ErrCnt; i++)
    {
        printf("%s %d", ErrorList[i].word, ErrorList[i].times);
        for (j = 0; j < ErrorList[i].times; j++)
            printf("%d ", ErrorList[i].pos[j]);
        puts("");
    }
    return 0;
}

void Init(char **des, char *file)
{
    int fd;
    struct stat sb;
    fd = open(file, O_RDONLY);
    fstat(fd, &sb);
    *des = (char *) mmap(NULL, sb.st_size + 1, (PROT_READ | PROT_WRITE), MAP_PRIVATE, fd, 0);
    (*des)[sb.st_size] = 0;
}

unsigned int RSHash(char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * a + tolower(*str++);
        a *= b;
    }
    return (hash % M);
}

void InitDic()
{
    char delims[] = "\n";
    char *result = NULL;
    word *tmp;
    result = strtok(article, delims);
    while (result != NULL)
    {
        tmp = (word *) malloc(sizeof(word));
        WordList[RSHash(result)].index++;
        strcpy(tmp->data, result);
        tmp->next = WordList[RSHash(result)].list;
        WordList[RSHash(result)].list = tmp;
        result = strtok(NULL, delims);
    }
}

int GetWord(char *output)
{
    while (!isalpha(*(pos++)))
        if (*pos == '\0')
            return 0;
    WordPos = pos;
    do
    {
        *(output++) = tolower(*pos);
    } while (isalpha(*(pos++)));
    *output = '\0';
    return 1;
}

void Check(char *str)
{
    int index = RSHash(str);
    int result;
    word *tmp;
    if (WordList[index].index == 0)
    {
        AddError(str);
        return;
    }
    tmp = WordList[index].list;
    while (tmp != NULL)
    {
        result = strcmp(tmp->data, str);
        if (result == 0)
            return;
        tmp = tmp->next;
    }
    AddError(str);
}

void AddError(char *str)
{
    int i;
    for (i = 0; i < ErrCnt; i++)
    {
        if (*str == *(ErrorList[i].word))
            if (strcmp(str, ErrorList[i].word) == 0)
            {
                ErrorList[i].times++;
                break;
            }
    }
    if (i == ErrCnt)
    {
        ErrorList[ErrCnt].pos[ErrorList[ErrCnt].times++] = WordPos - article;
        ErrorList[ErrCnt].word = (char *) malloc(sizeof(str) + 1);
        strcpy(ErrorList[i].word, str);
        ErrCnt++;
    }
}

int cmp(const void *p, const void *q)
{
    err *a = (err *) p;
    err *b = (err *) q;
    int rt = a->times - b->times;
    if (rt > 0)
        return 1;
    if (rt < 0)
        return -1;
    return strcmp(a->word, b->word);
}