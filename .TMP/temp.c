#include <stdio.h>
#include <stdlib.h>

#define classnum 6       //�༶����
#define timenum 3        //ÿ��Ŀ�ʱ����
#define coursenum 6      //�γ�����
#define studentnum 232   //ѧ������
#define classcapacity 55 //�����������

int table[timenum][classnum] = {
    {0, 4, 0, 5, 3, 2},
    {2, 3, 1, 1, 5, 0},
    {2, 4, 4, 3, 1, 5}};
//��ʾ�ڼ���������һ����ʱ��ʲô�Σ���ֵ012345Ϊ����ʷ����
//                                          0 1 2 3 4 5

typedef struct student
{
    int choice[coursenum];  //012345�ֱ��Ӧ����ʷ��������ֵ1��ʾѡ�ˣ���ֵ2��ʾûѡ
    int timetable[timenum]; //012�ֱ��Ӧ��123��ʱ����ֵ��ʾ���ĸ�����
} STUDENT;

typedef struct classroom
{
    int stunum; //���ڽ�����������
    int stuname[classcapacity];
} CLASSROOM;

void Initialize(STUDENT *Pstu);
void Choose(STUDENT *Pstu, CLASSROOM (*Pclassroom)[timenum]);
void Printresult(STUDENT *Pstu, CLASSROOM (*Pclassroom)[timenum]);

int main()
{
    int i, j, k;
    STUDENT stu[studentnum], *Pstu;         //����232��ѧ��
    CLASSROOM classroom[timenum][classnum]; //ÿ��ʱ��ζ���һ������

    //ѧ����ʼ��
    for (i = 0; i < studentnum; i++)
    {
        for (j = 0; j < coursenum; j++)
            stu[i].choice[j] = -1;
        for (j = 0; j < timenum; j++)
            stu[i].timetable[j] = -1; //δѡ�����ҵ���Ϊ-1
    }

    //���ҳ�ʼ��
    for (i = 0; i < timenum; i++)
        for (j = 0; j < classnum; j++)
        {
            classroom[i][j].stunum = 0;
            for (k = 0; k < classcapacity; k++)
                classroom[i][j].stuname[k] = -1; //��ѧ��ռλʱ��Ϊ-1��
        }

    Initialize(stu);             //¼��ѧ����ѡ�γ�
    Choose(stu, classroom);      //ѧ��ѡ����
    Printresult(stu, classroom); //��ӡ���

    /*
	for(i = 0; i < coursenum; i++)
	{
		printf("ѡ�˿�Ŀ%d��ѧ���У�\n",i+1);
		for(j = 0; j < studentnum; j++)
		{
			if (stu[j].choice[i] == 1) printf("ѧ��%d\n",j+1);
		}
		printf("\n");
	}*/
}

void Initialize(STUDENT *Pstu)
{
    int i, j, k,
        in[20] = {17, 9, 3, 5, 4, 3, 3, 6, 26, 8, 11, 7, 12, 4, 9, 26, 7, 53, 17, 2};
    //������17��������9��������3��������5��������4��������3��������3��������6��������26��������8��
    //�����11�����ﻯ7��������12��������4�������9���ﻯ��26���ﻯ��7���ﻯ��53��������17��������2��

    k = 0;
    for (i = 0; i < in[0]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //������
    for (i = 0; i < in[1]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //������
    for (i = 0; i < in[2]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[3] = 1;
        k++;
    } //������
    for (i = 0; i < in[3]; i++)
    {
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //������
    for (i = 0; i < in[4]; i++)
    {
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[4] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //������

    for (i = 0; i < in[5]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[4] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //������
    for (i = 0; i < in[6]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //������
    for (i = 0; i < in[7]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //������
    for (i = 0; i < in[8]; i++)
    {
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[4] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //������
    for (i = 0; i < in[9]; i++)
    {
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //������

    for (i = 0; i < in[10]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[4] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //�����
    for (i = 0; i < in[11]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //���ﻯ
    for (i = 0; i < in[12]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //������
    for (i = 0; i < in[13]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //������
    for (i = 0; i < in[14]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //�����

    for (i = 0; i < in[15]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //�ﻯ��
    for (i = 0; i < in[16]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[3] = 1;
        k++;
    } //�ﻯ��
    for (i = 0; i < in[17]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[2] = 1;
        k++;
    } //�ﻯ��
    for (i = 0; i < in[18]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //������
    for (i = 0; i < in[19]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[3] = 1;
        k++;
    } //������
}

void Choose(STUDENT *Pstu, CLASSROOM (*Pclassroom)[timenum])
{
    int i, j, k, l, m, n, sitflag[timenum][classnum] = {0}, chooseflag[coursenum] = {1}, timeflag[timenum] = {1};
    for (i = 0; i < studentnum; i++) //��ѧ����ʼ����
    {
        for (n = 0; n < coursenum; n++)
            chooseflag[n] = 1; //���ſ���ѡ��־��ʼ��
        for (l = 0; l < timenum; l++)
            timeflag[l] = 1;            //��ѡ��ʱ���ʼ��
        for (j = 0; j < coursenum; j++) //��ѧ����ѡ�γ̿�ʼ����
        {
            if ((Pstu)[i].choice[j] != 0) //���ѧ��ѡ�����ſ�
            {
                for (m = 0; m < timenum; m++)
                    for (k = 0; k < classnum; k++) //�������н���
                    {
                        if ((table[m][k] == j) && ((Pclassroom)[m][k].stunum <= classcapacity) && (chooseflag[j]) && (timeflag[m])) //����ҵ�����ѧ�������������������������γ�δ��ѡ�������ʱ��û��
                        {
                            Pclassroom[m][k].stunum++;                   //�ý���ѧ������1
                            Pclassroom[m][k].stuname[sitflag[m][k]] = i; //��λ����λ�����Ǹ�ѧ��
                            sitflag[m][k]++;                             //��λ��ż�һ
                            chooseflag[j] = 0;                           //�����ſα��Ϊ��ѡ
                            timeflag[m] = 0;                             //�����ʱ���Ϊ��ѡ
                            (Pstu)[i].timetable[m] = k;                  //��ѧ���Ŀα�������Ϊ�˽���
                        }
                    }
            }
        }
    }
}

void Printresult(STUDENT *Pstu, CLASSROOM (*Pclassroom)[timenum])
{
    int i, j, k, flag[studentnum] = {0};

    for (i = 0; i < timenum; i++)
        for (j = 0; j < classnum; j++)
        {
            printf("��%d�ڿ�   ��%d�����ҵ�ѧ���У�\n", i + 1, j + 1);
            for (k = 0; k < (Pclassroom)[i][j].stunum; k++)
            {
                if ((Pclassroom)[i][j].stuname[k] == -1)
                    break;
                printf("ѧ��%d\t", (Pclassroom)[i][j].stuname[k] + 1);
                if ((k + 1) % 10 == 0)
                    printf("\n");
            }
            printf("\n");
            printf("\n");
            printf("\n");
        }
    printf("ûѡ�����ҵ�ѧ���У�\n");
    for (i = 0; i < studentnum; i++)
    {
        for (j = 0; j < timenum; j++)
            if ((Pstu)[i].timetable[j] == -1)
                printf("ѧ��%d�ĵ�%d�ڿ�\n", i + 1, j + 1);
    }
}
