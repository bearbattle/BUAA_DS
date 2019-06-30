#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x7FFFFFFF

typedef struct Edge
{
    int end;
    int weight;
    int line;
    struct Edge *next;
} edge;

typedef struct Node
{
    char Name[50];
    int flag;
    edge *from;
    edge *list;
} node;

node map[501];
int path[501][501];
int destination;
int CountOfStation = 0;

void Init();

void Dijkstra();

int main()
{
    int i;
    char beg[50], end[50];
    Init();
    scanf("%s", beg);
    scanf("%s", end);
    Dijkstra(beg, end);
    for (i = 0; path[destination][i] != -1; i++)
    {
        printf("%s ", map[path[destination][i]].Name);
    }
    return 0;
}

void Init()
{
    FILE *IN;
    int SumOfLine, line[13];
    int SumOfStation[13];
    node Line[13][50];
    int i, j, k;
    int des;
    edge *tmp;
    IN = fopen("bgstations.txt", "r");
    fscanf(IN, "%d", &SumOfLine);

    for (i = 0; i < SumOfLine; i++)
    {
        fscanf(IN, "%d%d", &line[i], &SumOfStation[i]);
        for (j = 0; j < SumOfStation[i]; j++)
        {
            fscanf(IN, "%s%d", Line[i][j].Name, &(Line[i][j].flag));
        }
        for (j = 0; j < SumOfStation[i]; j++) //Set the map of stations
        {
            if (Line[i][j].flag)
            {
                for (k = 0; k < CountOfStation; k++)
                {
                    if (strcmp(Line[i][0].Name, map[k].Name) == 0)
                    {
                        continue;
                    }
                }
            }
            strcpy(map[CountOfStation].Name, Line[i][j].Name);
            map[CountOfStation].flag = Line[i][j].flag;
            CountOfStation++;
        }
    }
    for (i = 0; i < SumOfLine; i++)
    {
        //Deal with the first station
        tmp = (edge *)malloc(sizeof(edge));
        tmp->next = NULL;
        tmp->line = line[i];
        tmp->weight = 1;
        for (k = 0; k < CountOfStation; k++)
        {
            if (strcmp(Line[i][1].Name, map[k].Name) == 0)
            {
                tmp->end = k;
                break;
            }
        }
        for (k = 0; k < CountOfStation; k++)
        {
            if (strcmp(Line[i][0].Name, map[k].Name) == 0)
            {
                des = k;
                break;
            }
        }
        tmp->next = map[des].list;
        map[des].list = tmp;
        //Deal with mid stations
        for (j = 1; j < SumOfStation[i] - 1; j++)
        {
            for (k = 0; k < CountOfStation; k++)
            {
                if (strcmp(Line[i][j].Name, map[k].Name) == 0)
                {
                    des = k;
                    break;
                }
            }

            tmp = (edge *)malloc(sizeof(edge));
            tmp->line = line[i];
            tmp->weight = 1;
            for (k = 0; k < CountOfStation; k++)
            {
                if (strcmp(Line[i][j - 1].Name, map[k].Name) == 0)
                {
                    tmp->end = k;
                    break;
                }
            }
            tmp->next = map[des].list;
            map[des].list = tmp;

            tmp = (edge *)malloc(sizeof(edge));
            tmp->line = line[i];
            tmp->weight = 1;
            for (k = 0; k < CountOfStation; k++)
            {
                if (strcmp(Line[i][j + 1].Name, map[k].Name) == 0)
                {
                    tmp->end = k;
                    break;
                }
            }
            tmp->next = map[des].list;
            map[des].list = tmp;
        }
        for (k = 0; k < CountOfStation; k++)
        {
            if (strcmp(Line[i][SumOfStation[i] - 1].Name, map[k].Name) == 0)
            {
                des = k;
                break;
            }
        }
        tmp = (edge *)malloc(sizeof(edge));
        tmp->line = line[i];
        tmp->weight = 1;
        for (k = 0; k < CountOfStation; k++)
        {
            if (strcmp(Line[i][SumOfStation[i] - 1].Name, map[k].Name) == 0)
            {
                tmp->end = k;
                break;
            }
        }
        tmp->next = map[des].list;
        map[des].list = tmp;
    }
}

void Dijkstra(char *Start, char *Des)
{
    int flag[CountOfStation];
    int dis[CountOfStation];
    int mid;
    int i, j;
    int pos[CountOfStation];
    int lowcost;
    int beg = -1, end = -1;
    edge *tmp;
    for (i = 0; i < CountOfStation; i++)
    {
        if (strcmp(Start, map[i].Name) == 0)
        {
            beg = i;
        }
        if (strcmp(Des, map[i].Name) == 0)
        {
            end = i;
        }
        if (beg >= 0 && end >= 0)
            break;
    }
    destination = end;

    memset(flag, 0, sizeof(flag));
    memset(pos, 0, sizeof(pos));
    for (i = 0; i < CountOfStation; i++)
        for (j = 0; j < CountOfStation; j++)
            path[i][j] = -1;

    for (i = 0; i < CountOfStation; i++)
    {
        path[i][0] = beg;
        dis[i] = INF;
    }
    for (tmp = map[beg].list; tmp != NULL; tmp = tmp->next)
    {
        map[tmp->end].from = tmp;
        dis[tmp->end] = tmp->weight;
    }
    flag[beg] = 1;

    while (1)
    {
        lowcost = INF;
        for (j = 0; j < CountOfStation; j++)
        {
            if (flag[j] == 0 && dis[j] < lowcost)
            {
                mid = j;
                lowcost = dis[j];
            }
        }
        flag[mid] = 1;
        path[mid][++pos[mid]] = mid;
        tmp = map[mid].list;
        while (tmp != NULL)
        {
            if (flag[tmp->end])
            {
                tmp = tmp->next;
                continue;
            }
            if (dis[mid] + tmp->weight < dis[tmp->end])
            {
                dis[tmp->end] = dis[mid] + tmp->weight;
                map[tmp->end].from = tmp;
                for (j = 0; j < pos[mid]; j++)
                    path[tmp->end][j] = path[mid][j];
            }
            tmp = tmp->next;
        }
        if (flag[end])
            break;
    }
}