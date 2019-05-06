#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStruct
{
    char word[30];
    int cishu;
    struct MyStruct *ln, *rn;
} node;

struct word
{
    char s[30];
    int n;
    struct word *next;
};

void create(node **root, char *temp);
void middle(node *root);

int main()
{
    struct word *p, *q, *head = NULL, *m;
    int i, j;
    int c;
    char temp[30];
    int temp1;
    FILE *fp;
    fp = fopen("article.txt", "r");
    if (fp == NULL)
        printf("baiabi");
    for (i = 0;; i++)
    {
        q = (struct word *)malloc(sizeof(struct word));
        q->next = NULL;
        memset(q->s, '\0', 30);
        q->n = 1;

        //get the word

        for (j = 0;; j++)
        {
            c = fgetc(fp);
            if (c >= 'A' && c <= 'Z')
                c = towlower(c);
            if (feof(fp))
            {
                break;
            }

            if (c < 'a' || c > 'z')
                continue;
            else
                break;

        } //this step is used to find the first "char" which is zifu

        for (j = 0;; j++)
        {

            q->s[j] = c;
            c = fgetc(fp);
            if (isalpha(c))
            {
                c = towlower(c);
            }
            else
                break;
            if (feof(fp))
                break;
        } //put the word into the link;
        if (head == NULL)
            head = p = q;
        else
            p->next = q;
        p = q;
        if (feof(fp))
            break;
    } //getword into lianbiao;
    node *root = NULL;
    node *kk;
    for (p = head; p != NULL; p = p->next)
    {
        create(&root, p->s);
    }
    if (root != NULL && root->rn != NULL && root->rn->rn != NULL)
        printf("%s %s %s\n", root->word, root->rn->word, root->rn->rn->word);
    else
    {
        kk = root;

        while (kk->rn != NULL && kk != NULL)
        {
            printf("%s ", kk->word);
            kk = kk->rn;
        }
        printf("%s\n", kk->word);
    }

    for (p = head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (strcmp(q->s, p->s) == 0 && q != p)
            {
                p->n++;
                m = head;
                while (m->next != q)
                    m = m->next;
                m->next = q->next;
                free(q);
                q = m;
            }
        }
    }

    for (p = head; p != NULL; p = p->next)
    {
        m = p;
        strncpy(m->s, p->s, 30);
        for (q = p->next; q != NULL; q = q->next)
        {
            if (strcmp(m->s, q->s) > 0)
            {
                strncpy(temp, m->s, 30);
                strncpy(m->s, q->s, 30);
                strncpy(q->s, temp, 30);
                temp1 = m->n;
                m->n = q->n;
                q->n = temp1;
            }
        }
    }
    for (p = head; p->next != NULL; p = p->next)
    {
        printf("%s %d\n", p->s, p->n);
    }
    // middle(root);
    fclose(fp);
    getchar();
    getchar();
    return 0;
}

void create(node **root, char *temp)
{
    node *q;
    if ((*root) == NULL)
    {
        q = (node *)malloc(sizeof(node));
        q->ln = NULL;
        q->rn = NULL;
        q->cishu = 1;
        *root = q;
        memset((*root)->word, '\0', 30);
        strcpy((*root)->word, temp);
        return;
    }
    else
    {
        if (strcmp((*root)->word, temp) == 0)
        {
            (*root)->cishu++;
            return;
        }
        if (strcmp((*root)->word, temp) > 0)
        {
            create(&((*root)->ln), temp);
        }
        if (strcmp((*root)->word, temp) < 0)
        {
            create(&((*root)->rn), temp);
        }
    }
}

void middle(node *root)
{
    if (root == NULL)
        return;
    else
    {
        middle(root->ln);
        if (root->word[0] != '\0' && root->word[0] != -1)
            printf("%s %d\n", root->word, root->cishu);
        middle(root->rn);
    }
}
