#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "getch.h"

#define UP 65 
#define DOWN 66
#define RIGHT 67
#define LEFT 68

int Title();
void UI(int *pst);
void Map(int *pst);
int Boss(int *pst);
int randsys(int num1, int num2);
void Chat(char ment[]);

int main(void)
{
	//0 hp, 1 maxhp, 2 +atk, 3 boss1, 4 boss2, 5 boss3, 6 물약, 7 층, 8 도망
	int status[9]={500,500,0,1500,2500,7777,0,1,3};
	int menu;

	srand(time(NULL));

	while(1)
	{
		menu=Title();

		if(menu==49)
		{
			Map(status);
			
			if(status[5]<=0)
			{
				system("clear");
				printf("\n\n\n\n\n디아복로 : ");
				Chat("아직 끝났다고 생각하지 마라.....!!!\n           다음 프로젝트가 널 기다릴테니...후후후...\n");							
			}
			else if(status[0]<=0)
			{
				system("clear");
				printf("\n\n\n\n\n");
				printf("	           ■▒    ▒▒▒▒▒▒▒          ▒■▒▒▒▒■▒▒                        \n");
				printf("	          ▒■▒▒▒▒■▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒■▒▒▒▒■▒▒▒▒▒                   \n");
				printf("	        ▒▒▒■▒▒▒▒■▒▒▒▒▒▒■▒▒▒▒▒▒▒■▒▒▒■▒▒▒▒■▒▒▒▒▒▒▒                  \n ");
				printf("	       ▒▒▒▒■▒▒▒▒■▒▒▒▒▒▒■▒▒▒■▒▒▒■▒▒▒■▒▒▒▒■▒▒▒▒▒▒▒▒                \n");
				printf("	      ▒▒▒▒▒■▒▒▒▒■▒▒▒▒▒■■■■■■■■■■■■■■■▒▒▒■▒▒■▒▒▒▒                \n");
				printf("	     ▒▒▒▒▒▒■■■■■■■■▒■■               ■■▒■▒▒■▒▒▒▒▒▒                \n");
				printf("	     ▒▒▒▒▒▒■       ■                   ■■▒▒■▒▒▒▒▒               \n");
				printf("	    ▒▒▒▒▒▒■         ■                    ■▒■▒▒■▒▒▒▒           \n");
				printf("	    ▒▒▒▒▒■           ■                   ■▒■▒▒■▒▒▒▒           \n");
				printf("	    ▒▒▒▒▒■           ■                   ■▒■▒▒■▒▒▒▒▒             \n");
				printf("	     ▒▒▒▒■           ■                   ■▒■▒▒■▒▒▒▒▒▒▒            \n");
				printf("	     ▒▒▒▒■           ■                  ■▒▒■▒▒■▒▒▒▒▒▒▒          \n");
				printf("	     ▒▒▒▒▒■         ■     ■■■■         ■▒▒▒■▒▒■▒▒▒▒▒▒▒▒           \n");
				printf("	      ▒▒▒▒■■       ■ ■   ■   ■■■       ■■■■■■■■■▒▒▒▒▒             \n");
				printf("	      ▒▒▒▒■ ■■■■■■■  ■   ■   ■  ■     ■         ■▒▒▒▒▒         \n");
				printf("	      ▒▒▒■   ■      ■   ■    ■■■       ■■■■■■■■■■▒▒▒▒            \n");
				printf("	     ▒▒▒▒■   ■      ■   ■      ■                 ■▒▒▒      \n");
				printf("	     ▒▒▒▒■   ■     ■    ■       ■■■■■■■■■■■■■■■■■▒▒▒▒▒▒     \n");
				printf("	    ▒▒■■■    ■   ■■     ■                              \n");
				printf("	    ▒■      ■   ■      ■                      \n");
				printf("	    ▒▒■■■■■■     ■■■■■■                              \n\n");
				Chat("애송이.....강해져서 돌아와라.....!\n");
				
			}
			return 0;
		}
		else if(menu==50)
		{
			break;
		}
		else
		{
			continue;
		}
	}
	return 0;
}

