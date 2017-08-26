#include <graphics.h>
#include <time.h>

#define LEFT 0x4b00    //光标键值定义
#define RIGHT 0x4d00
#define DOWN 0x5000
#define UP 0x4800
#define A 0x1e61
#define D 0x2064
#define S 0x1f73
#define W 0x1177
#define ESC 0x011b
#define BACKSPACE 0x0e08
#define FREQUENCY 50

int driver=0;
int mode=VESA_1024x768x8bit;
int stop=0;
int pause=0;
int seed=0;
int fail=0;
int x_1,y_1;
int x_2,y_2;
int score1=0,score2=0;
int flag1=0,flag2=0;
int cur1,cur2;
int next1,next2;
char name1[],name2[];
int time_count=0;
time_t t10;
time_t t11;

void init();
void game();

void drawwall();
void gameover();

void player1();
void judge1();
void control1();
void rotate1();
void preview1();

void player2();
void judge2();
void control2();
void rotate2();
void preview2();

void draw();
void information1();
void information2();
void wordprint(char* s,int x,int y,int color);
void numberprint(int n,int x,int y,int color);

int mark1[26][12],mark2[26][12];
int block1[14][17]={{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1},
	              {0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,2},
	              {0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,3},
	              {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,4},
	              {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,5},
	              {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,6},
	              {0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,14},
				  {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1},
				  {0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,2},
	              {0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,3},
	              {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,4},
	              {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,5},
	              {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,6},
	              {0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,14}};

int block2[14][17]={{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1},
	              {0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,2},
	              {0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,3},
	              {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,4},
	              {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,5},
	              {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,6},
	              {0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,14},
				  {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1},
				  {0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,2},
	              {0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,3},
	              {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,4},
	              {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,5},
	              {0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,6},
	              {0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,14}};

	              


int main(int argc, char *argv[])    //主函数
{
	init();
	game();
	gameover();
	return 0;
}

void init()    //初始化
{
	int i,j;
	initgraph(&driver,&mode,"");
	cleardevice();

	x_1=x_2=0;
	
	srand(time(NULL)+seed);
	y_1=rand()%7;
	seed+=7;
    srand(time(NULL)+seed);
	y_2=rand()%7;
	seed+=7;

	srand(time(NULL)+seed);
	seed+=7;
	cur1=rand()%7;

	srand(time(NULL)+seed);
	seed+=7;
	cur2=rand()%7;

	srand(time(NULL)+seed);
	seed+=7;
	next1=rand()%7+7;

	srand(time(NULL)+seed);
	seed+=7;
	next2=rand()%7+7;

	for(i=0;i<12;i++)
		mark1[0][i]=mark1[25][i]=3;
	for(i=1;i<25;i++)
		mark1[i][0]=mark1[i][11]=3;
	for(i=1;i<=24;i++)
		for(j=1;j<=10;j++)
		    mark1[i][j]=0;
	
	for(i=0;i<12;i++)
		mark2[0][i]=mark2[25][i]=3;
	for(i=1;i<25;i++)
		mark2[i][0]=mark2[i][11]=3;
	for(i=1;i<=24;i++)
		for(j=1;j<=10;j++)
		    mark2[i][j]=0;

	drawwall();
}

void drawwall()    //绘制外墙
{
	int i;
	setcolor(15);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	for(i=100;i<=914;i++)
	{
		rectangle(i,50,i+9,59);
		rectangle(i,540,i+9,549);
	}
	for(i=60;i<=530;i++)
	{
		rectangle(100,i,109,i+9);
		rectangle(285,i,294,i+9);
		rectangle(495,i,510,i+9);
		rectangle(513,i,528,i+9);
		rectangle(729,i,738,i+9);
		rectangle(914,i,923,i+9);
	}
	for(i=110;i<=275;i++)
		rectangle(i,250,i+9,259);
	for(i=739;i<=913;i++)
		rectangle(i,250,i+9,259);

}

void game(){    //游戏主体函数
	t10=clock();
	while(!stop){
		player1();
		if(stop==1)
			return;
		player2();
	}
	return;
}

void player1(){//玩家一
	preview1();
	judge1();
    draw();
	control1();
	if(stop==1)
		return;
	draw();
	information1();
}

