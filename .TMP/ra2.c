#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<conio.h>

/*�˴�����������1����Ϊ�˺����������Դ�1��ʼ�����ڼ���*/
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
#define width 82/*ȥ����ͼ�߽磬��֤�����1��ʼ��80*/
#define kindnum 11
#define datanum 10

int timestamp=0;/*ʱ�����������ʱ��ʵ�ֹ��ٵȹ���*/
int attackable[kindnum+1][kindnum+1];/*���Բ�ͬ���ֵĿɹ�������,��attackable[2][3]��ʾ����Ϊ2�ı����Ƿ��ܹ�������Ϊ3�ı��֣�1Ϊ����0Ϊ�����ԡ����粽���򲻵��ɻ�*/

typedef struct unit
{
	int locatx;
	int locaty;/*����λ��*/
	int hp;/*����ֵ*/
	int att;/*attack��������*/
	int arr;/*arrange��������Χ*/
	int speed;/*�ƶ��ٶ�*/
	int cost;/*���*/
	int attspeed;/*�����ٶ�*/
}UNIT;

typedef struct armys
{
	UNIT soilder[soildermaxnum*2+1],/*��ͨʿ��*/
         tank[tankmaxnum*2+1],/*̹�˱���*/ 
         cannon[cannonmaxnum*2+1],/*���ڱ���*/ 
         jet[jetmaxnum*2+1],/*�ɻ�����*/
         helicopter[helicoptermaxnum*2+1],//��װֱ��������
		 defense[defensemaxnum*2+1],//���ձ��� 
		 fence[fencemaxnum*2+1],//դ������ 
		 walkcannon[walkcannonmaxnum*2+1],//�����ڱ���
		 mine[minemaxnum*2+1],//����
		 retank[retankmaxnum*2+1],//��̹�˲��� 
		 reair[reairmaxnum*2+1];//���վ����� 
		  
}ARMYS;/*ֱ�Ӷ�����ֻ��ͬ�ľ���*/



void goto_xy(int x,int y){ //��λ���λ�õ�ָ������
HANDLE hOut;
hOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos={x,y};
SetConsoleCursorPosition(hOut,pos);
}