void Map(int *pst)
{
	int i, j;
	int ch, rs, temp, ct=0, mct=0;
	int bsx=1, bsy=1;
	int px=5, py=8;
	int hpx=0,hpy=0;
	int mhpx=0,mhpy=0;
	int atkx=0,atky=0;
	int trx=0,try=0;
	int map[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}};

	map[py][px]=2;				//캐릭터와 겹치지 않도록 미리 배열에 캐릭터 좌표소환
	
	while(1)//보스 소환 좌표
	{
		bsx=randsys(1,8);
		bsy=randsys(1,8);
		if(map[bsy][bsx]==0)	
		{
			map[bsy][bsx]=95;
			break;
		}
	}

	while(ct<10)//회복물약 소환 좌표
	{
		hpx=randsys(1,8);
		hpy=randsys(1,8);
		if(map[hpy][hpx]==0 || (hpy==0 && hpx==0))	
		{
			map[hpy][hpx]=99;
			ct++;
		}
	}
	ct=0;

	mct=randsys(1,3);
	while(ct<mct)//체력물약 소환 좌표
	{
		mhpx=randsys(1,8);
		mhpy=randsys(1,8);
		if(map[mhpy][mhpx]==0 || (mhpy==0 && mhpx==0))	
		{
			map[mhpy][mhpx]=98;
			ct++;
		}

	}
	ct=0;
	mct=0;

	mct=randsys(3,5);
	while(ct<mct)//공격물약 소환 좌표
	{
		atkx=randsys(1,8);
		atky=randsys(1,8);
		if(map[atky][atkx]==0 || atky==0 || atkx==0)	
		{
			map[atky][atkx]=97;
			ct++;
		}

	}
	ct=0;
	mct=0;

	mct=randsys(3,10);
	while(ct<mct)//함정 소환 좌표
	{
		trx=randsys(1,8);
		try=randsys(1,8);
		if(map[try][trx]==0 || (try==0 && trx==0))	
		{
			map[try][trx]=96;
			ct++;
		}
	}

	while(1)	//맵그리기
	{
		system("clear");
		
		map[py][px]=2;
		map[bsy][bsx]=95;
		

		for(i=0; i<10; i++)
		{
			for(j=0; j<10; j++)
			{
				if(map[i][j]==0)
				{
					printf("  ");
				}
				if(map[i][j]==1)
				{
					printf("▒▒");
				}
				if(map[i][j]==2)
				{
					printf("ਊ ");
				}
				if(map[i][j]==95)
				{
					printf("  ");
				}
				if(map[i][j]==99)
				{
					printf("\033[1;31m∈∋\033[1;0m");
				}
				if(map[i][j]==98)
				{
					printf("\033[1;32m∈∋\033[1;0m");
				}
				if(map[i][j]==97)
				{
					printf("\033[1;34m∈∋\033[1;0m");
				}
				if(map[i][j]==96)
				{
					printf("  ");
				}
			}
			printf("\n");
		}


		UI(pst);
		
		if(pst[3]>0 || pst[4]>0 || pst[5]>0)	//함수를 빠져나올때 걸리지 않도록 하기위한 조건
		{
			ch = getch();
		}

		switch(ch)
		{
			case UP :
				{
					if(map[py-1][px]==0 || (map[py-1][px]>=90 && map[py-1][px]<=99))
					{
						temp=map[py-1][px];
						map[py][px]=0;
						py--;
					}

					break;
				}

			case DOWN :
				{
					if(map[py+1][px]==0 || (map[py+1][px]>=90 && map[py+1][px]<=99))
					{
						temp=map[py+1][px];
						map[py][px]=0;
						py++; 
					}
					break;
				}

			case RIGHT :
				{
					if(map[py][px+1]==0 || (map[py][px+1]>=90 && map[py][px+1]<=99))
					{
						temp=map[py][px+1];
						map[py][px]=0;
						px++;
					}
					break;
				}

			case LEFT :
				{
					if(map[py][px-1]==0 || (map[py][px-1]>=90 && map[py][px-1]<=99))
					{
						temp=map[py][px-1];
						map[py][px]=0;
						px--;
					}
					break;
				}
			default :
				{
					continue;
				}
		}//switch

		if(temp!=0)
		{
			if(temp==99)
			{//체력회복 물약
				pst[6]+=1;
				temp=0;
			}
			else if(temp==98)
			{//maxhp 영구증가
				pst[1]+=randsys(10,40);
				temp=0;
			}
			else if(temp==97)
			{//atk 영구증가
				pst[2]+=randsys(20,80);
				temp=0;
			}
			else if(temp==96)
			{//함정
				pst[0]-=10;
				temp=0;
			}
			else if(temp==95)
			{//보스 출현
				rs=Boss(pst);
				while(1)
				{
					if(rs==0)//캐릭터 사망 혹은 마지막 보스 사망
					{
						
						return;
					}
					else if(rs>=1 && rs<=30)//도망
					{	
						if(pst[8]>0)	//도망카운트가 있을때의 조건
						{
							while(1)//보스 재소환 좌표
							{
								bsx=randsys(1,8);
								bsy=randsys(1,8);

								if(map[bsy][bsx]==0)	
								{
									map[bsy][bsx]=95;
									break;
								}
							}
							pst[8]-=1;

							sleep(1);

							break;
						}
						else
						{
							system("clear");
							Chat("더이상 도망갈수 없다\n");

							rs=Boss(pst);
						}
					}
					else if(rs>30 && rs<=100)	//도망실패시 체력-5
					{
						system("clear");
						Chat("도망 실패\n");
						pst[0]-=5;

						rs=Boss(pst);
					}
				}
				if(pst[5]<=0)
				{
					break;
				}
			}

		}
	}//while
}

