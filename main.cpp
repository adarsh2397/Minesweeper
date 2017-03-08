#include<iostream>
#include<graphics.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<ctype.h>
using namespace std;

void layout(int xs, int ys, int r);
void placeBombs(int r,int n);
void redDot(int xs,int ys,int r);
bool checkIfBomb(int i,int j);
void addNumbers(int r);
bool gameOver(int r);
void caller(int,int,int,int);
bool ripple(int,int);
int jclick(int,int);
int iclick(int,int);
void smallbox(int,int);
bool gameOver(int r);
void callDrawBomb(int r);

int xg,yg;
static int rows;
int numbers[20][20];
bool bombs[20][20];
bool flag[20][20];
bool flagPresent[20][20];

void click_handler(int x, int y)

{
	
	if(x<xg || y<yg || x>(xg+ 30*rows) || y>(yg+ 30*rows)){
			return;
	}
	
	caller(x,y,xg,yg);
	gameOver(rows);
	
}

void drawflag(int i,int j)
{
	setfillstyle(1,RED);
	int tri[6]={xg+j*30+6,yg+i*30+6,xg+j*30+24, yg+ i*30 +13, xg+j*30+6, yg+ i*30 +16 };
	fillpoly(3,tri);
	setcolor(BROWN);
	line(xg+j*30+6,yg+i*30+6, xg+j*30+6,yg+i*30+24);
}

void flag_handler(int x,int y){
	int i = iclick(y,yg);
	int j = jclick(x,xg);
	if(flag[i][j] == true && bombs[i][j] == false){
		return;
	}
	if(flagPresent[i][j] == false){
		drawflag(i,j);
		flagPresent[i][j] = true;
	}else{
		smallbox(xg + j*30,yg + i*30);
		flagPresent[i][j] = false;
	}
	gameOver(rows);
}

void makeAllFlagNotPresent(){
	for(int i=0;i<20;i++){
	for(int j=0;j<20;j++){
			flagPresent[i][j] = false;
		}
	}
}

void makeAllZero(){
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			numbers[i][j] = 0;
		}
	}
}

void makeAllFlagFalse(int r){
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			flag[i][j] = false;
		}
	}
}

void removeBombs(){
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			bombs[i][j] = false;
		}
	}
}

void displayNumbers(int r){
	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			cout<<numbers[i][j]<<" ";
		}
		cout<<endl;
	}
}
int main(){
	int gd = DETECT;
	int gm;
	
	do{
	int r;
	int noBombs;
	cout<<"Enter number of rows: ";
	cin>>r;
	rows = r;
	cout<<"Enter number of bombs: ";
	cin>>noBombs;
	if(noBombs>r*r)
	cout<<"No scene";
	removeBombs();
	makeAllFlagFalse(r);
	makeAllFlagNotPresent();
	placeBombs(r,noBombs);
	
	makeAllZero();
	addNumbers(r);
	displayNumbers(r);
	
	
	initwindow(1280,720);

	int X=getmaxx()/2, Y=getmaxy()/2;
	int startx,starty;
	if(r%2==0){
		startx = X-((r/2)*30);
		starty = Y-((r/2)*30);
	}else{
		startx = X-((r/2)*30)-15;
		starty = Y-((r/2)*30)-15;
	}
	
	xg = startx;
	yg = starty;
	
	
	layout(startx,starty,r);
	//redDot(startx,starty,r);
		
		
	registermousehandler(WM_LBUTTONDOWN, click_handler);
	registermousehandler(WM_RBUTTONDOWN, flag_handler);

	
	getch();
	
	
}
}


void smallbox(int x,int y)
{
	
	
	setcolor(7);
	
	//inner rect
	int points[] = {x+4,y+4,x+26,y+4,x+26,y+26,x+4,y+26};
	setfillstyle(1,7);
	fillpoly(4,points);
	
	
	
	
	//trapezium 1
	int points1[] = {x,y,x+30,y,x+26,y+4,x+4,y+4};
	setfillstyle(1,15);
	fillpoly(4,points1);
	
	//trapezium 2 left
	int points2[] = {x,y,x+4,y+4,x+4,y+26,x,y+30};
	fillpoly(4,points2);
	
	//trapezium 3 - bottom
	int points3[] = {x,y+30,x+4,y+26,x+26,y+26,x+30,y+30};
	setfillstyle(1,8);
	fillpoly(4,points3);
	
	//trapezium 4 - right
	int points4[] = {x+30,y,x+30,y+30,x+26,y+26,x+26,y+4};
	fillpoly(4,points4);	
	
	
	line(x,y,x+4,y+4);
}

void layout(int xs, int ys, int r)
{
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<r;j++)
		{
			smallbox(xs+(j*30), ys+(i*30));
		}
	}
}

