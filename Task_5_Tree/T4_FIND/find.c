/*************************
*   Title:  Family - LCA (Last Common Ancester)
*   Author: BearHuchao
*   Data:   2019.5.13
*   Note:   A Possible Way to Find LCA
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO "NULL"

typedef struct Tree
{
    char name[30];
    int layer;
    struct Tree *left, *right, *father;
} tree;

tree *root;
FILE *IN;

void Init();

void AddSon(tree *des);

void Dfs(const char *des, tree *now);

tree *dfs;

tree *LCA(tree *p, tree *q);

int main()
{
    char desA[30], desB[30];
    tree *p1, *p2, *lca;
    Init();
    scanf("%s%s", desA, desB);
    Dfs(desA, root);
    p1 = dfs;
    Dfs(desB, root);
    p2 = dfs;
    if (p1->layer != p2->layer)
    {
        if (p1->layer < p2->layer)
            printf("%s %s %d", p2->name, p1->name, p2->layer - p1->layer);
        if (p1->layer > p2->layer)
            printf("%s %s %d", p1->name, p2->name, p1->layer - p2->layer);
    } else
    {
        lca = LCA(p1, p2);
        printf("%s %s %d\n", lca->name, p1->name, p1->layer - lca->layer);
        printf("%s %s %d\n", lca->name, p2->name, p2->layer - lca->layer);
    }
    return 0;
}

void Init()
{
    int n;
    char name[30];

    IN = fopen("in.txt", "r");
    root = (tree *) malloc(sizeof(tree));
    root->layer = 0;
    fscanf(IN, "%d", &n);
    fscanf(IN, "%s", root->name);
    root->layer = 0;
    root->father = root;
    AddSon(root);
    while (--n)
    {
        fscanf(IN, "%s", name);
        Dfs(name, root);
        AddSon(dfs);
    }
}

void AddSon(tree *des)
{
    char lname[30], rname[30];
    tree *lt, *rt;

    fscanf(IN, "%s%s", lname, rname);
    if (strcmp(lname, NO) != 0)
    {
        lt = (tree *) malloc(sizeof(tree));
        lt->layer = des->layer + 1;
        strcpy(lt->name, lname);
        lt->father = des;
        lt->left = NULL;
        lt->right = NULL;
        des->left = lt;
    } else
    {
        des->left = NULL;
    }
    if (strcmp(rname, NO) != 0)
    {
        rt = (tree *) malloc(sizeof(tree));
        rt->layer = des->layer + 1;
        strcpy(rt->name, rname);
        rt->father = des;
        rt->left = NULL;
        rt->right = NULL;
        des->right = rt;
    } else
    {
        des->right = NULL;
    }
}

void Dfs(const char *des, tree *now)
{
    if (now == root)
        dfs = NULL;
    if (dfs != NULL)
        return;
    if (now == NULL)
        return;
    if (strcmp(des, now->name) == 0)
    {
        dfs = now;
        return;
    }
    Dfs(des, now->left);
    Dfs(des, now->right);
}

tree *LCA(tree *p, tree *q)
{
    if (p->father == q->father)
    {
        return p->father;
    }
    return LCA(p->father, q->father);
}