void judge1(){//玩家一-判断方块
    
	int i,j;
	int bottom;
	int random;
	int line;
	t11=clock();

    if(pause==0){
		if(difftime(t11,t10)>FREQUENCY){
			t10=t11;
			time_count+=1;

			for(line=2;line<=24;line++){//得分
				bottom=0;
				for(i=1;i<=10;i++)
					if(mark1[line][i]==2)
						bottom++;
			
			    while(bottom==10){
					for(j=1;j<=10;j++)
						for(i=line;i>=2;i--)
							mark1[i][j]=mark1[i-1][j];
					for(i=1;i<=10;i++)
						mark1[1][i]=0;
					score1+=10;
		
					bottom=0;
					for(i=1;i<=10;i++)
						if(mark1[line][i]==2)
							bottom++;
				}
			}
			
			if(flag1==1){//下一回合
				flag1=0;
		
				cur1=next1-7;
				srand(time(NULL)+seed);
    			seed+=7;
				random=rand()%7;
				next1=random+7;

				srand(time(NULL)+seed);
				seed+=7;
				random=rand()%7;
				x_1=-3;
				y_1=random;
			}

			else{//本回合

				for(i=15;i>=0;i--)//回合结束
					if(x_1+i/4>=0)
						if(block1[cur1][i]==1)
							if(mark1[x_1+i/4+1][y_1+i%4]!=0){
								flag1=1;
								for(i=15;i>=0;i--)
									if(block1[cur1][i]==1)
										mark1[x_1+i/4][y_1+i%4]=2;
							}
		
				for(i=1;i<=10;i++)//游戏结束
					if(mark1[1][i]==2){
					    stop=1;
						fail=1;
						break;
						}

				if(stop!=1&&flag1!=1){//回合未结束
					if(time_count%10==0)
						x_1++;
				}
			}
	    }
	}
}

void control1(){//玩家一-控制方块
 
	int i,j;
	int flag=0;
	int read;
	int temp[16];
 
	if(bioskey(1)){
		if(pause==0){
			read=bioskey(0);
			switch(read){
				case W:
					for(i=0;i<16;i++)
					    temp[i]=block1[cur1][i];
					rotate1();
					for(i=0;i<16;i++)
						if(block1[cur1][i]==1&&mark1[x_1+i/4][y_1+i%4]!=0){
							flag=1;
							break;
						}
					if(flag==1)
						for(i=0;i<16;i++)
							block1[cur1][i]=temp[i];
				    break;
			
				case S:
					for(i=1;;i++){
					    for(j=15;j>=0;j--){
							if(block1[cur1][j]==1)
					            if(mark1[x_1+j/4+i][y_1+j%4]!=0){
								    flag=1;
								    break;
								}
						}
						if(flag==1)
							break;	
					}
					x_1+=i-1;
				    break;
			
				case A:
					for(j=15;j>=0;j--){
						if(block1[cur1][j]==1)
							if(mark1[x_1+j/4][y_1+j%4-1]!=0){
								flag=1;
								break;
							}
					}
					if(flag==0)
					    y_1-=1;
					break;
			
				case D:	
					for(j=15;j>=0;j--){
						if(block1[cur1][j]==1)
							if(mark1[x_1+j/4][y_1+j%4+1]!=0){
								flag=1;
								break;
							}
					}
					if(flag==0)
					    y_1+=1;
					break;
			
				case ESC:
					stop=1;
					return;
				    break;
			
				case BACKSPACE:
					pause=1;
				    break;
				    		
				default:break;
			}
		}
		
		else{
			read=bioskey(0);
			switch(read){
				case BACKSPACE:
					pause=0;
					break;
				default:break;
			}
		}
	}
}

void rotate1()    //玩家一-旋转
{
	int i,j;
	int temp[16];

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			temp[4*j+(3-i)]=block1[cur1][4*i+j];

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			block1[cur1][4*i+j]=temp[4*i+j];
	free(temp);
}

void preview1(){//玩家一-预览方块

	int i;
	char s1[6]="Next:";

	wordprint(s1,150,100,14);
	for(i=0;i<16;i++)
		if(block1[next1][i]==1){
			setfillstyle(SOLID_FILL,block1[next1][16]);
			bar(150+(i%4)*20,120+(i/4)*20,169+(i%4)*20,139+(i/4)*20);
		}
		else{
			setfillstyle(SOLID_FILL,0);
			bar(150+(i%4)*20,120+(i/4)*20,169+(i%4)*20,139+(i/4)*20);
		}

}

