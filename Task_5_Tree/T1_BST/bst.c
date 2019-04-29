/*************************
*   Title:  bst
*   Author: BearHuchao
*   Data:   2019.4.26-
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree
{
    struct Tree *left, *right;
    int data;
} tree;

tree *root = NULL;

tree *Add(tree *des, int val);
void Dfs(tree *des, int layer);
//int LayerGet(tree *dest);

int main()
{
    int n;
    scanf("%d", &n);
    while (scanf("%d", &n) != EOF)
    {
        Add(root, n);
    }
    Dfs(root, 1);
    return 0;
}

tree *Add(tree *des, int val)
{
    if (root == NULL)
    {
        root = (tree *)malloc(sizeof(tree));
        root->data = val;
        root->left = NULL;
        root->right = NULL;
        return NULL;
    }
    if (des == NULL)
    {
        des = (tree *)malloc(sizeof(tree));
        des->data = val;
        des->left = NULL;
        des->right = NULL;
        return des;
    }
    else
    {
        if (val < des->data)
            des->left = Add(des->left, val);
        else
            des->right = Add(des->right, val);
    }
    return des;
}

void Dfs(tree *des, int layer)
{
    if (des->left == NULL && des->right == NULL)
    {
        printf("%d %d\n", des->data, layer);
        return;
    }
    if (des->left != NULL)
    {
        Dfs(des->left, layer + 1);
    }
    if (des->right != NULL)
    {
        Dfs(des->right, layer + 1);
    }
    return;
}

// int LayerGet(tree *dest)
// {
//     tree *queue[2000];
//     int head = 0, tail = 0;
//     queue[tail++] = &root;
//     while (tail != head)
//     {
//         if (queue[head]->left != NULL)
//         {
//             queue[tail] = queue[head]->left;
//             queue[tail]->layer = queue[head]->layer + 1;
//         }

//         if (queue[head]->left != NULL)
//         {
//             queue[tail] = queue[head]->left;
//             queue[tail]->layer = queue[head]->layer + 1;
//         }

//     }
// }