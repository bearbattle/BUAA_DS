#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<conio.h>

/*此处兵种数都＋1了是为了后面的数组可以从1开始更便于计算*/
#define soildermaxnum 21
#define tankmaxnum 21
#define cannonmaxnum 21 
#define jetmaxnum 21
#define helicoptermaxnum 21
#define defensemaxnum 21
#define fencemaxnum 100
#define walkcannonmaxnum 21
#define minemaxnum 21
#define retankmaxnum 21
#define reairmaxnum 21

#define length 42
#define width 82/*去掉地图边界，保证数组从1开始到80*/
#define kindnum 11
#define datanum 10

int timestamp=0;/*时间戳，用来计时来实现攻速等功能*/
int attackable[kindnum+1][kindnum+1];/*来自不同兵种的可攻击能力,如attackable[2][3]表示代号为2的兵种是否能攻击代号为3的兵种，1为可以0为不可以。例如步兵打不到飞机*/

typedef struct unit
{
	int locatx;
	int locaty;/*兵种位置*/
	int hp;/*生命值*/
	int att;/*attack即攻击力*/
	int arr;/*arrange即攻击范围*/
	int speed;/*移动速度*/
	int cost;/*造价*/
	int attspeed;/*攻击速度*/
}UNIT;

typedef struct armys
{
	UNIT soilder[soildermaxnum*2+1],/*普通士兵*/
         tank[tankmaxnum*2+1],/*坦克兵种*/ 
         cannon[cannonmaxnum*2+1],/*火炮兵种*/ 
         jet[jetmaxnum*2+1],/*飞机兵种*/
         helicopter[helicoptermaxnum*2+1],//武装直升机兵种
		 defense[defensemaxnum*2+1],//防空兵种 
		 fence[fencemaxnum*2+1],//栅栏兵种 
		 walkcannon[walkcannonmaxnum*2+1],//自走炮兵种
		 mine[minemaxnum*2+1],//地雷
		 retank[retankmaxnum*2+1],//反坦克步兵 
		 reair[reairmaxnum*2+1];//反空军步兵 
		  
}ARMYS;/*直接定义两只不同的军队*/



void goto_xy(int x,int y){ //定位光标位置到指定坐标
HANDLE hOut;
hOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos={x,y};
SetConsoleCursorPosition(hOut,pos);
}