void Printmap(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*��ӡ�Կ���ͼ�ĺ���*/

void Printmap2(int map[][width], int bug, int money, ARMYS red, ARMYS blue);/*����ӡ��ϸ��Ϣ��ͼ�ĺ���*/

void Start(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*��ʼ������*/ 

void Setforce(int map[][width], ARMYS red, ARMYS blue);/*�����������*/

void Move(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*�ƶ�����*/

void Attack(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*��������*/

void Fresh(int map[][width], ARMYS *Pred, ARMYS *Pblue);/*ˢ�º���*/

int Win(int map[][width], ARMYS red, ARMYS blue);/*�ж�����*/ 

void End(int map[][width], ARMYS red, ARMYS blue);


int main()
{
	int map[length][width],end=0;
	ARMYS red,blue,*Pred,*Pblue;
    system("color 09");
	Start(map,&red,&blue);

    while (!end)
    {
	/*printf("�췽�ĵ�һ��������������£�\n");
    printf("Ѫ��:%d  ������:%d  ������Χ:%d  ����:%d  λ��:(%d,%d)\n",red.soilder[1].hp,
                                                    	red.soilder[1].att,
                                                      	red.soilder[1].arr,
                                                      	red.soilder[1].speed,
                                                      	red.soilder[1].locatx,
                                                      	red.soilder[1].locaty);
    printf("������̹�˵��������£�\n");
    printf("Ѫ��:%d  ������:%d  ������Χ:%d  ����:%d  λ��:(%d,%d)\n",blue.tank[1].hp,
                                                      	blue.tank[1].att,
                                                      	blue.tank[1].arr,
                                                      	blue.tank[1].speed,
                                                      	blue.tank[1].locatx,
                                                      	blue.tank[1].locaty);*/
        system("cls");
        timestamp++;/*ʱ�������*/
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
        data[datanum],/*�����Ĵ��ļ��ж�ȡ������*/
        k[2][kindnum];/*����ȷ�����ֵ��±꣬���������·�λ�ó�ʼ��*/
	FILE *fpin;
	char str[5];
	if ((fpin=fopen("data1.txt","r")) == NULL)
    {
        printf("�޷����ļ���ϵͳ����ر�\n");
		exit(0); 
    }
    

	/*����Ϊ��������ĳ�ʼ��*/
    
	fscanf(fpin,"������%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
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
    }/*ʿ�����ֵ�����¼��*/ 

    fscanf(fpin,"̹�ˣ�%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
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
    }/*̹�˱��ֵ�¼��*/
    
    fscanf(fpin,"���ڣ�%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
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
    }/*���ڱ��ֵ�¼��*/
    
    fscanf(fpin,"�ɻ���%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
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
    }/*�ɻ����ֵ�¼��*/
    
    fscanf(fpin,"��ֱ��%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
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
    }/*��ֱ���ֵ�¼��*/
    
    fscanf(fpin,"���գ�%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
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
    }/*��������¼��*/
    
    fscanf(fpin,"դ����%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
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
    }/*դ����¼��*/

	fscanf(fpin,"���ף�%d,%d,%d,%d,%d\n",&data[0],&data[1],&data[2],&data[3],&data[4]);
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
    }/*���׵�¼��*/

    fclose(fpin);
    /*����Ϊ��������ĳ�ʼ��*/
	
	//����Ϊ��Լ������Χ�ĳ�ʼ��
	for (i = 1; i <= kindnum; i++)
		for (j = 1; j <= kindnum; j++)
			attackable[i][j]=1;//���ǵ��ɹ����ıȽ϶���ȫ����ʼ���ɿɹ���
			
	for (i = 1; i <= kindnum; i++)//�ɻ���ܵ��湥�� 
		if ((i == 4) || (i == 5) || (i == 6) || (i == 11)) 
			attackable[i][4]=1;
		else  attackable[i][4]=0;
	
	for (i = 1; i <= kindnum; i++)//��ֱ��ܵ��湥�� 
		if ((i == 4) || (i == 5) || (i == 6) || (i == 11)) 
			attackable[i][5]=1;
		else  attackable[i][5]=0;
		
	for (i = 1; i <= kindnum; i++)//ֻ�в������ܶԵ�������˺� 
		if  (i == 1) 
			attackable[i][9]=1;
		else  attackable[i][9]=0;
	
	
	/*����Ϊ��ͼ�ĳ�����ʼ��*/
	for(i = 0; i < length; i++)
		for(j = 0; j < width; j++)
			map[i][j]=0;

	Setforce(map,(*Pred),(*Pblue));/*�������*/

	for(i = 1; i <= 10; i++)
		map[i][58]=-7;
	for(i = 30; i <=40; i++) 
		map[i][58]=-7;//����դ�� 
	
	for(i = 14; i<=23; i++)
	{
		map[i][54]=-2;
		map[i][55]=-2;
	}//̹��սȺ 
	
	for(i = 4; i <= 7; i++)
		for(j = 61; j <= 63; j++)
		map[i][j]=-4;
		
	for(i = 31; i <= 34; i++)
		for(j = 61; j <= 63; j++)
		map[i][j]=-4;//�ɻ�Ⱥ
		
	for(i = 1; i <= 9; i=i+2)
		map[i][60]=-3;
	for(i = 31; i <= 39; i=i+2)
		map[i][60]=-3;//������	 
		
		
	
    /*����Ϊ��ͼ�ĳ�ʼ��*/


    /*����Ϊ���Դ�ӡ���� 
    printf("�췽�Ĵ�����������£�\n");
    printf("Ѫ��:%d  ������:%d  ������Χ:%d  ����:%d\n",(*Pred).soilder[1].hp,
                                                      (*Pred).soilder[1].att,
                                                      (*Pred).soilder[1].arr,
                                                      (*Pred).soilder[1].speed);
    printf("������̹�˵��������£�\n");
    printf("Ѫ��:%d  ������:%d  ������Χ:%d  ����:%d\n",(*Pblue).tank[1].hp,
                                                      (*Pblue).tank[1].att,
                                                      (*Pblue).tank[1].arr,
                                                      (*Pblue).tank[1].speed);
	printf("�췽�Ļ��ڵ��������£�\n");
    printf("Ѫ��:%d  ������:%d  ������Χ:%d  ����:%d\n",(*Pred).cannon[1].hp,
                                                      (*Pred).cannon[1].att,
                                                      (*Pred).cannon[1].arr,
                                                      (*Pred).cannon[1].speed);
	printf("�����ķɻ����������£�\n");
    printf("Ѫ��:%d  ������:%d  ������Χ:%d  ����:%d\n",(*Pred).jet[1].hp,
                                                      (*Pred).jet[1].att,
                                                      (*Pred).jet[1].arr,
                                                      (*Pred).jet[1].speed);                                           
    */


	/*�����ǳ�ʼ���ı���λ��¼��*/
	for(i = 0; i < 2; i++)
        for(j = 0; j < kindnum+1; j++)
            k[i][j]=0;

    for(i = 1; i < length-1; i++)
        for(j = 1; j < width-1; j++)
            {
                switch(map[i][j])/*����k�ĵ�һ���±��ʾ����������0Ϊ�죬1Ϊ�����ڶ����±��ʾ���֣�1Ϊ������2Ϊ̹��*/
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

	/*����Ϊ��ʼ���ı���λ��¼��*/

    printf("\n");
}

void Setforce(int map[][width], ARMYS red, ARMYS blue)
{
	int i,j,key,half, 
		flag,/*���ֵı�־*/
		x,y,/*Ҫ���õ�����*/
		m,n,/*��һ���ı������*/
		out=1,/*�ж��Ƿ��˳�*/
		money,/*���еĽ��*/ 
		pay;/*����*/
	
	half=(width-2)/2;
	printf("��������е��ܽ���Ӧ��Ϸ�Ѷȣ�30000����Ϊ���ѣ�30000����Ϊ�򵥣���");
	scanf("%d",&money);
	printf("\n"); 
	
	/*��ʼ��*/
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
			case 'w':{m=x-1;n=y;/*����Wʱ�ķ�Ӧ*/
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
			case 'a':{m=x;n=y-1;/*����Aʱ�ķ�Ӧ*/ 
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
			case 's':{m=x+1;n=y;/*����Sʱ�ķ�Ӧ*/ 
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
			case 'd': {m=x;n=y+1;/*����Dʱ�ķ�Ӧ*/ 
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
			case 13:{switch (flag)/*���»س��ķ�Ӧ*/
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
			case 27:{out=0;/*����Esc�ķ�Ӧ*/
				 map[x][y]=0;
				 system("cls");
				 Printmap2(map,3,money,red,blue);
				 break;
			}
		}
		
	}
	printf("������㲿��췽�����յ�ͼ\n");
	getchar();
	getchar();/*����һЩbug���»�������������Զ�дһ��getchar*/
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
	
	printf("-----------------------------------------------------�����Կ���ͼ-------------------------------------------------------\n");
	printf("                                                                                                                                                          ˫����ƴ��ϸ������\n");




	/*����Ϊ��ӡ������������*/
	printf("                    00000000011111111112222222222333333333344444444445555555555666666666677777777778\n");
	printf("                    12345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
    /*����Ϊ��ӡ������������*/


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
			else switch(map[i][j])/*ͨ�����������ж�˫��������ͬ*/
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


    /*������ͳ�Ƴ��Ϻ������������*/
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

            switch(map[i][j])/*ͳ����Ѫ���ĺ���*/
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
	printf("�����Ǻ�����������ϸ���ݣ�");
	goto_xy(120,41);
    printf("�췽                          |����");
    goto_xy(120,42);
    printf("����      ����      ��Ѫ��    |����      ����      ��Ѫ��    ");
    goto_xy(120,43);
    printf("ʿ��      %-10d%-10d|ʿ��      %-10d%-10d\n",Rsoildernum,Rsoilderhp,Bsoildernum,Bsoilderhp);
    goto_xy(120,44);
    printf("̹��      %-10d%-10d|̹��      %-10d%-10d\n",Rtanknum,Rtankhp,Btanknum,Btankhp);
    goto_xy(120,45);
    printf("����      %-10d%-10d|����      %-10d%-10d\n",Rcannonnum,Rcannonhp,Bcannonnum,Bcannonhp);
    goto_xy(120,46);
    printf("�ɻ�      %-10d%-10d|�ɻ�      %-10d%-10d\n",Rjetnum,Rjethp,Bjetnum,Bjethp);
    goto_xy(120,47);
    printf("��ֱ      %-10d%-10d|��ֱ      %-10d%-10d\n",Rhelicopternum,Rhelicopterhp,Bhelicopternum,Bhelicopterhp);
    goto_xy(120,48);
    printf("����      %-10d%-10d|����      %-10d%-10d\n",Rdefensenum,Rdefensehp,Bdefensenum,Bdefensehp);
    goto_xy(120,49);
    printf("դ��      %-10d%-10d|դ��      %-10d%-10d\n",Rfencenum,Rfencehp,Bfencenum,Bfencehp);
    goto_xy(120,50);
    //printf("����      %-10d%-10d|����      %-10d%-10d\n",Rfencenum,Rfencehp,Bfencenum,Bfencehp);
}

void Printmap2(int map[][width], int bug, int money, ARMYS red, ARMYS blue)
{
	int i,j,k,half;
	half=(width-2)/2;
	/*����Ϊ�ڲ�����������г��ֵĴ�ӡ��ͼ*/
	/*������Ϊ�췽����ֻ�ܲ��ú췽һ�볡��*/
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	printf("\n"); 
	printf("-------------------------------------------------սǰ�����ͼ-----------------------------------------------------\n");
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
			else if (j >= half) printf("X");/*��ɫ��������ʾX��ʾ���ɷ���*/
			else switch(map[i][j])/*ͨ�����������ж�˫��������ͬ*/
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
	printf("                                                         ע��X��ʾ���ڵ�ס���������أ����������ʱ����Խ����������\n");
	printf("\n");
	printf("\n");
	if (bug != 3)
	{
		printf("���ֹ���˵�                                           �������Ϊ����%d\n",money);
		printf("--------------------------------------------------------------------------\n"); 
		printf("��1������\t\t��%d\t\t\t��7��դ��\t\t��%d\n",red.soilder[1].cost,red.fence[1].cost); 
		printf("��2��̹��\t\t��%d\t\t\t��8��������\t\t��%d\n",red.tank[1].cost,red.fence[1].cost);
		printf("��3������\t\t��%d\t\t\t��9������\t\t��%d\n",red.cannon[1].cost,red.fence[1].cost);
		printf("��4���ɻ�\t\t��%d\t\t\t��0����̹�˲���\t\t��%d\n",red.jet[1].cost,red.fence[1].cost);
		printf("��5����ֱ\t\t��%d\t\t\t��-�����ղ���\t\t��%d\n",red.helicopter[1].cost,red.defense[1].cost);
		printf("��6��������\t\t��%d\n",red.defense[1].cost);
		printf("\n");
		printf("��W�������ƶ����   ��S�������ƶ����   ��A�������ƶ����   ��D�������ƶ����\n");
		printf("��ESC��ȷ�ϲ���      ��Enter��ȷ�Ϸ��ñ���\n");
	}
	
	
	/*bug�ж���˵��*/
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	if(bug == 1) printf("���õ�λ��Խ����\n");
	else if (bug == 2) printf("���õ�λ���б�����\n");
	else if (bug == 4) printf("�������㣡\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
}


void Move(int map[][width], ARMYS *Pred, ARMYS *Pblue)
{
    int i,j,k,
        step,temp,
        flag[length][width];
    /*kΪ���ֵ�λ���±��¼����*/


    /*��־����ĳ�ʼ��*/
    for(i = 1; i < length-1; i++)
        for(j = 1; j < width-1; j++)
        	flag[i][j]=0;

    /*����ʽ�����ƶ�*/
	for(i = 1; i < length-1; i++)
        for(j = 1; j < width-1; j++)
        {
            if (map[i][j]>0 && flag[i][j]!=1)/*�ж�Ϊ�췽�����Ҳ����ƶ����ı��������һ������ƶ�*/
            {
                switch(map[i][j])
                {
                    case 1:{step=(*Pred).soilder[1].speed;
                            if (j >= 40) step=-step;
							for(k = 1; k < soildermaxnum; k++)
                                if (((*Pred).soilder[k].locatx == i) && (*Pred).soilder[k].locaty == j)
                                if (map[i][j+step]==0)/*�췽�����ƶ��������ƶ�*/ 
                				{
                    				map[i][j+step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j+step]=1;
                    				(*Pred).soilder[k].locaty+=step;
                				}
								else if (map[i-step][j]==0)/*����������*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pred).soilder[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*����������*/ 
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
                                if (map[i][j+step]==0)/*�췽�����ƶ��������ƶ�*/ 
                				{
                    				map[i][j+step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j+step]=1;
                    				(*Pred).tank[k].locaty+=step;
                				}
								else if (map[i-step][j]==0)/*����������*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pred).tank[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*����������*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pred).tank[k].locatx+=step;
                				}
                            break;
                    }
                    case 3:{step=(*Pred).cannon[1].speed;/*�����ƶ���λ*/ 
                            for(k = 1; k < cannonmaxnum; k++)
                                if (((*Pred).cannon[k].locatx == i) && (*Pred).cannon[k].locaty == j)
                                    (*Pred).cannon[k].locaty+=step;
                            break;
                    }
                    case 4:{step=(*Pred).jet[1].speed;
                    		if (j >= 40) step=-step;
                            for(k = 1; k < jetmaxnum; k++)
                                if (((*Pred).jet[k].locatx == i) && (*Pred).jet[k].locaty == j)
                                if (map[i][j+step]==0)/*�췽�����ƶ��������ƶ�*/ 
                				{
                    				map[i][j+step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j+step]=1;
                    				(*Pred).jet[k].locaty+=step;
                				}
								else if (map[i-step][j]==0)/*����������*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pred).jet[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*����������*/ 
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
                                if (map[i][j+step]==0)/*�췽�����ƶ��������ƶ�*/ 
                				{
                    				map[i][j+step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j+step]=1;
                    				(*Pred).helicopter[k].locaty+=step;
                				}
								else if (map[i-step][j]==0)/*����������*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pred).helicopter[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*����������*/ 
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
            else if (map[i][j]<0 && flag[i][j]!=1)/*�ж�Ϊ���������Ҳ����ƶ����ı���������������ƶ��ƶ�*/
            {
                switch(map[i][j])
                {
                    case -1:{step=(*Pblue).soilder[1].speed;
                    		if (j <= 40) step=-step;
                            for(k = 1; k < soildermaxnum; k++)
                                if (((*Pblue).soilder[k].locatx == i) && (*Pblue).soilder[k].locaty == j)
                                if (map[i][j-step]==0)/*���������ƶ��������ƶ�*/ 
                				{
                    				map[i][j-step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j-step]=1;
                    				(*Pblue).soilder[k].locaty-=step;
                				}
								else if (map[i-step][j]==0)/*����������*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pblue).soilder[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*����������*/ 
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
                                if (map[i][j-step]==0)/*���������ƶ��������ƶ�*/ 
                				{
                    				map[i][j-step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j-step]=1;
                    				(*Pblue).tank[k].locaty-=step;
                				}
								else if (map[i-step][j]==0)/*����������*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pblue).tank[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*����������*/ 
                				{
                    				map[i+step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i+step][j]=1;
                    				(*Pblue).tank[k].locatx+=step;
                				}
                            break;
                    }
                    case -3:{step=(*Pblue).cannon[1].speed;/*�����ƶ���λ*/
                            for(k = 1; k < cannonmaxnum; k++)
                                if (((*Pblue).cannon[k].locatx == i) && (*Pblue).cannon[k].locaty == j)
                                    (*Pblue).cannon[k].locaty-=step;
                            break;
                    }
                    case -4:{step=(*Pblue).jet[1].speed;
                    		if (j <= 40) step=-step;
                            for(k = 1; k < jetmaxnum; k++)
                                if (((*Pblue).jet[k].locatx == i) && (*Pblue).jet[k].locaty == j)
                                if (map[i][j-step]==0)/*���������ƶ��������ƶ�*/ 
                				{
                    				map[i][j-step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j-step]=1;
                    				(*Pblue).jet[k].locaty-=step;
                				}
								else if (map[i-step][j]==0)/*����������*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pblue).jet[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*����������*/ 
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
                                if (map[i][j-step]==0)/*���������ƶ��������ƶ�*/ 
                				{
                    				map[i][j-step]=map[i][j];
                    				map[i][j]=0;
                    				flag[i][j-step]=1;
                    				(*Pblue).helicopter[k].locaty-=step;
                				}
								else if (map[i-step][j]==0)/*����������*/ 
                				{
                    				map[i-step][j]=map[i][j];
                    				map[i][j]=0;
                    				flag[i-step][j]=1;
                    				(*Pblue).helicopter[k].locatx-=step;
                				}
								else if (map[i+step][j]==0)/*����������*/ 
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
    int attack;/*�Ĵ�ñ��ֵĹ�����*/ 
    int Rline,Bline;
    const int Rcolumn=120;
    const int Bcolumn=165;
    
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Rline=7;Bline=7;
    for(i = 1; i <= length-2; i++)
        for(j = 1; j <= width-2; j++)
        if(map[i][j] != 0)
        {
             switch(map[i][j]){/*��ȡ������������Χ�Ȳ���*/
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
			//printf("��ȡ������Ϊ��������Χ��%d\t��������%d\n",range,attack);
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
            /*����Ϊ��ֹ����Խ��*/
            nearest=2*(range*2)*(range*2);/*����Ϊ��󹥻���Χ*/
            flagx=0;
            flagy=0;
            for(m = up; m <= down; m++)
                for(n = left; n <= right; n++)
                    if (map[m][n]*map[i][j] < 0)/*Ѱ�ҹ�����Χ������ĵз�Ŀ�겢��¼*/
                        {
                            test=(m-i)*(m-i)+(n-j)*(n-j);
                            if (test <= nearest)
                            {
                                nearest=test;
                                flagx=m;
                                flagy=n;
                            }
                        }
                        //printf("������ĵз���λ������Ϊ��(%d,%d)\n",flagx,flagy);
            if (((flagx*flagy) != 0) && (attackable[abs(map[i][j])][abs(map[flagx][flagy])]))/*�ҵ�����Ŀ��,���ܶԸ�Ŀ����й���*/ 
            {
				switch(map[i][j])
				{
					case 1:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
							goto_xy(Rcolumn,Rline);
							printf("�췽����  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break;
					case 2:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
							goto_xy(Rcolumn,Rline);
					   		printf("�췽̹��  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break;
					case 3:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("�췽����  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break;
					case 4:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("�췽�ɻ�  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break; 
					case 5:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("�췽��ֱ  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break; 
					case 6:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("�췽����  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break;
					case 7:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					   		goto_xy(Rcolumn,Rline);
							printf("�췽դ��  ");
					   		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
					   		break; 
					case -1:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("��������  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			    	case -2:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("����̹��  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
					case -3:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("��������  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
					case -4:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("�����ɻ�  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			    	case -5:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("������ֱ  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			    	case -6:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("��������  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			    	case -7:SetConsoleTextAttribute(handle,FOREGROUND_BLUE);
					 		goto_xy(Bcolumn,Bline);
							printf("����դ��  ");
			    			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			    			break;
			 	}
				switch(map[flagx][flagy])/*����ѡ�е�Ŀ����й���*/
                             {
                                case 1:for(k = 1; k < soildermaxnum; k++)
                                        if (((*Pred).soilder[k].locatx == flagx) && (*Pred).soilder[k].locaty == flagy)
                                            {
												(*Pred).soilder[k].hp=(*Pred).soilder[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  �췽����  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++; 
												//printf("���Ժ췽��%d��ʿ�����%d���˺�\n",k,attack);
                                        	}
                                        break;
                                case 2:for(k = 1; k < tankmaxnum; k++)
                                        if (((*Pred).tank[k].locatx == flagx) && (*Pred).tank[k].locaty == flagy)
                                            {
												(*Pred).tank[k].hp=(*Pred).tank[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  �췽̹��  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("���Ժ췽��%d��̹�����%d���˺�\n",k,attack);
											}
                                        break;
                                case 3:for(k = 1; k < cannonmaxnum; k++)
                                        if (((*Pred).cannon[k].locatx == flagx) && (*Pred).cannon[k].locaty == flagy)
                                            {
												(*Pred).cannon[k].hp=(*Pred).cannon[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  �췽����  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("���Ժ췽��%d�Ż������%d���˺�\n",k,attack);
											}
                                        break;
                                case 4:for(k = 1; k < jetmaxnum; k++)
                                        if (((*Pred).jet[k].locatx == flagx) && (*Pred).jet[k].locaty == flagy)
                                            {
												(*Pred).jet[k].hp=(*Pred).jet[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  �췽�ɻ�  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("���Ժ췽��%d�Ż������%d���˺�\n",k,attack);
											}
                                        break;
                                case 5:for(k = 1; k < helicoptermaxnum; k++)
                                        if (((*Pred).helicopter[k].locatx == flagx) && (*Pred).helicopter[k].locaty == flagy)
                                            {
												(*Pred).helicopter[k].hp=(*Pred).helicopter[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  �췽��ֱ  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("���Ժ췽��%d�Ż������%d���˺�\n",k,attack);
											}
                                        break;
                                case 6:for(k = 1; k < defensemaxnum; k++)
                                        if (((*Pred).defense[k].locatx == flagx) && (*Pred).defense[k].locaty == flagy)
                                            {
												(*Pred).defense[k].hp=(*Pred).defense[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  �췽��ֱ  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("���Ժ췽��%d�Ż������%d���˺�\n",k,attack);
											}
                                        break;
                                case 7:for(k = 1; k < fencemaxnum; k++)
                                        if (((*Pred).fence[k].locatx == flagx) && (*Pred).fence[k].locaty == flagy)
                                            {
												(*Pred).fence[k].hp=(*Pred).fence[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED); 
												printf("  �췽��ֱ  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Bline++;
												//printf("���Ժ췽��%d�Ż������%d���˺�\n",k,attack);
											}
                                        break;
                                case -1:for(k = 1; k < soildermaxnum; k++)
                                        if (((*Pblue).soilder[k].locatx == flagx) && (*Pblue).soilder[k].locaty == flagy)
                                            {
												(*Pblue).soilder[k].hp=(*Pblue).soilder[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  ��������  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("����������%d��ʿ�����%d���˺�\n",k,attack);
											} 
                                        break;
                                case -2:for(k = 1; k < tankmaxnum; k++)
                                        if (((*Pblue).tank[k].locatx == flagx) && (*Pblue).tank[k].locaty == flagy)
                                            {
												(*Pblue).tank[k].hp=(*Pblue).tank[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  ����̹��  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("����������%d��̹�����%d���˺�\n",k,attack);
										}
                                        break;
                                case -3:for(k = 1; k < cannonmaxnum; k++)
                                        if (((*Pblue).cannon[k].locatx == flagx) && (*Pblue).cannon[k].locaty == flagy)
                                            {
												(*Pblue).cannon[k].hp=(*Pblue).cannon[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  ��������  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("����������%d��̹�����%d���˺�\n",k,attack);
										}
                                        break;
                                case -4:for(k = 1; k < jetmaxnum; k++)
                                        if (((*Pblue).jet[k].locatx == flagx) && (*Pblue).jet[k].locaty == flagy)
                                            {
												(*Pblue).jet[k].hp=(*Pblue).jet[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  �����ɻ�  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("����������%d��̹�����%d���˺�\n",k,attack);
										}
                                        break;
                                case -5:for(k = 1; k < helicoptermaxnum; k++)
                                        if (((*Pblue).helicopter[k].locatx == flagx) && (*Pblue).helicopter[k].locaty == flagy)
                                            {
												(*Pblue).helicopter[k].hp=(*Pblue).helicopter[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  �����ɻ�  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("����������%d��̹�����%d���˺�\n",k,attack);
										}
                                        break;
                                case -6:for(k = 1; k < defensemaxnum; k++)
                                        if (((*Pblue).defense[k].locatx == flagx) && (*Pblue).defense[k].locaty == flagy)
                                            {
												(*Pblue).defense[k].hp=(*Pblue).defense[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  �����ɻ�  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("����������%d��̹�����%d���˺�\n",k,attack);
										}
                                        break;
                                case -7:for(k = 1; k < fencemaxnum; k++)
                                        if (((*Pblue).fence[k].locatx == flagx) && (*Pblue).fence[k].locaty == flagy)
                                            {
												(*Pblue).fence[k].hp=(*Pblue).fence[k].hp-attack;
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("��");
												SetConsoleTextAttribute(handle, FOREGROUND_BLUE); 
												printf("  �����ɻ�  ");
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
												printf("�����%d���˺�\n",attack);
												SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
												Rline++;
												//printf("����������%d��̹�����%d���˺�\n",k,attack);
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
				Rcount++;/*����췽��λ����*/ 
			if (map[i][j]>0)
				Bcount++;/*����������λ����*/ 
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
			}/*�ж��Ƿ��п��ƶ���λ*/ 
		}
	
	if ((Rflag) && (Bflag))
	{
		if ( Rcount > Bcount)
		{
			system("cls");
			Printmap(map,&red,&blue);
			goto_xy(55,20);
			printf("�췽��ʤ��\n");
			endflag=1;
		}
		else if ( Rcount < Bcount)
		{
			system("cls");
			Printmap(map,&red,&blue);
			goto_xy(55,20);
			printf("������ʤ��\n");
			endflag=1;
		}
		else if (Rcount == Bcount)
		{
			system("cls");
			Printmap(map,&red,&blue);
			goto_xy(55,20);
			printf("ƽ��\n");
			endflag=1;
		}
	}
	else if (Rflag)
	{
		system("cls");
		Printmap(map,&red,&blue);
		goto_xy(55,20);
		printf("������ʤ��\n");
		endflag=1;
	}
	else if (Bflag)
	{
		system("cls");
		Printmap(map,&red,&blue);
		goto_xy(55,20);
		printf("�췽��ʤ��\n");
		endflag=1;
	}
	return endflag;
}