void player2(){//玩家二
	preview2();
	judge2();
    draw();
	control2();
	if(stop==1)
		return;
	draw();
	information2();
}

void judge2(){//玩家二-判断方块
    
	int i,j;
	int bottom;
	int random;
	int line;
	t11=clock();

    if(pause==0){
		if(difftime(t11,t10)>FREQUENCY){
			t10=t11;
			time_count+=1;

			for(line=2;line<=24;line++){//得分
				bottom=0;
				for(i=1;i<=10;i++)
					if(mark2[line][i]==2)
						bottom++;
			
			    while(bottom==10){
					for(j=1;j<=10;j++)
						for(i=line;i>=2;i--)
							mark2[i][j]=mark2[i-1][j];
					for(i=1;i<=10;i++)
						mark2[1][i]=0;
					score2+=10;
		
					bottom=0;
					for(i=1;i<=10;i++)
						if(mark2[line][i]==2)
							bottom++;
				}
			}
			
			if(flag2==1){//下一回合
				flag2=0;
		
				cur2=next2-7;
				srand(time(NULL)+seed);
    			seed+=7;
				random=rand()%7;
				next2=random+7;

				srand(time(NULL)+seed);
				seed+=7;
				random=rand()%7;
				x_2=-3;
				y_2=random;
			}

			else{//本回合

				for(i=15;i>=0;i--)//回合结束
					if(x_2+i/4>=0)
						if(block2[cur2][i]==1)
							if(mark2[x_2+i/4+1][y_2+i%4]!=0){
								flag2=1;
								for(i=15;i>=0;i--)
									if(block2[cur2][i]==1)
										mark2[x_2+i/4][y_2+i%4]=2;
							}
		
				for(i=1;i<=10;i++)//游戏结束
					if(mark2[1][i]==2){
					    stop=1;
						fail=2;
						break;
						}

				if(stop!=1&&flag2!=1){//回合未结束
					if(time_count%10==0)
						x_2++;
				}
			}
	    }
	}
}

void control2(){//玩家二-控制方块
 
	int i,j;
	int flag=0;
	int read;
	int temp[16];
 
	if(bioskey(1)){
		if(pause==0){
			read=bioskey(0);
			switch(read){
				case UP:
					for(i=0;i<16;i++)
					    temp[i]=block2[cur2][i];
					rotate2();
					for(i=0;i<16;i++)
						if(block2[cur2][i]==1&&mark2[x_2+i/4][y_2+i%4]!=0){
							flag=1;
							break;
						}
					if(flag==1)
						for(i=0;i<16;i++)
							block2[cur2][i]=temp[i];
				    break;
			
				case DOWN:
					for(i=1;;i++){
					    for(j=15;j>=0;j--){
							if(block2[cur2][j]==1)
					            if(mark2[x_2+j/4+i][y_2+j%4]!=0){
								    flag=1;
								    break;
								}
						}
						if(flag==1)
							break;	
					}
					x_2+=i-1;
				    break;
			
				case LEFT:
					for(j=15;j>=0;j--){
						if(block2[cur2][j]==1)
							if(mark2[x_2+j/4][y_2+j%4-1]!=0){
								flag=1;
								break;
							}
					}
					if(flag==0)
					    y_2-=1;
					break;
			
				case RIGHT:	
					for(j=15;j>=0;j--){
						if(block2[cur2][j]==1)
							if(mark2[x_2+j/4][y_2+j%4+1]!=0){
								flag=1;
								break;
							}
					}
					if(flag==0)
					    y_2+=1;
					break;
			
				case ESC:
					stop=1;
					return;
				    break;
			
				case BACKSPACE:
					pause=1;
				    break;
				    		
				default:break;
			}
		}
		
		else{
			read=bioskey(0);
			switch(read){
				case BACKSPACE:
					pause=0;
					break;
				default:break;
			}
		}
	}
}

void rotate2()    //玩家一-旋转
{
	int i,j;
	int temp[16];

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			temp[4*j+(3-i)]=block2[cur2][4*i+j];

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			block2[cur2][4*i+j]=temp[4*i+j];
	free(temp);
}