void placeBombs(int r,int n){
	srand((unsigned)time(0)); 
    int random; 
    int lowest=0, highest=r*r-1; 
    int range=(highest-lowest)+1; 
    for(int index=0; index<n;){ 
        random = lowest+int(range*rand()/(RAND_MAX + 1.0)); 
        if(checkIfBomb(random/r,random%r) == false)
       	{
		  bombs[random/r][random%r] = true;
		  flag[random/r][random%r] = true;
		  index++;
		}
    } 
}

bool checkIfBomb(int i,int j){
	if(bombs[i][j] == true){
		return true;
	}else return false;
}

void redDot(int xs,int ys,int r){
	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			setcolor(RED);
			if(bombs[i][j] == true){
				circle(xs + j*30 + 15, ys + i*30 + 15,5);
			}
		}
	}
}

void addNumbers(int r){
	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			if(checkIfBomb(i,j) == true){
				numbers[i-1][j-1]++;
				numbers[i-1][j]++;
				numbers[i-1][j+1]++;
				numbers[i][j-1]++;
				numbers[i][j+1]++;
				numbers[i+1][j-1]++;
				numbers[i+1][j]++;
				numbers[i+1][j+1]++;
			}
		}
	}
}

int jclick(int x,int xs){
	int pos = (x-xs)/30;
	return pos;
}

int iclick(int y,int ys){
	int pos = (y-ys)/30;
	return pos; 
}

void caller(int x,int y,int xs,int ys){
	int i = iclick(y,ys);
	int j = jclick(x,xs);
	
	if(bombs[i][j] == true){
		char *str = "GAME OVER!";
		setbkcolor(BLACK);
		settextstyle(3, HORIZ_DIR, 5);
		outtextxy(getmaxx()/2 - 130, 50,str);
		callDrawBomb(rows);
		delay(5000);
		closegraph();
	}else{
	ripple(i,j);
	}
}

bool ripple(int i,int j){
	if(flag[i][j]==true)
	return false;
	
	
	if(i<0 || j<0 || i>rows-1 || j>rows-1){
		return false;
	}
	
	if(numbers[i][j] == 0){
		if(i<rows && j<rows){
		flag[i][j] = true;
		setcolor(8);
		cout<<i<<" "<<j<<" "<<rows<<endl;
		setfillstyle(1,7);
		int points[] = {xg + j*30,yg + i*30,xg+j*30 + 30,yg+i*30,xg+j*30 + 30,yg+i*30 + 30,xg +j*30,yg + i*30 + 30};
		fillpoly(4,points);
		}
		ripple(i-1,j-1);
		ripple(i-1,j);
		ripple(i-1,j+1);
		ripple(i,j-1);
		ripple(i,j+1);
		ripple(i+1,j-1);
		ripple(i+1,j);
		ripple(i+1,j+1);	
	}
	else 
	{
		if(i<rows && j<rows){
		setfillstyle(1,7);
		setbkcolor(7);
		flag[i][j] = true;
		setcolor(8);
		cout<<i<<" "<<j<<" "<<rows<<endl;
		int points[] = {xg + j*30,yg + i*30,xg+j*30 + 30,yg+i*30,xg+j*30 + 30,yg+i*30 + 30,xg +j*30,yg + i*30 + 30};
		fillpoly(4,points);
		char str[2];
		setcolor(RED);
		itoa(numbers[i][j],str,10);
		settextstyle(3, HORIZ_DIR, 1);
		outtextxy(xg + j*30 + 12, yg + i*30 + 2,str);
		}
		return false;
	}
	
	return false;
}



bool gameOver(int r){
	bool condition1 = true;
	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			if(flag[i][j] == false){
				condition1 = false;
				break;
			}
		}
	}
	
	bool condition2 = true;
	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			if(bombs[i][j] != flagPresent[i][j]){
				condition2 = false;
				break;
			}
		}
	}
	
	if(condition1 && condition2){
		char *str = "YOU WIN!";
		setbkcolor(BLACK);
		settextstyle(3, HORIZ_DIR, 5);
		outtextxy(getmaxx()/2 - 110, 50,str);
		delay(5000);
		closegraph();
	}
	
	/*for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			cout<<flag[i][j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<endl;
	
	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			cout<<flagPresent[i][j]<<" ";
		}
		cout<<endl;
	}*/
	
	return true;
}

void drawbomb(int i,int j)
{
	
	setcolor(BLACK);
	circle(xg + j*30 + 15,yg + i*30 + 15, 5);
	circle(xg + j*30 + 15,yg + i*30 + 15, 4);
	circle(xg + j*30 + 15,yg + i*30 + 15, 3);
	circle(xg + j*30 + 15,yg + i*30 + 15, 2);
	circle(xg + j*30 + 15,yg + i*30 + 15, 1);
	setcolor(YELLOW);
	circle(xg + j*30 + 15,yg + i*30 + 15, 6);
	circle(xg + j*30 + 15,yg + i*30 + 15, 7);
}

void callDrawBomb(int r){
	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			if(bombs[i][j] == true){
				drawbomb(i,j);
			}
		}
	}
}


