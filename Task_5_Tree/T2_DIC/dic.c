/*************************
*   Title:  dic - Dictionary
*   Author: BearHuchao
*   Data:   2019.4.26-
*************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree
{
    struct Tree *left, *right;
    int time;
    char *data;
} tree;

tree *root = NULL;
FILE *IN;
char *pos;

tree *Add(tree *des, char *data);
int GetWord(char *word);
void Dfs_M(tree *des);

int main()
{
    char word[50];
    IN = fopen("article.txt", "r");
    while (GetWord(word) != EOF)
    {
        Add(root, word);
    }
    printf("%s", root->data);
    if (root->right != NULL)
    {
        printf(" %s", root->right->data);
        if (root->right->right != NULL)
        {
            printf(" %s", root->right->right->data);
        }
    }
    puts("");
    Dfs_M(root);
    return 0;
}

int GetWord(char *word)
{
    char c;
    while (!isalpha(c = fgetc(IN)))
        if (c == EOF)
            return c;
    do
    {
        *(word++) = tolower(c);
    } while (isalpha(c = fgetc(IN)));
    *word = '\0';
    return 1;
}

tree *Add(tree *des, char *data)
{
    if (root == NULL)
    {
        root = (tree *)malloc(sizeof(tree));
        root->data = (char *)malloc(50);
        strcpy(root->data, data);
        root->left = NULL;
        root->right = NULL;
        root->time = 1;
        return root;
    }
    if (des == NULL)
    {
        des = (tree *)malloc(sizeof(tree));
        des->data = (char *)malloc(50);
        strcpy(des->data, data);
        des->left = NULL;
        des->right = NULL;
        des->time = 1;
        return des;
    }
    else
    {
        if (strcmp(des->data, data) > 0)
            des->left = Add(des->left, data);
        if (strcmp(des->data, data) < 0)
            des->right = Add(des->right, data);
        if (strcmp(des->data, data) == 0)
            des->time++;
    }
    return des;
}

void Dfs_M(tree *des)
{
    if (des->left != NULL)
        Dfs_M(des->left);
    printf("%s %d\n", des->data, des->time);
    if (des->right != NULL)
        Dfs_M(des->right);
}