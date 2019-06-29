#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define M 16777216

typedef struct Word
{
    char *data;
    struct Word *next;
} word;

typedef struct Reference
{
    int index;
    word *list;
} ref;

typedef struct Error
{
    int pos[3001];
    int times;
    char *word;
} err;

ref WordList[M];
err ErrorList[25000];
char BufferOut[500000];
char *BufferPtr;

int ErrCnt;
char *article, *dictionary;
char *pos;
char *WordPos;

unsigned int RSHash(char *str);

void Init(char **des, char *file);

void InitDic();

int GetWord(char **output);

void Check(char *str);

void AddError(char *str);

int cmp(const void *p, const void *q);

void PrintInt(int x);

void Output();

int main()
{
    char *output;
    Init(&article, "article.txt");
    Init(&dictionary, "dictionary.txt");
    pos = dictionary;
    InitDic();
    pos = article;
    while (GetWord(&output))
    {
        //puts(output);
        Check(output);
    }
    qsort(ErrorList, ErrCnt, sizeof(err), cmp);
    Output();
    //fclose(OUT);
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
    size_t len = strlen(str);
    u_int32_t h = 97;
    if (len > 3)
    {
        const u_int32_t *key_x4 = (const u_int32_t *) str;
        size_t i = len >> 2;
        do
        {
            u_int32_t k = *key_x4++;
            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
            h = (h << 13) | (h >> 19);
            h = h * 5 + 0xe6546b64;
        } while (--i);
        str = (const u_int8_t *) key_x4;
    }
    if (len & 3)
    {
        size_t i = len & 3;
        u_int32_t k = 0;
        do
        {
            k <<= 8;
            k |= str[i - 1];
        } while (--i);
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
    }
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return (h & (unsigned int) (M - 1));
}

void InitDic()
{
    word *tmp;
    char *out;
    int hash;
    while (GetWord(&out))
    {
        hash = RSHash(out);
        tmp = (word *) malloc(sizeof(word));
        WordList[hash].index++;
        tmp->data = out;
        tmp->next = WordList[hash].list;
        WordList[hash].list = tmp;
    }
}

int GetWord(char **output)
{
    while (!isalpha(*pos))
    {
        if (*pos == '\0')
            return 0;
        pos++;
    }
    WordPos = pos;
    do
    {
        *pos = tolower(*pos);
        pos++;
    } while (isalpha(*pos));
    *pos = '\0';
    *output = WordPos;
    pos++;
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
            if (strlen(str) == strlen(ErrorList[i].word))
                if (strcmp(str, ErrorList[i].word) == 0)
                {
                    ErrorList[i].pos[ErrorList[i].times] = WordPos - article;
                    ErrorList[i].times++;
                    break;
                }
    }
    if (i == ErrCnt)
    {
        ErrorList[ErrCnt].pos[0] = WordPos - article;
        ErrorList[ErrCnt].times++;
        ErrorList[ErrCnt].word = (char *) malloc(strlen(str) + 1);
        strcpy(ErrorList[i].word, str);
        ErrCnt++;
    }
}

int cmp(const void *p, const void *q)
{
    err *a = (err *) p;
    err *b = (err *) q;
    int rt = b->times - a->times;
    if (rt > 0)
        return 1;
    if (rt < 0)
        return -1;
    return strcmp(a->word, b->word);
}

void Output()
{
    FILE *OUT;
    int i, j;
    OUT = fopen("misspelling.txt", "wb");
    BufferPtr = BufferOut;
    for (i = 0; i < ErrCnt; i++)
    {
        strcpy(BufferPtr, ErrorList[i].word);
        BufferPtr += strlen(ErrorList[i].word);
        *(BufferPtr++) = ' ';
        PrintInt(ErrorList[i].times);
        for (j = 0; j < ErrorList[i].times; j++)
            PrintInt(ErrorList[i].pos[j]);
        *(BufferPtr++) = '\n';
    }
    fwrite(BufferOut, BufferPtr - BufferOut, 1, OUT);
}

void PrintInt(int x)
{
    char num[20];
    int i, cnt = 0;
    while (x != 0)
    {
        num[cnt++] = x % 10 + '0';
        x /= 10;
    }
    for (i = cnt - 1; i >= 0; i--)
    {
        *(BufferPtr++) = num[i];
    }
    *(BufferPtr++) = ' ';
}