void preview2(){//玩家二-预览方块

	int i;
	char s1[6]="Next:";

	wordprint(s1,779,100,14);
	for(i=0;i<16;i++)
		if(block2[next2][i]==1){
			setfillstyle(SOLID_FILL,block2[next2][16]);
			bar(779+(i%4)*20,120+(i/4)*20,798+(i%4)*20,139+(i/4)*20);
		}
		else{
			setfillstyle(SOLID_FILL,0);
			bar(779+(i%4)*20,120+(i/4)*20,798+(i%4)*20,139+(i/4)*20);
		}

}

void draw(){//绘制函数
	int i,j;
	int color;

	for(i=1;i<=24;i++)
		for(j=1;j<=10;j++){
			if((i>=x_1&&i<=x_1+3)&&(j>=y_1&&j<=y_1+3)){
				if(block1[cur1][(i-x_1)*4+(j-y_1)]==1){
					color=block1[cur1][16];
					setfillstyle(SOLID_FILL,color);
					bar(275+j*20,40+i*20,294+j*20,59+i*20);
				}
				else if(mark1[i][j]==2){
					setfillstyle(SOLID_FILL,7);
					bar(275+j*20,40+i*20,294+j*20,59+i*20);
				}
				else{
					setfillstyle(SOLID_FILL,0);
					bar(275+j*20,40+i*20,294+j*20,59+i*20);
				}

			}
			else if(mark1[i][j]==2){
				setfillstyle(SOLID_FILL,7);
				bar(275+j*20,40+i*20,294+j*20,59+i*20);
			}
			else{
				setfillstyle(SOLID_FILL,0);
				bar(275+j*20,40+i*20,294+j*20,59+i*20);
			}
		}

	for(i=1;i<=24;i++)
		for(j=1;j<=10;j++){
			if((i>=x_2&&i<=x_2+3)&&(j>=y_2&&j<=y_2+3)){
				if(block2[cur2][(i-x_2)*4+(j-y_2)]==1){
					color=block2[cur2][16];
					setfillstyle(SOLID_FILL,color);
					bar(509+j*20,40+i*20,529+j*20,59+i*20);
				}
				else if(mark2[i][j]==2){
					setfillstyle(SOLID_FILL,7);
					bar(509+j*20,40+i*20,529+j*20,59+i*20);
				}
				else{
					setfillstyle(SOLID_FILL,0);
					bar(509+j*20,40+i*20,529+j*20,59+i*20);
				}

			}
			else if(mark2[i][j]==2){
				setfillstyle(SOLID_FILL,7);
				bar(509+j*20,40+i*20,529+j*20,59+i*20);
			}
			else{
				setfillstyle(SOLID_FILL,0);
				bar(509+j*20,40+i*20,529+j*20,59+i*20);
			}
		}
}

void information1(){//玩家1信息
	
	char s1[6]="Name:";
	char s2[7]="Score:";

	wordprint(s1,150,270,14);
	//wordprint(name1,150,300,14);
	wordprint(s2,150,330,14);
	setfillstyle(SOLID_FILL,0);
	bar(150,360,250,370);
	numberprint(score1,150,360,14);

}

void information2(){//玩家2信息

	char s1[6]="Name:";
	char s2[7]="Score:";

	wordprint(s1,779,270,14);
	//wordprint(name2,779,300,14);
	wordprint(s2,779,330,14);
	setfillstyle(SOLID_FILL,0);
	bar(779,360,879,370);
	numberprint(score2,779,360,14);

}

void wordprint(char* s,int x,int y,int color)   //文字打印函数
{ 
	setcolor(color);
	outtextxy(x,y,s);
	
}

void numberprint(int n,int x,int y,int color)    //数字打印函数
{
	char* p;
	int number=n;
	int i;
	int count=0;
	setcolor(color);

	if(number==0)
		count=1;
	while(number!=0)
	{
		count++;
		number/=10;
	}

	if((p=(char*)malloc(sizeof(char)*(count+1)))==NULL)
		exit(0);

	for(i=count-1;i>=0;i--){
		*(p+i)=(char)(48+n%10);
		n/=10;
	}

	*(p+count)=NULL;

	outtextxy(x,y,p);
}

void gameover()    //关闭游戏
{
	clrscr();

	getch();
	closegraph();
}