void UI(int *pst)
{
	int i;
	printf("   HP : %d / %d\n", pst[0], pst[1]);
	for(i=0; i<pst[0]/(pst[1]/20); i++)
	{
		printf("\033[1;41m \033[1;0m");
	}
	for(i=0; i<20-(pst[0]/(pst[1]/20)); i++)
	{
		printf("▒");
	}

	printf("\n지하%d층  물약갯수:%d\n", pst[7], pst[6]);
}

int Boss(int *pst)
{
	int i, ch;
	int atkb[3];
	int map[10][10]={
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}};



	atkb[0]=randsys(70,250);
	atkb[1]=randsys(130,300);
	atkb[2]=randsys(250,450);

	while(1)
	{
		system("clear");

		if(pst[7]==1)
		{
			printf("도살자동현 %d/1500\n", pst[3]);
			for(i=0; i<pst[3]/75; i++)
			{
				printf("\033[1;41m \033[1;0m");
			}
			for(i=0; i<(1500-pst[3])/75; i++)
			{
				printf("▒");
			}
			printf("\n");

		}
		else if(pst[7]==2)
		{
			printf("성준바알 %d/2500\n", pst[4]);
			for(i=0; i<pst[4]/125; i++)
			{
				printf("\033[1;41m \033[1;0m");
			}
			for(i=0; i<(2500-pst[4])/125; i++)
			{
				printf("▒");
			}
			printf("\n");
		
		}
		else if(pst[7]==3)
		{
			printf("디아복로 %d/7777\n", pst[5]);
			for(i=0; i<pst[5]/388; i++)
			{
				printf("\033[1;41m \033[1;0m");
			}
			for(i=0; i<(7777-pst[5])/388; i++)
			{
				printf("▒");
			}
			printf("\n");
		}

		printf("\n\n\n\n\n\n1 공격 2 물약 3 도망\n");

		UI(pst);

		if(pst[3]>0 || pst[4]>0 || pst[5]>0)
		{
			ch=getch();
		}

		switch(ch)
		{
			case 49 :	//공격
				{
					pst[pst[7]+2]-=(pst[2]+randsys(10,50));
					pst[0]-=atkb[pst[7]-1];

					if(pst[pst[7]+2]<=0)
					{
						if(pst[5]<=0)
						{
							return 0;
						}
						pst[7]+=1;
						Map(pst);
					}
					break;
				}
			case 50 :	//물약 사용
				{
					if(pst[6]>0)
					{
						pst[0]+=randsys(30,100);
						pst[6]-=1;
						if(pst[0]>pst[1])
						{
							pst[0]=pst[1];
						}
					}
					break;
				}
			case 51 :	//도망
				{
					ch=randsys(1,100);
					return ch;
				}
			default :	//아무숫자
				{
					continue;
				}
		}
		if(pst[0]<0)
		{			
			return 0;
		}							
	}
}

int randsys(int num1, int num2)
{
	return rand()%(num2+1-num1)+num1;
}

int Title()
{
	int ch;

	system("clear");

	printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");
	printf("▒▒▒▒▒▒\033[1;41m   \033[1;0m▒▒▒\033[1;41m   \033[1;0m▒▒▒\033[1;41m   \033[1;0m▒▒▒\033[1;41m    \033[1;0m▒▒▒▒▒\033[1;41m   \033[1;0m▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒▒\033[1;41m \033[1;0m▒▒▒▒\033[1;41m   \033[1;0m▒▒▒\n");
	printf("▒▒▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒\033[1;41m \033[1;0m▒\033[1;41m \033[1;0m▒▒▒▒\033[1;41m \033[1;0m▒▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒\n");
	printf("▒▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m     \033[1;0m▒▒\033[1;41m     \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒\033[1;41m   \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\n");
	printf("▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒\033[1;41m \033[1;0m▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒▒▒\n");
	printf("▒▒▒\033[1;41m    \033[1;0m▒▒▒\033[1;41m   \033[1;0m▒▒\033[1;41m \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒\033[1;41m    \033[1;0m▒▒▒▒\033[1;41m    \033[1;0m▒▒▒\033[1;41m \033[1;0m▒▒\033[1;41m \033[1;0m▒▒\033[1;41m    \033[1;0m▒▒\033[1;41m    \033[1;0m▒▒▒▒▒\n");
	printf("▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");

	
	printf("\n\n\n                     1 게임시작 2 종료\n");

	ch=getch();

	return ch;
}


void Chat(char ment[])
{
	int max;

	max = strlen(ment);

	for(int i=0; i<max; i++)
	{
		fflush(stdout);
		printf("%c", ment[i]);
		usleep(50000);
	}
}
