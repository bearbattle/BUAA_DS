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
    edge *list;
} node;

node map[501];

void Init();

void Dijkstra();

int main()
{
    Init();

    return 0;
}

void Init()
{
    FILE *IN;
    int SumOfLine, line[13];
    int SumOfStation[13];
    int CountOfStation = 0;
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

void Dijkstra()
{
    
}