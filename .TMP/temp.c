#include <stdio.h>
#include <stdlib.h>

#define classnum 6       //班级数量
#define timenum 3        //每天的课时数量
#define coursenum 6      //课程数量
#define studentnum 232   //学生数量
#define classcapacity 55 //教室最大容量

int table[timenum][classnum] = {
    {0, 4, 0, 5, 3, 2},
    {2, 3, 1, 1, 5, 0},
    {2, 4, 4, 3, 1, 5}};
//表示第几个教室哪一个课时上什么课，数值012345为理化生史地政
//                                          0 1 2 3 4 5

typedef struct student
{
    int choice[coursenum];  //012345分别对应理化生史地政，数值1表示选了，数值2表示没选
    int timetable[timenum]; //012分别对应第123课时，数值表示在哪个教室
} STUDENT;

typedef struct classroom
{
    int stunum; //现在教室已有人数
    int stuname[classcapacity];
} CLASSROOM;

void Initialize(STUDENT *Pstu);
void Choose(STUDENT *Pstu, CLASSROOM (*Pclassroom)[timenum]);
void Printresult(STUDENT *Pstu, CLASSROOM (*Pclassroom)[timenum]);

int main()
{
    int i, j, k;
    STUDENT stu[studentnum], *Pstu;         //定义232个学生
    CLASSROOM classroom[timenum][classnum]; //每个时间段定义一个教室

    //学生初始化
    for (i = 0; i < studentnum; i++)
    {
        for (j = 0; j < coursenum; j++)
            stu[i].choice[j] = -1;
        for (j = 0; j < timenum; j++)
            stu[i].timetable[j] = -1; //未选到教室的置为-1
    }

    //教室初始化
    for (i = 0; i < timenum; i++)
        for (j = 0; j < classnum; j++)
        {
            classroom[i][j].stunum = 0;
            for (k = 0; k < classcapacity; k++)
                classroom[i][j].stuname[k] = -1; //无学生占位时置为-1；
        }

    Initialize(stu);             //录入学生所选课程
    Choose(stu, classroom);      //学生选教室
    Printresult(stu, classroom); //打印结果

    /*
	for(i = 0; i < coursenum; i++)
	{
		printf("选了科目%d的学生有：\n",i+1);
		for(j = 0; j < studentnum; j++)
		{
			if (stu[j].choice[i] == 1) printf("学生%d\n",j+1);
		}
		printf("\n");
	}*/
}

void Initialize(STUDENT *Pstu)
{
    int i, j, k,
        in[20] = {17, 9, 3, 5, 4, 3, 3, 6, 26, 8, 11, 7, 12, 4, 9, 26, 7, 53, 17, 2};
    //化地生17，化历地9，化历生3，历地生5，政地生4，政化地3，政化历3，政化生6，政历地26，政历生8。
    //政物地11，政物化7，政物历12，政物生4，物地生9，物化地26，物化历7，物化生53，物历地17，物历生2。

    k = 0;
    for (i = 0; i < in[0]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //化地生
    for (i = 0; i < in[1]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //化历地
    for (i = 0; i < in[2]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[3] = 1;
        k++;
    } //化历生
    for (i = 0; i < in[3]; i++)
    {
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //历地生
    for (i = 0; i < in[4]; i++)
    {
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[4] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政地生

    for (i = 0; i < in[5]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[4] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政化地
    for (i = 0; i < in[6]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政化历
    for (i = 0; i < in[7]; i++)
    {
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政化生
    for (i = 0; i < in[8]; i++)
    {
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[4] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政历地
    for (i = 0; i < in[9]; i++)
    {
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政历生

    for (i = 0; i < in[10]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[4] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政物地
    for (i = 0; i < in[11]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政物化
    for (i = 0; i < in[12]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政物历
    for (i = 0; i < in[13]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[5] = 1;
        k++;
    } //政物生
    for (i = 0; i < in[14]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //物地生

    for (i = 0; i < in[15]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //物化地
    for (i = 0; i < in[16]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[3] = 1;
        k++;
    } //物化历
    for (i = 0; i < in[17]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[1] = 1;
        (Pstu)[k].choice[2] = 1;
        k++;
    } //物化生
    for (i = 0; i < in[18]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[3] = 1;
        (Pstu)[k].choice[4] = 1;
        k++;
    } //物历地
    for (i = 0; i < in[19]; i++)
    {
        (Pstu)[k].choice[0] = 1;
        (Pstu)[k].choice[2] = 1;
        (Pstu)[k].choice[3] = 1;
        k++;
    } //物历生
}

void Choose(STUDENT *Pstu, CLASSROOM (*Pclassroom)[timenum])
{
    int i, j, k, l, m, n, sitflag[timenum][classnum] = {0}, chooseflag[coursenum] = {1}, timeflag[timenum] = {1};
    for (i = 0; i < studentnum; i++) //对学生开始遍历
    {
        for (n = 0; n < coursenum; n++)
            chooseflag[n] = 1; //这门课已选标志初始化
        for (l = 0; l < timenum; l++)
            timeflag[l] = 1;            //可选择时间初始化
        for (j = 0; j < coursenum; j++) //对学生所选课程开始遍历
        {
            if ((Pstu)[i].choice[j] != 0) //如果学生选了这门课
            {
                for (m = 0; m < timenum; m++)
                    for (k = 0; k < classnum; k++) //遍历所有教室
                    {
                        if ((table[m][k] == j) && ((Pclassroom)[m][k].stunum <= classcapacity) && (chooseflag[j]) && (timeflag[m])) //如果找到了且学生数量不大于最大容量且这个课程未被选且这个课时还没课
                        {
                            Pclassroom[m][k].stunum++;                   //该教室学生数＋1
                            Pclassroom[m][k].stuname[sitflag[m][k]] = i; //该位置座位坐了那个学生
                            sitflag[m][k]++;                             //座位序号加一
                            chooseflag[j] = 0;                           //将这门课标记为已选
                            timeflag[m] = 0;                             //将这个时间标为已选
                            (Pstu)[i].timetable[m] = k;                  //将学生的课表安排设置为此教室
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
            printf("第%d节课   第%d个教室的学生有：\n", i + 1, j + 1);
            for (k = 0; k < (Pclassroom)[i][j].stunum; k++)
            {
                if ((Pclassroom)[i][j].stuname[k] == -1)
                    break;
                printf("学生%d\t", (Pclassroom)[i][j].stuname[k] + 1);
                if ((k + 1) % 10 == 0)
                    printf("\n");
            }
            printf("\n");
            printf("\n");
            printf("\n");
        }
    printf("没选到教室的学生有：\n");
    for (i = 0; i < studentnum; i++)
    {
        for (j = 0; j < timenum; j++)
            if ((Pstu)[i].timetable[j] == -1)
                printf("学生%d的第%d节课\n", i + 1, j + 1);
    }
}