void Printmap(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*打印对抗地图的函数*/

void Printmap2(int map[][width], int bug, int money, ARMYS red, ARMYS blue);/*不打印详细信息地图的函数*/

void Start(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*初始化函数*/ 

void Setforce(int map[][width], ARMYS red, ARMYS blue);/*部署兵力函数*/

void Move(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*移动函数*/

void Attack(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*攻击函数*/

void Fresh(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*刷新函数*/

int Win(int map[][width], ARMYS red, ARMYS blue);/*判断正负*/ 

void End(int map[][width], ARMYS red, ARMYS blue);


int main()
{
	int map[length][width],end=0;
	ARMYS red,blue,*Pred,*Pblue;
    system("color 09");
	Start(map,&red,&blue);

    while (!end)
    {
	/*printf("红方的第一个大兵的数据如下：\n");
    printf("血量:%d  攻击力:%d  攻击范围:%d  移速:%d  位置:(%d,%d)\n",red.soilder[1].hp,
                                                    	red.soilder[1].att,
                                                      	red.soilder[1].arr,
                                                      	red.soilder[1].speed,
                                                      	red.soilder[1].locatx,
                                                      	red.soilder[1].locaty);
    printf("蓝方的坦克的数据如下：\n");
    printf("血量:%d  攻击力:%d  攻击范围:%d  移速:%d  位置:(%d,%d)\n",blue.tank[1].hp,
                                                      	blue.tank[1].att,
                                                      	blue.tank[1].arr,
                                                      	blue.tank[1].speed,
                                                      	blue.tank[1].locatx,
                                                      	blue.tank[1].locaty);*/
        system("cls");
        timestamp++;/*时间戳自增*/
		Printmap(map,&red,&blue);
		Move(map,&red,&blue);
        Attack(map,&red,&blue);
        Fresh(map,&red,&blue);
        end=Win(map,red,blue);
        getchar();
    }
}


void Start(int map[][width], ARMYS *Pred, ARMYS *Pblue)
{
	int i,j,
        data[datanum],/*用来寄存文件中读取的数据*/
        k[2][kindnum];/*用来确定兵种的下标，具体规则见下方位置初始化*/
	FILE *fpin;
	char str[5];
	if ((fpin=fopen("data1.txt","r")) == NULL)
    {
        printf("无法打开文件，系统错误关闭\n");
		exit(0); 
    }
    

	/*以下为兵力部署的初始化*/
    
	fscanf(fpin,"步兵：%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
    for(i = 1; i <= soildermaxnum; i++){
    (*Pred).soilder[i].hp=data[0];
    (*Pblue).soilder[i].hp=data[0];
    (*Pred).soilder[i].att=data[1];
    (*Pblue).soilder[i].att=data[1];
    (*Pred).soilder[i].arr=data[2];
    (*Pblue).soilder[i].arr=data[2];
    (*Pred).soilder[i].speed=data[3];
    (*Pblue).soilder[i].speed=data[3];
    (*Pred).soilder[i].cost=data[4];
    (*Pblue).soilder[i].cost=data[4];
    }/*士兵兵种的数据录入*/ 

    fscanf(fpin,"坦克：%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
    for(i = 0; i <= tankmaxnum; i++){
    (*Pred).tank[i].hp=data[0];
    (*Pblue).tank[i].hp=data[0];
    (*Pred).tank[i].att=data[1];
    (*Pblue).tank[i].att=data[1];
    (*Pred).tank[i].arr=data[2];
    (*Pblue).tank[i].arr=data[2];
    (*Pred).tank[i].speed=data[3];
    (*Pblue).tank[i].speed=data[3];
    (*Pred).tank[i].cost=data[4];
    (*Pblue).tank[i].cost=data[4];
    }/*坦克兵种的录入*/
    
    fscanf(fpin,"火炮：%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
    for(i = 0; i <= cannonmaxnum; i++){
    (*Pred).cannon[i].hp=data[0];
    (*Pblue).cannon[i].hp=data[0];
    (*Pred).cannon[i].att=data[1];
    (*Pblue).cannon[i].att=data[1];
    (*Pred).cannon[i].arr=data[2];
    (*Pblue).cannon[i].arr=data[2];
    (*Pred).cannon[i].speed=data[3];
    (*Pblue).cannon[i].speed=data[3];
    (*Pred).cannon[i].cost=data[4];
    (*Pblue).cannon[i].cost=data[4];
    }/*火炮兵种的录入*/
    
    fscanf(fpin,"飞机：%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
    for(i = 0; i <= jetmaxnum; i++){
    (*Pred).jet[i].hp=data[0];
    (*Pblue).jet[i].hp=data[0];
    (*Pred).jet[i].att=data[1];
    (*Pblue).jet[i].att=data[1];
    (*Pred).jet[i].arr=data[2];
    (*Pblue).jet[i].arr=data[2];
    (*Pred).jet[i].speed=data[3];
    (*Pblue).jet[i].speed=data[3];
    (*Pred).jet[i].cost=data[4];
    (*Pblue).jet[i].cost=data[4];
    }/*飞机兵种的录入*/
    
    fscanf(fpin,"武直：%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
    for(i = 0; i <= helicoptermaxnum; i++){
    (*Pred).helicopter[i].hp=data[0];
    (*Pblue).helicopter[i].hp=data[0];
    (*Pred).helicopter[i].att=data[1];
    (*Pblue).helicopter[i].att=data[1];
    (*Pred).helicopter[i].arr=data[2];
    (*Pblue).helicopter[i].arr=data[2];
    (*Pred).helicopter[i].speed=data[3];
    (*Pblue).helicopter[i].speed=data[3];
    (*Pred).helicopter[i].cost=data[4];
    (*Pblue).helicopter[i].cost=data[4];
    }/*武直兵种的录入*/
    
    fscanf(fpin,"防空：%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
    for(i = 0; i <= defensemaxnum; i++){
    (*Pred).defense[i].hp=data[0];
    (*Pblue).defense[i].hp=data[0];
    (*Pred).defense[i].att=data[1];
    (*Pblue).defense[i].att=data[1];
    (*Pred).defense[i].arr=data[2];
    (*Pblue).defense[i].arr=data[2];
    (*Pred).defense[i].speed=data[3];
    (*Pblue).defense[i].speed=data[3];
    (*Pred).defense[i].cost=data[4];
    (*Pblue).defense[i].cost=data[4];
    }/*防空塔的录入*/
    
    fscanf(fpin,"栅栏：%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
    for(i = 0; i <= fencemaxnum; i++){
    (*Pred).fence[i].hp=data[0];
    (*Pblue).fence[i].hp=data[0];
    (*Pred).fence[i].att=data[1];
    (*Pblue).fence[i].att=data[1];
    (*Pred).fence[i].arr=data[2];
    (*Pblue).fence[i].arr=data[2];
    (*Pred).fence[i].speed=data[3];
    (*Pblue).fence[i].speed=data[3];
    (*Pred).fence[i].cost=data[4];
    (*Pblue).fence[i].cost=data[4];
    }/*栅栏的录入*/

	fscanf(fpin,"地雷：%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
    for(i = 0; i <= fencemaxnum; i++){
    (*Pred).mine[i].hp=data[0];
    (*Pblue).mine[i].hp=data[0];
    (*Pred).mine[i].att=data[1];
    (*Pblue).mine[i].att=data[1];
    (*Pred).mine[i].arr=data[2];
    (*Pblue).mine[i].arr=data[2];
    (*Pred).mine[i].speed=data[3];
    (*Pblue).mine[i].speed=data[3];
    (*Pred).mine[i].cost=data[4];
    (*Pblue).mine[i].cost=data[4];
    }/*地雷的录入*/

    fclose(fpin);
    /*以上为兵力部署的初始化*/
	
	//以下为制约攻击范围的初始化
	for (i = 1; i <= kindnum; i++)
		for (j = 1; j <= kindnum; j++)
			attackable[i][j]=1;//考虑到可攻击的比较多先全部初始化成可攻击
			
	for (i = 1; i <= kindnum; i++)//飞机躲避地面攻击 
		if ((i == 4) || (i == 5) || (i == 6) || (i == 11)) 
			attackable[i][4]=1;
		else  attackable[i][4]=0;
	
	for (i = 1; i <= kindnum; i++)//武直躲避地面攻击 
		if ((i == 4) || (i == 5) || (i == 6) || (i == 11)) 
			attackable[i][5]=1;
		else  attackable[i][5]=0;
		
	for (i = 1; i <= kindnum; i++)//只有步兵才能对地雷造成伤害 
		if  (i == 1) 
			attackable[i][9]=1;
		else  attackable[i][9]=0;
	
	
	/*以下为地图的初步初始化*/
	for(i = 0; i < length; i++)
		for(j = 0; j < width; j++)
			map[i][j]=0;

	Setforce(map,(*Pred),(*Pblue));/*部署兵力*/

	for(i = 1; i <= 10; i++)
		map[i][58]=-7;
	for(i = 30; i <=40; i++) 
		map[i][58]=-7;//放置栅栏 
	
	for(i = 14; i<=23; i++)
	{
		map[i][54]=-2;
		map[i][55]=-2;
	}//坦克战群 
	
	for(i = 4; i <= 7; i++)
		for(j = 61; j <= 63; j++)
		map[i][j]=-4;
		
	for(i = 31; i <= 34; i++)
		for(j = 61; j <= 63; j++)
		map[i][j]=-4;//飞机群
		
	for(i = 1; i <= 9; i=i+2)
		map[i][60]=-3;
	for(i = 31; i <= 39; i=i+2)
		map[i][60]=-3;//炮塔阵	 
		
		
	
    /*以上为地图的初始化*/


    /*以下为测试打印部分 
    printf("红方的大兵的数据如下：\n");
    printf("血量:%d  攻击力:%d  攻击范围:%d  移速:%d\n",(*Pred).soilder[1].hp,
                                                      (*Pred).soilder[1].att,
                                                      (*Pred).soilder[1].arr,
                                                      (*Pred).soilder[1].speed);
    printf("蓝方的坦克的数据如下：\n");
    printf("血量:%d  攻击力:%d  攻击范围:%d  移速:%d\n",(*Pblue).tank[1].hp,
                                                      (*Pblue).tank[1].att,
                                                      (*Pblue).tank[1].arr,
                                                      (*Pblue).tank[1].speed);
	printf("红方的火炮的数据如下：\n");
    printf("血量:%d  攻击力:%d  攻击范围:%d  移速:%d\n",(*Pred).cannon[1].hp,
                                                      (*Pred).cannon[1].att,
                                                      (*Pred).cannon[1].arr,
                                                      (*Pred).cannon[1].speed);
	printf("蓝方的飞机的数据如下：\n");
    printf("血量:%d  攻击力:%d  攻击范围:%d  移速:%d\n",(*Pred).jet[1].hp,
                                                      (*Pred).jet[1].att,
                                                      (*Pred).jet[1].arr,
                                                      (*Pred).jet[1].speed);                                           
    */


	/*以下是初始化的兵种位置录入*/
	for(i = 0; i < 2; i++)
        for(j = 0; j < kindnum+1; j++)
            k[i][j]=0;

    for(i = 1; i < length-1; i++)
        for(j = 1; j < width-1; j++)
            {
                switch(map[i][j])/*其中k的第一个下标表示红蓝方区别，0为红，1为蓝，第二个下标表示兵种，1为步兵，2为坦克*/
                {
                    case 1:{k[0][1]++;
                            (*Pred).soilder[(k[0][1])].locatx=i;
                            (*Pred).soilder[(k[0][1])].locaty=j;
                            break;
                            }
                    case 2:{k[0][2]++;
                            (*Pred).tank[(k[0][2])].locatx=i;
                            (*Pred).tank[(k[0][2])].locaty=j;
                            break;
                            }
                    case 3:{k[0][3]++;
                            (*Pred).cannon[(k[0][3])].locatx=i;
                            (*Pred).cannon[(k[0][3])].locaty=j;
                            break;
                            }
                    case 4:{k[0][4]++;
                            (*Pred).jet[(k[0][4])].locatx=i;
                            (*Pred).jet[(k[0][4])].locaty=j;
                            break;
                            }
                    case 5:{k[0][5]++;
                            (*Pred).helicopter[(k[0][5])].locatx=i;
                            (*Pred).helicopter[(k[0][5])].locaty=j;
                            break;
                            }
                    case 6:{k[0][6]++;
                            (*Pred).defense[(k[0][6])].locatx=i;
                            (*Pred).defense[(k[0][6])].locaty=j;
                            break;
                            }
                    case 7:{k[0][7]++;
                            (*Pred).fence[(k[0][7])].locatx=i;
                            (*Pred).fence[(k[0][7])].locaty=j;
                            break;
                            }
                    case 8:{k[0][8]++;
                            (*Pred).mine[(k[0][8])].locatx=i;
                            (*Pred).mine[(k[0][8])].locaty=j;
                            break;
                            }
                    case -1:{k[1][1]++;
                            (*Pblue).soilder[(k[1][1])].locatx=i;
                            (*Pblue).soilder[(k[1][1])].locaty=j;
                            break;
                            }
                    case -2:{k[1][2]++;
                            (*Pblue).tank[(k[1][2])].locatx=i;
                            (*Pblue).tank[(k[1][2])].locaty=j;
                            break;
                            }
                    case -3:{k[1][3]++;
                            (*Pblue).cannon[(k[1][3])].locatx=i;
                            (*Pblue).cannon[(k[1][3])].locaty=j;
                            break;
                            }
                    case -4:{k[1][4]++;
                            (*Pblue).jet[(k[1][4])].locatx=i;
                            (*Pblue).jet[(k[1][4])].locaty=j;
                            break;
                            }
                    case -5:{k[1][5]++;
                            (*Pblue).helicopter[(k[1][5])].locatx=i;
                            (*Pblue).helicopter[(k[1][5])].locaty=j;
                            break;
                            }
                    case -6:{k[1][6]++;
                            (*Pblue).defense[(k[1][5])].locatx=i;
                            (*Pblue).defense[(k[1][5])].locaty=j;
                            break;
                            }
                    case -7:{k[1][7]++;
                            (*Pblue).fence[(k[1][5])].locatx=i;
                            (*Pblue).fence[(k[1][5])].locaty=j;
                            break;
                            }
                    case -8:{k[1][8]++;
                            (*Pblue).mine[(k[1][8])].locatx=i;
                            (*Pblue).mine[(k[1][8])].locaty=j;
                            break;
                            }
                }
            }

	/*以上为初始化的兵种位置录入*/

    printf("\n");
}

void Setforce(int map[][width], ARMYS red, ARMYS blue)
{
	int i,j,key,half, 
		flag,/*兵种的标志*/
		x,y,/*要放置的坐标*/
		m,n,/*下一步改变的坐标*/
		out=1,/*判断是否退出*/
		money,/*持有的金额*/ 
		pay;/*花费*/
	
	half=(width-2)/2;
	printf("请输入持有的总金额（对应游戏难度，30000以下为困难，30000以上为简单）：");
	scanf("%d",&money);
	printf("\n"); 
	
	/*初始化*/
	flag=1;
	x=20;
	y=1;
	map[x][y]=flag;
	system("cls"); 
	Printmap2(map,0,money,red,blue);
	while(out)
	{
		key = getch();
		switch(key)
		{
			case 49:{flag=1;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
			}
			case 50:{flag=2;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
			}
			case 51:{flag=3;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
			}
			case 52:{flag=4;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
			}
			case 53:{flag=5;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
			}
			case 54:{flag=6;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
			}
			case 55:{flag=7;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
			}
			case 56:{flag=8;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
			}
			case 'w':{m=x-1;n=y;/*按下W时的反应*/
				if ((m < 1) || (m > 40) || (n < 1) || (n >= half))
				{
					system("cls");
					Printmap2(map,1,money,red,blue); 
					break;
				}
				else if(map[m][n] != 0)
				{
					system("cls");
					Printmap2(map,2,money,red,blue);  
					break;
				}
				else{
					map[x][y]=0;
					map[m][n]=flag;
					x=m;
					y=n;
					system("cls");
					Printmap2(map,0,money,red,blue);
					break;
				} 
			}
			case 'a':{m=x;n=y-1;/*按下A时的反应*/ 
				if ((m < 1) || (m > 40) || (n < 1) || (n >= half))
				{
					system("cls");
					Printmap2(map,1,money,red,blue); 
					break;
				}
				else if(map[m][n] != 0)
				{
					system("cls");
					Printmap2(map,2,money,red,blue);  
					break;
				}
				else{
					map[x][y]=0;
					map[m][n]=flag;
					system("cls");
					x=m;
					y=n;
					Printmap2(map,0,money,red,blue);
					break;
				} 
			}
			case 's':{m=x+1;n=y;/*按下S时的反应*/ 
				if ((m < 1) || (m > 40) || (n < 1) || (n >= half))
				{
					system("cls");
					Printmap2(map,1,money,red,blue); 
					break;
				}
				else if(map[m][n] != 0)
				{
					system("cls");
					Printmap2(map,2,money,red,blue);  
					break;
				}
				else{
					map[x][y]=0;
					map[m][n]=flag;
					x=m;
					y=n;
					system("cls");
					Printmap2(map,0,money,red,blue);
					break;
				} 
			}
			case 'd': {m=x;n=y+1;/*按下D时的反应*/ 
				if ((m < 1) || (m > 40) || (n < 1) || (n >= half))
				{
					system("cls");
					Printmap2(map,1,money,red,blue); 
					break;
				}
				else if(map[m][n] != 0)
				{
					system("cls");
					Printmap2(map,2,money,red,blue);  
					break;
				}
				else{
					map[x][y]=0;
					map[m][n]=flag;
					x=m;
					y=n;
					system("cls");
					Printmap2(map,0,money,red,blue);
					break;
				} 
			}
			case 13:{switch (flag)/*按下回车的反应*/
				{
					case 1:{pay=red.soilder[1].cost;
						money=money-pay;
						break;
					}
					case 2:{pay=red.tank[1].cost;
						money=money-pay;
						break;
					}
					case 3:{pay=red.cannon[1].cost;
						money=money-pay;
						break;
					}
					case 4:{pay=red.jet[1].cost;
						money=money-pay;
						break;
					}
					case 5:{pay=red.helicopter[1].cost;
						money=money-pay;
						break;
					}
					case 6:{pay=red.defense[1].cost;
						money=money-pay;
						break;
					}
					case 7:{pay=red.fence[1].cost;
						money=money-pay;
						break;
					}
				}
				if (money < 0)
				{
					money=money+pay;
					system("cls");
					Printmap2(map,4,money,red,blue);
					break;
				}
				else{
				x=m+1;y=n;
				map[x][y]=flag;
				system("cls");
				Printmap2(map,0,money,red,blue);
				break;
				}
			}
			case 27:{out=0;/*按下Esc的反应*/
				 map[x][y]=0;
				 system("cls");
				 Printmap2(map,3,money,red,blue);
				 break;
			}
		}
		
	}
	printf("这就是你部署红方的最终地图\n");
	getchar();
	getchar();/*出了一些bug导致缓存区溢出了所以多写一个getchar*/
}

void Printmap(int map[][width], ARMYS *Pred, ARMYS *Pblue)
{
	int i,j,k,test=10;
	int Rsoildernum=0,Rsoilderhp=0;
	int Rtanknum=0,Rtankhp=0;
	int Rcannonnum=0,Rcannonhp=0;
	int Rjetnum=0,Rjethp=0;
	int Rhelicopternum=0,Rhelicopterhp=0;
	int Rdefensenum=0,Rdefensehp=0;
	int Rfencenum=0,Rfencehp=0;
	int Rminenum=0,Rminehp=0;

	int Bsoildernum=0,Bsoilderhp=0;
	int Btanknum=0,Btankhp=0;
	int Bcannonnum=0,Bcannonhp=0;
	int Bjetnum=0,Bjethp=0;
	int Bhelicopternum=0,Bhelicopterhp=0;
	int Bdefensenum=0,Bdefensehp=0;
	int Bfencenum=0,Bfencehp=0;
	int Bminenum=0,Bminehp=0;
	
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	printf("-----------------------------------------------------红蓝对抗地图-------------------------------------------------------\n");
	printf("                                                                                                                                                          双方对拼详细数据栏\n");




	/*以下为打印横坐标轴数字*/
	printf("                    00000000011111111112222222222333333333344444444445555555555666666666677777777778\n");
	printf("                    12345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
    /*以上为打印横坐标轴数字*/


	for(i = 0; i < length; i++)
	{
        if ((i < 10)&&(i > 0))
            printf("                  %d",i);
        else if (i > 0)
            printf("                 %d",i);
        else
            printf("                   ");
		for(j = 0; j < width; j++)
        {
			if (j == 0 || j == width-1)
				printf("|");
			else if (i == 0 || i == length-1)
				printf("-");
			else switch(map[i][j])/*通过正负号来判断双方势力不同*/
			{
			    case 0:printf(" ");break;
			    case 1:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   	printf("S");
					   	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   	break; 
			    case 2:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("T");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 3:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("C");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 4:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("J");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 5:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("H");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 6:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("D");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 7:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("F");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 8:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("M");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case -1:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 	printf("S");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case -2:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 	printf("T");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case -3:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 	printf("C");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case -4:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 	printf("J");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case -5:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 	printf("H");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case -6:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 	printf("D");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case -7:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 	printf("F");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case -8:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 	printf("M");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			}
        }
		printf("\n");
	}


    /*以下是统计场上红蓝势力的情况*/
    for(i = 1; i < length-1; i++)
        for(j = 1; j < width-1; j++)
        if (map[i][j] != 0)
        {
            switch(map[i][j])
            {
                case 1:Rsoildernum++;break;
                case 2:Rtanknum++;break;
                case 3:Rcannonnum++;break;
                case 4:Rjetnum++;break;
                case 5:Rhelicopternum++;break;
                case 6:Rdefensenum++;break;
                case 7:Rfencenum++;break;
                case 8:Rminenum++;break;
                case -1:Bsoildernum++;break;
                case -2:Btanknum++;break;
                case -3:Bcannonnum++;break;
                case -4:Bjetnum++;break;
                case -5:Bhelicopternum++;break;
                case -6:Bdefensenum++;break;
                case -7:Bfencenum++;break;
                case -8:Bminenum++;break;
            }

            switch(map[i][j])/*统计总血量的函数*/
            {
                case 1:{for(k = 1; k < soildermaxnum; k++)
                        if (((*Pred).soilder[k].locatx == i) && (*Pred).soilder[k].locaty == j)
                            Rsoilderhp+=(*Pred).soilder[k].hp;
                }
                case 2:{for(k = 1; k < tankmaxnum; k++)
                        if (((*Pred).tank[k].locatx == i) && (*Pred).tank[k].locaty == j)
                            Rtankhp+=(*Pred).tank[k].hp;
                }
                case 3:{for(k = 1; k < cannonmaxnum; k++)
                        if (((*Pred).cannon[k].locatx == i) && (*Pred).cannon[k].locaty == j)
                            Rcannonhp+=(*Pred).cannon[k].hp;
                }
                case 4:{for(k = 1; k < jetmaxnum; k++)
                        if (((*Pred).jet[k].locatx == i) && (*Pred).jet[k].locaty == j)
                            Rjethp+=(*Pred).jet[k].hp;
                }
                case 5:{for(k = 1; k < helicoptermaxnum; k++)
                        if (((*Pred).helicopter[k].locatx == i) && (*Pred).helicopter[k].locaty == j)
                            Rhelicopterhp+=(*Pred).helicopter[k].hp;
                }
                case 6:{for(k = 1; k < defensemaxnum; k++)
                        if (((*Pred).defense[k].locatx == i) && (*Pred).defense[k].locaty == j)
                            Rdefensehp+=(*Pred).defense[k].hp;
                }
                case 7:{for(k = 1; k < fencemaxnum; k++)
                        if (((*Pred).fence[k].locatx == i) && (*Pred).fence[k].locaty == j)
                            Rfencehp+=(*Pred).fence[k].hp;
                }
                case 8:{for(k = 1; k < minemaxnum; k++)
                        if (((*Pred).mine[k].locatx == i) && (*Pred).mine[k].locaty == j)
                            Rminehp+=(*Pred).mine[k].hp;
                }
                case -1:{for(k = 1; k < soildermaxnum; k++)
                        if (((*Pblue).soilder[k].locatx == i) && (*Pblue).soilder[k].locaty == j)
                            Bsoilderhp+=(*Pblue).soilder[k].hp;
                }
                case -2:{for(k = 1; k < tankmaxnum; k++)
                        if (((*Pblue).tank[k].locatx == i) && (*Pblue).tank[k].locaty == j)
                            Btankhp+=(*Pblue).tank[k].hp;
            	}
                case -3:{for(k = 1; k < cannonmaxnum; k++)
                        if (((*Pblue).cannon[k].locatx == i) && (*Pblue).cannon[k].locaty == j)
                            Bcannonhp+=(*Pblue).cannon[k].hp;
            	}
            	case -4:{for(k = 1; k < jetmaxnum; k++)
                        if (((*Pblue).jet[k].locatx == i) && (*Pblue).jet[k].locaty == j)
                            Bjethp+=(*Pblue).jet[k].hp;
            	}
            	case -5:{for(k = 1; k < helicoptermaxnum; k++)
                        if (((*Pblue).helicopter[k].locatx == i) && (*Pblue).helicopter[k].locaty == j)
                            Bhelicopterhp+=(*Pblue).helicopter[k].hp;
            	}
            	case -6:{for(k = 1; k < defensemaxnum; k++)
                        if (((*Pblue).defense[k].locatx == i) && (*Pblue).defense[k].locaty == j)
                            Bdefensehp+=(*Pblue).defense[k].hp;
            	}
            	case -7:{for(k = 1; k < fencemaxnum; k++)
                        if (((*Pblue).fence[k].locatx == i) && (*Pblue).fence[k].locaty == j)
                            Bfencehp+=(*Pblue).fence[k].hp;
            	}
            	case -8:{for(k = 1; k < minemaxnum; k++)
                        if (((*Pblue).mine[k].locatx == i) && (*Pblue).mine[k].locaty == j)
                            Bminehp+=(*Pblue).mine[k].hp;
            }
        }



		} 
    printf("\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    goto_xy(120,40);
	printf("以下是红蓝势力的详细数据：");
	goto_xy(120,41);
    printf("红方                          |蓝方");
    goto_xy(120,42);
    printf("兵种      数量      总血量    |兵种      数量      总血量    ");
    goto_xy(120,43);
    printf("士兵      %-10d%-10d|士兵      %-10d%-10d\n",Rsoildernum,Rsoilderhp,Bsoildernum,Bsoilderhp);
    goto_xy(120,44);
    printf("坦克      %-10d%-10d|坦克      %-10d%-10d\n",Rtanknum,Rtankhp,Btanknum,Btankhp);
    goto_xy(120,45);
    printf("炮塔      %-10d%-10d|炮塔      %-10d%-10d\n",Rcannonnum,Rcannonhp,Bcannonnum,Bcannonhp);
    goto_xy(120,46);
    printf("飞机      %-10d%-10d|飞机      %-10d%-10d\n",Rjetnum,Rjethp,Bjetnum,Bjethp);
    goto_xy(120,47);
    printf("武直      %-10d%-10d|武直      %-10d%-10d\n",Rhelicopternum,Rhelicopterhp,Bhelicopternum,Bhelicopterhp);
    goto_xy(120,48);
    printf("防空      %-10d%-10d|防空      %-10d%-10d\n",Rdefensenum,Rdefensehp,Bdefensenum,Bdefensehp);
    goto_xy(120,49);
    printf("栅栏      %-10d%-10d|栅栏      %-10d%-10d\n",Rfencenum,Rfencehp,Bfencenum,Bfencehp);
    goto_xy(120,50);
    //printf("地雷      %-10d%-10d|地雷      %-10d%-10d\n",Rfencenum,Rfencehp,Bfencenum,Bfencehp);
}

void Printmap2(int map[][width], int bug, int money, ARMYS red, ARMYS blue)
{
	int i,j,k,half;
	half=(width-2)/2;
	/*以下为在部署兵力函数中出现的打印地图*/
	/*由于人为红方，故只能布置红方一半场地*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	printf("\n"); 
	printf("-------------------------------------------------战前部署地图-----------------------------------------------------\n");
	for(i = 0; i < length; i++)
	{
        if ((i < 10)&&(i > 0))
            printf("                  %d",i);
        else if (i > 0)
            printf("                 %d",i);
        else
            printf("                   ");
		for(j = 0; j < width; j++)
        {
			if (j == 0 || j == width-1)
				printf("|");
			else if (i == 0 || i == length-1)
				printf("-");
			else if (j >= half) printf("X");/*蓝色方地区显示X表示不可放置*/
			else switch(map[i][j])/*通过正负号来判断双方势力不同*/
			{
			    case 0:printf(" ");break;
			    case 1:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   	printf("S");
					   	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   	break; 
			    case 2:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("T");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 3:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("C");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 4:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("J");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 5:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("H");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 6:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("D");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
			    case 7:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					 	printf("F");
			    		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    		break;
        	}
		}
		printf("\n");
	 }
	printf("------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                         注：X表示被遮挡住的蓝方场地，您部署兵力时不可越过蓝方领域\n");
	printf("\n");
	printf("\n");
	if (bug != 3)
	{
		printf("兵种购买菜单                                           您的余额为：￥%d\n",money);
		printf("--------------------------------------------------------------------------\n"); 
		printf("【1】步兵\t\t￥%d\t\t\t【7】栅栏\t\t￥%d\n",red.soilder[1].cost,red.fence[1].cost); 
		printf("【2】坦克\t\t￥%d\t\t\t【8】自走炮\t\t￥%d\n",red.tank[1].cost,red.fence[1].cost);
		printf("【3】炮塔\t\t￥%d\t\t\t【9】地雷\t\t￥%d\n",red.cannon[1].cost,red.fence[1].cost);
		printf("【4】飞机\t\t￥%d\t\t\t【0】反坦克步兵\t\t￥%d\n",red.jet[1].cost,red.fence[1].cost);
		printf("【5】武直\t\t￥%d\t\t\t【-】防空步兵\t\t￥%d\n",red.helicopter[1].cost,red.defense[1].cost);
		printf("【6】防空塔\t\t￥%d\n",red.defense[1].cost);
		printf("\n");
		printf("【W】向上移动光标   【S】向下移动光标   【A】向左移动光标   【D】向右移动光标\n");
		printf("【ESC】确认部署      【Enter】确认放置兵力\n");
	}
	
	
	/*bug判断与说明*/
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	if(bug == 1) printf("放置的位置越界了\n");
	else if (bug == 2) printf("放置的位置有兵力了\n");
	else if (bug == 4) printf("您的余额不足！\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
}


void Move(int map[][width], ARMYS *Pred, ARMYS *Pblue)
{
    int i,j,k,
        step,temp,
        flag[length][width];
    /*k为兵种单位的下标记录数组*/


    /*标志数组的初始化*/
    for(i = 1; i < length-1; i++)
        for(j = 1; j < width-1; j++)
        	flag[i][j]=0;

    /*遍历式兵力移动*/
	for(i = 1; i < length-1; i++)
        for(j = 1; j < width-1; j++)
        {
            if (map[i][j]>0 && flag[i][j]!=1)/*判断为红方势力且不是移动过的兵力，向右或上下移动*/
            {
                switch(map[i][j])
                {
                    case 1:{step=(*Pred).soilder[1].speed;
                            if (j >= 40) step=-step;
							for(k = 1; k < soildermaxnum; k++)
                                if (((*Pred).soilder[k].locatx == i) && (*Pred).soilder[k].locaty == j)
                                if (map[i][j+step]==0)/*红方基础移动即向右移动*/ 
                				{
                    				map[i][j+step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j+step]=1;
                    				(*Pred).soilder[k].locaty+=step;
                				}
								else if (map[i-step][j]==0)/*尝试向上走*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pred).soilder[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*尝试向下走*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pred).soilder[k].locatx+=step;
                				}	
                            break;
                    }
                    case 2:{step=(*Pred).tank[1].speed;
                    		if (j >= 40) step=-step;
                            for(k = 1; k < tankmaxnum; k++)
                                if (((*Pred).tank[k].locatx == i) && (*Pred).tank[k].locaty == j)
                                if (map[i][j+step]==0)/*红方基础移动即向右移动*/ 
                				{
                    				map[i][j+step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j+step]=1;
                    				(*Pred).tank[k].locaty+=step;
                				}
								else if (map[i-step][j]==0)/*尝试向上走*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pred).tank[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*尝试向下走*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pred).tank[k].locatx+=step;
                				}
                            break;
                    }
                    case 3:{step=(*Pred).cannon[1].speed;/*不可移动单位*/ 
                            for(k = 1; k < cannonmaxnum; k++)
                                if (((*Pred).cannon[k].locatx == i) && (*Pred).cannon[k].locaty == j)
                                    (*Pred).cannon[k].locaty+=step;
                            break;
                    }
                    case 4:{step=(*Pred).jet[1].speed;
                    		if (j >= 40) step=-step;
                            for(k = 1; k < jetmaxnum; k++)
                                if (((*Pred).jet[k].locatx == i) && (*Pred).jet[k].locaty == j)
                                if (map[i][j+step]==0)/*红方基础移动即向右移动*/ 
                				{
                    				map[i][j+step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j+step]=1;
                    				(*Pred).jet[k].locaty+=step;
                				}
								else if (map[i-step][j]==0)/*尝试向上走*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pred).jet[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*尝试向下走*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pred).jet[k].locatx+=step;
                				}
                            break;
                    }
                    case 5:{step=(*Pred).helicopter[1].speed;
                    		if (j >= 40) step=-step;
                            for(k = 1; k < helicoptermaxnum; k++)
                                if (((*Pred).helicopter[k].locatx == i) && (*Pred).helicopter[k].locaty == j)
                                if (map[i][j+step]==0)/*红方基础移动即向右移动*/ 
                				{
                    				map[i][j+step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j+step]=1;
                    				(*Pred).helicopter[k].locaty+=step;
                				}
								else if (map[i-step][j]==0)/*尝试向上走*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pred).helicopter[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*尝试向下走*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pred).helicopter[k].locatx+=step;
                				}
                            break;
                    }
                    case 6:break; 
                    case 7:break;
                }
            }
            else if (map[i][j]<0 && flag[i][j]!=1)/*判断为蓝方势力且不是移动过的兵力，向左或上下移动移动*/
            {
                switch(map[i][j])
                {
                    case -1:{step=(*Pblue).soilder[1].speed;
                    		if (j <= 40) step=-step;
                            for(k = 1; k < soildermaxnum; k++)
                                if (((*Pblue).soilder[k].locatx == i) && (*Pblue).soilder[k].locaty == j)
                                if (map[i][j-step]==0)/*蓝方基础移动即向左移动*/ 
                				{
                    				map[i][j-step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j-step]=1;
                    				(*Pblue).soilder[k].locaty-=step;
                				}
								else if (map[i-step][j]==0)/*尝试向上走*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pblue).soilder[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*尝试向下走*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pblue).soilder[k].locatx+=step;
                				}
                            break;
                    }
                    case -2:{step=(*Pblue).tank[1].speed;
                    		if (j <= 40) step=-step;
                            for(k = 1; k < tankmaxnum; k++)
                                if (((*Pblue).tank[k].locatx == i) && (*Pblue).tank[k].locaty == j)
                                if (map[i][j-step]==0)/*蓝方基础移动即向左移动*/ 
                				{
                    				map[i][j-step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j-step]=1;
                    				(*Pblue).tank[k].locaty-=step;
                				}
								else if (map[i-step][j]==0)/*尝试向上走*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pblue).tank[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*尝试向下走*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pblue).tank[k].locatx+=step;
                				}
                            break;
                    }
                    case -3:{step=(*Pblue).cannon[1].speed;/*不可移动单位*/
                            for(k = 1; k < cannonmaxnum; k++)
                                if (((*Pblue).cannon[k].locatx == i) && (*Pblue).cannon[k].locaty == j)
                                    (*Pblue).cannon[k].locaty-=step;
                            break;
                    }
                    case -4:{step=(*Pblue).jet[1].speed;
                    		if (j <= 40) step=-step;
                            for(k = 1; k < jetmaxnum; k++)
                                if (((*Pblue).jet[k].locatx == i) && (*Pblue).jet[k].locaty == j)
                                if (map[i][j-step]==0)/*蓝方基础移动即向左移动*/ 
                				{
                    				map[i][j-step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j-step]=1;
                    				(*Pblue).jet[k].locaty-=step;
                				}
								else if (map[i-step][j]==0)/*尝试向上走*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pblue).jet[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*尝试向下走*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pblue).jet[k].locatx+=step;
                				}
                            break;
                    }
                    case -5:{step=(*Pblue).helicopter[1].speed;
                    		if (j <= 40) step=-step;
                            for(k = 1; k < helicoptermaxnum; k++)
                                if (((*Pblue).helicopter[k].locatx == i) && (*Pblue).helicopter[k].locaty == j)
                                if (map[i][j-step]==0)/*蓝方基础移动即向左移动*/ 
                				{
                    				map[i][j-step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j-step]=1;
                    				(*Pblue).helicopter[k].locaty-=step;
                				}
								else if (map[i-step][j]==0)/*尝试向上走*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pblue).helicopter[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*尝试向下走*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pblue).helicopter[k].locatx+=step;
                				}
                            break;
                    }
                    case -6:break;
                    case -7:break;
                }
                
            }
        }

}

void Attack(int map[][width], ARMYS *Pred, ARMYS *Pblue)
{
    int i,j,k,m,n,left,up,right,down,range;
    int nearest,test=0;
    int flagx,flagy;
    int attack;/*寄存该兵种的攻击力*/ 
    int Rline,Bline;
    const int Rcolumn=120;
    const int Bcolumn=165;
    
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Rline=7;Bline=7;
    for(i = 1; i <= length-2; i++)
        for(j = 1; j <= width-2; j++)
        if(map[i][j] != 0)
        {
             switch(map[i][j]){/*获取攻击力攻击范围等参数*/
                 case 1:range=(*Pred).soilder[1].arr;
                        attack=(*Pred).soilder[1].att;
                        break;
                 case 2:range=(*Pred).tank[1].arr;
                        attack=(*Pred).tank[1].att;
                        break;
                 case 3:range=(*Pred).cannon[1].arr;
                        attack=(*Pred).cannon[1].att;
                        break;
                 case 4:range=(*Pred).jet[1].arr;
                        attack=(*Pred).jet[1].att;
                        break;
                 case 5:range=(*Pred).helicopter[1].arr;
                        attack=(*Pred).helicopter[1].att;
                        break;
                 case 6:range=(*Pred).defense[1].arr;
                        attack=(*Pred).defense[1].att;
                        break;
                 case 7:range=(*Pred).fence[1].arr;
                        attack=(*Pred).fence[1].att;
                        break;
                 case -1:range=(*Pblue).soilder[1].arr;
                        attack=(*Pblue).soilder[1].att;
                        break;
                 case -2:range=(*Pblue).tank[1].arr;
                        attack=(*Pblue).tank[1].att;
                        break;
                 case -3:range=(*Pblue).cannon[1].arr;
                        attack=(*Pblue).cannon[1].att;
                        break;
                 case -4:range=(*Pblue).jet[1].arr;
                        attack=(*Pblue).jet[1].att;
                        break;
                 case -5:range=(*Pblue).helicopter[1].arr;
                        attack=(*Pblue).helicopter[1].att;
                        break;
                 case -6:range=(*Pblue).defense[1].arr;
                        attack=(*Pblue).defense[1].att;
                        break;
                 case -7:range=(*Pblue).fence[1].arr;
                        attack=(*Pblue).fence[1].att;
                        break;
             }
			//printf("获取的数据为：攻击范围：%d\t攻击力：%d\n",range,attack);
            if (i-range < 1)
                up=1;
            else up=i-range;
                
            if (i+range > 40)
                down=40;
            else down=i+range;
                
            if (j-range < 1)
                left=1;
            else left=j-range;
                
            if (j+range > 80)
                right=80;
            else right=j+range;
            /*以上为防止数组越界*/
            nearest=2*(range*2)*(range*2);/*设置为最大攻击范围*/
            flagx=0;
            flagy=0;
            for(m = up; m <= down; m++)
                for(n = left; n <= right; n++)
                    if (map[m][n]*map[i][j] < 0)/*寻找攻击范围内最近的敌方目标并记录*/
                        {
                            test=(m-i)*(m-i)+(n-j)*(n-j);
                            if (test <= nearest)
                            {
                                nearest=test;
                                flagx=m;
                                flagy=n;
                            }
                        }
                        //printf("它最近的敌方单位的坐标为：(%d,%d)\n",flagx,flagy);
            if (((flagx*flagy) != 0) && (attackable[abs(map[i][j])][abs(map[flagx][flagy])]))/*找到攻击目标,且能对该目标进行攻击*/ 
            {
				switch(map[i][j])
				{
					case 1:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
							goto_xy(Rcolumn,Rline);
							printf("红方步兵  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break;
					case 2:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
							goto_xy(Rcolumn,Rline);
					   		printf("红方坦克  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break;
					case 3:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("红方炮塔  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break;
					case 4:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("红方飞机  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break; 
					case 5:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("红方武直  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break; 
					case 6:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("红方防空  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break;
					case 7:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("红方栅栏  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break; 
					case -1:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("蓝方步兵  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			    	case -2:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("蓝方坦克  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
					case -3:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("蓝方炮塔  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
					case -4:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("蓝方飞机  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			    	case -5:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("蓝方武直  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			    	case -6:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("蓝方防空  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			    	case -7:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("蓝方栅栏  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			 	}
				switch(map[flagx][flagy])/*对所选中的目标进行攻击*/
                             {
                                case 1:for(k = 1; k < soildermaxnum; k++)
                                        if (((*Pred).soilder[k].locatx == flagx) && (*Pred).soilder[k].locaty == flagy)
                                            {
												(*Pred).soilder[k].hp=(*Pred).soilder[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  红方步兵  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++; 
												//printf("它对红方第%d号士兵造成%d的伤害\n",k,attack);
                                        	}
                                        break;
                                case 2:for(k = 1; k < tankmaxnum; k++)
                                        if (((*Pred).tank[k].locatx == flagx) && (*Pred).tank[k].locaty == flagy)
                                            {
												(*Pred).tank[k].hp=(*Pred).tank[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  红方坦克  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("它对红方第%d号坦克造成%d的伤害\n",k,attack);
											}
                                        break;
                                case 3:for(k = 1; k < cannonmaxnum; k++)
                                        if (((*Pred).cannon[k].locatx == flagx) && (*Pred).cannon[k].locaty == flagy)
                                            {
												(*Pred).cannon[k].hp=(*Pred).cannon[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  红方炮塔  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("它对红方第%d号火炮造成%d的伤害\n",k,attack);
											}
                                        break;
                                case 4:for(k = 1; k < jetmaxnum; k++)
                                        if (((*Pred).jet[k].locatx == flagx) && (*Pred).jet[k].locaty == flagy)
                                            {
												(*Pred).jet[k].hp=(*Pred).jet[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  红方飞机  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("它对红方第%d号火炮造成%d的伤害\n",k,attack);
											}
                                        break;
                                case 5:for(k = 1; k < helicoptermaxnum; k++)
                                        if (((*Pred).helicopter[k].locatx == flagx) && (*Pred).helicopter[k].locaty == flagy)
                                            {
												(*Pred).helicopter[k].hp=(*Pred).helicopter[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  红方武直  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("它对红方第%d号火炮造成%d的伤害\n",k,attack);
											}
                                        break;
                                case 6:for(k = 1; k < defensemaxnum; k++)
                                        if (((*Pred).defense[k].locatx == flagx) && (*Pred).defense[k].locaty == flagy)
                                            {
												(*Pred).defense[k].hp=(*Pred).defense[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  红方武直  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("它对红方第%d号火炮造成%d的伤害\n",k,attack);
											}
                                        break;
                                case 7:for(k = 1; k < fencemaxnum; k++)
                                        if (((*Pred).fence[k].locatx == flagx) && (*Pred).fence[k].locaty == flagy)
                                            {
												(*Pred).fence[k].hp=(*Pred).fence[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  红方武直  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("它对红方第%d号火炮造成%d的伤害\n",k,attack);
											}
                                        break;
                                case -1:for(k = 1; k < soildermaxnum; k++)
                                        if (((*Pblue).soilder[k].locatx == flagx) && (*Pblue).soilder[k].locaty == flagy)
                                            {
												(*Pblue).soilder[k].hp=(*Pblue).soilder[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  蓝方步兵  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("它对蓝方第%d号士兵造成%d的伤害\n",k,attack);
											} 
                                        break;
                                case -2:for(k = 1; k < tankmaxnum; k++)
                                        if (((*Pblue).tank[k].locatx == flagx) && (*Pblue).tank[k].locaty == flagy)
                                            {
												(*Pblue).tank[k].hp=(*Pblue).tank[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  蓝方坦克  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("它对蓝方第%d号坦克造成%d的伤害\n",k,attack);
										}
                                        break;
                                case -3:for(k = 1; k < cannonmaxnum; k++)
                                        if (((*Pblue).cannon[k].locatx == flagx) && (*Pblue).cannon[k].locaty == flagy)
                                            {
												(*Pblue).cannon[k].hp=(*Pblue).cannon[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  蓝方炮塔  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("它对蓝方第%d号坦克造成%d的伤害\n",k,attack);
										}
                                        break;
                                case -4:for(k = 1; k < jetmaxnum; k++)
                                        if (((*Pblue).jet[k].locatx == flagx) && (*Pblue).jet[k].locaty == flagy)
                                            {
												(*Pblue).jet[k].hp=(*Pblue).jet[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  蓝方飞机  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("它对蓝方第%d号坦克造成%d的伤害\n",k,attack);
										}
                                        break;
                                case -5:for(k = 1; k < helicoptermaxnum; k++)
                                        if (((*Pblue).helicopter[k].locatx == flagx) && (*Pblue).helicopter[k].locaty == flagy)
                                            {
												(*Pblue).helicopter[k].hp=(*Pblue).helicopter[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  蓝方飞机  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("它对蓝方第%d号坦克造成%d的伤害\n",k,attack);
										}
                                        break;
                                case -6:for(k = 1; k < defensemaxnum; k++)
                                        if (((*Pblue).defense[k].locatx == flagx) && (*Pblue).defense[k].locaty == flagy)
                                            {
												(*Pblue).defense[k].hp=(*Pblue).defense[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  蓝方飞机  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("它对蓝方第%d号坦克造成%d的伤害\n",k,attack);
										}
                                        break;
                                case -7:for(k = 1; k < fencemaxnum; k++)
                                        if (((*Pblue).fence[k].locatx == flagx) && (*Pblue).fence[k].locaty == flagy)
                                            {
												(*Pblue).fence[k].hp=(*Pblue).fence[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("对");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  蓝方飞机  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("造成了%d的伤害\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("它对蓝方第%d号坦克造成%d的伤害\n",k,attack);
										}
                                        break;
                            }
	
			}
       }
}

void Fresh(int map[][width], ARMYS *Pred, ARMYS *Pblue)
{
    int i,j,k,flag=0;
    for (i = 1; i < length-1; i++)
    for (j = 1; j < width-1; j++)
        if(map[i][j] != 0)
        {
            switch(map[i][j])
            {
                case 1:for(k = 1; k < soildermaxnum; k++)
                            {if (((*Pred).soilder[k].locatx == i) && (*Pred).soilder[k].locaty == j)
                                flag=k;}
                       if ((*Pred).soilder[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case 2:for(k = 1; k < tankmaxnum; k++)
                            {if (((*Pred).tank[k].locatx == i) && (*Pred).tank[k].locaty == j)
                                flag=k;}
                        if ((*Pred).tank[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case 3:for(k = 1; k < cannonmaxnum; k++)
                            {if (((*Pred).cannon[k].locatx == i) && (*Pred).cannon[k].locaty == j)
                                flag=k;}
                        if ((*Pred).cannon[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case 4:for(k = 1; k < jetmaxnum; k++)
                            {if (((*Pred).jet[k].locatx == i) && (*Pred).jet[k].locaty == j)
                                flag=k;}
                        if ((*Pred).jet[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case 5:for(k = 1; k < helicoptermaxnum; k++)
                            {if (((*Pred).helicopter[k].locatx == i) && (*Pred).helicopter[k].locaty == j)
                                flag=k;}
                        if ((*Pred).helicopter[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case 6:for(k = 1; k < defensemaxnum; k++)
                            {if (((*Pred).defense[k].locatx == i) && (*Pred).defense[k].locaty == j)
                                flag=k;}
                        if ((*Pred).defense[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case 7:for(k = 1; k < fencemaxnum; k++)
                            {if (((*Pred).fence[k].locatx == i) && (*Pred).fence[k].locaty == j)
                                flag=k;}
                        if ((*Pred).fence[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case -1:for(k = 1; k < soildermaxnum; k++)
                            {if (((*Pblue).soilder[k].locatx == i) && (*Pblue).soilder[k].locaty == j)
                                flag=k;}
                        if ((*Pblue).soilder[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case -2:for(k = 1; k < tankmaxnum; k++)
                            {if (((*Pblue).tank[k].locatx == i) && (*Pblue).tank[k].locaty == j)
                                flag=k;}
                        if ((*Pblue).tank[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case -3:for(k = 1; k < cannonmaxnum; k++)
                            {if (((*Pblue).cannon[k].locatx == i) && (*Pblue).cannon[k].locaty == j)
                                flag=k;}
                        if ((*Pblue).cannon[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case -4:for(k = 1; k < jetmaxnum; k++)
                            {if (((*Pblue).jet[k].locatx == i) && (*Pblue).jet[k].locaty == j)
                                flag=k;}
                        if ((*Pblue).jet[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case -5:for(k = 1; k < helicoptermaxnum; k++)
                            {if (((*Pblue).helicopter[k].locatx == i) && (*Pblue).helicopter[k].locaty == j)
                                flag=k;}
                        if ((*Pblue).helicopter[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case -6:for(k = 1; k < defensemaxnum; k++)
                            {if (((*Pblue).defense[k].locatx == i) && (*Pblue).defense[k].locaty == j)
                                flag=k;}
                        if ((*Pblue).defense[flag].hp <= 0)
                                map[i][j]=0;
                        break;
                case -7:for(k = 1; k < fencemaxnum; k++)
                            {if (((*Pblue).fence[k].locatx == i) && (*Pblue).fence[k].locaty == j)
                                flag=k;}
                        if ((*Pblue).fence[flag].hp <= 0)
                                map[i][j]=0;
                        break;
            }
        }
}


int Win(int map[][width], ARMYS red, ARMYS blue) 
{
	int i,j,Rflag=1,Bflag=1,
		Rcount,Bcount,
		endflag;
	
	Rcount=0;
	Bcount=0;
	endflag=0;
		
	for(i = 1; i < length-1; i++)
		for(j = 1; j < width-1; j++)
		{
			if (map[i][j]>0)
				Rcount++;/*计算红方单位数量*/ 
			if (map[i][j]>0)
				Bcount++;/*计算蓝方单位数量*/ 
			switch(map[i][j])
			{
				case 1:Rflag=0;break;
				case 2:Rflag=0;break;
				case 3:break; 
				case 4:Rflag=0;break;
				case 5:Rflag=0;break;
				case 6:break;
				case 7:break;
				
				case -1:Bflag=0;break;
				case -2:Bflag=0;break;
				case -3:break;
				case -4:Bflag=0;break;
				case -5:Bflag=0;break;
				case -6:break;
				case -7:break;
			}/*判断是否还有可移动单位*/ 
		}
	
	if ((Rflag) && (Bflag))
	{
		if ( Rcount > Bcount)
		{
			system("cls");
			Printmap(map,&red,&blue);
			goto_xy(55,20);
			printf("红方获胜！\n");
			endflag=1;
		}
		else if ( Rcount < Bcount)
		{
			system("cls");
			Printmap(map,&red,&blue);
			goto_xy(55,20);
			printf("蓝方获胜！\n");
			endflag=1;
		}
		else if (Rcount == Bcount)
		{
			system("cls");
			Printmap(map,&red,&blue);
			goto_xy(55,20);
			printf("平局\n");
			endflag=1;
		}
	}
	else if (Rflag)
	{
		system("cls");
		Printmap(map,&red,&blue);
		goto_xy(55,20);
		printf("蓝方获胜！\n");
		endflag=1;
	}
	else if (Bflag)
	{
		system("cls");
		Printmap(map,&red,&blue);
		goto_xy(55,20);
		printf("红方获胜！\n");
		endflag=1;
	}
	return endflag;
}

