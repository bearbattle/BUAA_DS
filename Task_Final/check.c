#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define M 10000019

typedef struct Word {
    char data[50];
    struct word *next;
} word;

typedef struct Reference {
    int index;
    word *list;
} ref;

ref WordList[M];

unsigned int RSHash(char *str);

char *article, *dictionary;

void Init(char **des, char *file);

void Split(char *str, char *delim);

void Split(char *str, char *delim) {
    char *result = NULL;
    result = strtok(str, delim);
    while (result != NULL) {
        printf("result is \"%s\"\n", result);
        result = strtok(NULL, delim);
    }
}

int main() {
    Init(&article, "article.txt");
    Init(&dictionary, "dictionary.txt");
    Split(article, " ");
    return 0;
}

void Init(char **des, char *file) {
    int fd;
    struct stat sb;
    fd = open(file, O_RDONLY);
    fstat(fd, &sb);
    *des = (char *) mmap(NULL, sb.st_size + 1, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    (*des)[sb.st_size] = 0;
    printf("%s", *des);
}

unsigned int RSHash(char *str) {
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    while (*str) {
        hash = hash * a + (*str++);
        a *= b;
    }
    return (hash % M);
}