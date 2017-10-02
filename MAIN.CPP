#include<iostream.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"CONSTANT.H"
#include"GRID.H"
#include<graphics.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

char *SAVEPATH="SAVEDATA.DAT";

class Display
{
	Grid gm;
	fstream file;
	int startx,starty,endx,endy;

public:

  Display()
  {
     file.open(SAVEPATH, ios::binary | ios::in | ios::ate | ios::out);
     startx=getmaxx()/2 - (int)(SIZE*PIXEL/2);
     endx=getmaxx()/2 + (int)(SIZE*PIXEL/2);
     starty=getmaxy()/2 - (int)(SIZE*PIXEL/2);
     endy=getmaxy()/2 + (int)(SIZE*PIXEL/2);
  }

    void paint(); //Paint the grid

    int isNextMovePoss(); //Calculates if next move is possible

    void input(); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(); //Save game and store in binary file

    void load(); //Load saved game

  ~Display()
  {
      file.close();
  }

};

void main()
{
    clrscr();
    // Get the HIGH SCORE for displaying on home screen
    // SAVEDATA.DAT
    int high=0;
    fstream f;
    f.open(SAVEPATH,ios::binary|ios::in|ios::ate);
    if(!f)
    {
	    f.open(SAVEPATH, ios::binary|ios::out|ios::in|ios::ate);
	    f.write((char*)(new int(0)), sizeof(int));
	    Grid t;
	    f.write((char *)&t, sizeof(Grid));
    }
    f.seekg(0,ios::beg);
    f.read((char*)&high, sizeof(int));
    randomize();


    char inp;
    cout<<"\t\t\t2048 GAME\n\n";
    cout<<"HIGH SCORE: "<<high<<"\n\n\n"; //<--high score
    cout<<"Help:\nN-New game.\nL-Load Game.\nP-Save game.\nX-Exit game.\nUse WASD to move\nPress any key to Start";
    getch();
   /* cin>>inp;
    switch(inp)
    {
	case keyL:
	case keyl:   //LOAD GAME
		    g.load();
		    break;
    }*/
    // Initialize graphics component
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
    //
    Display g;
    g.paint();
    g.input();
    getch();
    f.close();
//    closegraph();

}


void Display::paint()
{

    cleardevice();
    //setfillstyle(SOLID_FILL,LIGHTBLUE);

    //int vert[]={startx,starty,endx,starty,endx,endy,startx,endy};
    //fillpoly(4,vert);
    rectangle(startx,starty,endx,endy);
    char temp[10], sc[10];
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
    strcpy(temp, "Score :");
    itoa(gm.getScore(), sc, 10);
    strcat(temp, sc);
    outtextxy(startx, starty-35, temp);
    for(int i=0;i<SIZE;i++)
    {
	    line(startx, starty+PIXEL*(i+1), endx, starty+PIXEL*(i+1));
	    line(startx+PIXEL*(i+1), starty, startx+PIXEL*(i+1), endy);
	for(int j=0;j<SIZE;j++)
	{
	    int val=gm.getMatrix()[i][j];

	    if(val==EMPTY)
		outtextxy(startx+PIXEL*j+PIXEL/2,starty+PIXEL*i+PIXEL/2," ");
	    else
	    {
	       //	strcpy(temp, "");
	       //	sprintf(temp, "%d", gm.getMatrix()[i][j]);
		   strcpy(temp, "");
	       itoa(val, temp, 10);
		outtextxy(startx+PIXEL*j+PIXEL/2-10,starty+PIXEL*i+PIXEL/2,temp);
	    }
	}
    }
}

int Display::isNextMovePoss()
{   //Calculation of whether next move is possible or not

    return gm.isNextMovePossible();
}

void Display::input()
{
    char inp;
    do
    {
	inp=getch();
/*	outtextxy(10, 10, "Got input");
	getch();  */
	switch(inp)
	{
		case keyn://NEW GAME
		case keyN:
			 gm.reset();
			 paint();
			 break;


		case keyp://SAVE GAME
		case keyP:save();
			 break;

		case keyl://LOAD GAME
		case keyL:load();
			 break;


		/*case keyx://EXIT GAME Instead added at while checking
		case keyX:exit(0);
			 break;*/

		case keyw:
		case keyW:update(UP);
			 break;

		case keya:
		case keyA:update(LEFT);
			 break;

		case keys:
		case keyS:update(DOWN);
			 break;

		case keyd:
		case keyD:update(RIGHT);
			 break;
	}
  /*	outtextxy(10, 10, "moved");
	getch();*/
	paint();
    } while(inp!=keyx && inp!=keyX && isNextMovePoss());
    outtextxy(endx-40, starty-35, "Game Over! Press any key.");
    getch();
	//***************************************************display gameover message.
  //  cleardevice();
    closegraph();
    clrscr();
	int score=gm.getScore();
	cout<<"\n\n\nGAME OVER!!!\nYour score is : "<<score;
	file.seekg(0,ios::beg);
	int high;
	file.read((char*)&high, sizeof(int));
	if(score>high)
	{
	    cout<<"\n\n\nNEW HIGH SCORE!!!";
		file.seekp(0,ios::beg);
	    file.write((char*)&score,sizeof(int));
	}
	else
	    cout<<"\n\n\nHigh score:"<<high;

}

void Display::update(int ctrl)
{
    //UPDATE PROCESS
//    outtextxy(10, 10, "reached update");
    gm.move(ctrl);
    //Call paint() at end of update
}

void Display::save()
{
    file.seekp(sizeof(int),ios::beg);
    gm.save(file);
}

void Display::load()
{
    file.seekg(sizeof(int),ios::beg);
    gm.load(file);
    //gm=temp;
    //paint(); Moved to before do while ends
}
/*#include"GRID.H"
#include<graphics.h>
#include"CONSTANT.H"
#include"stdlib.h"*/
int **forRight(int **_2D, int i);
int action(int **p);
int **forLeft(int **_2D, int i);
int **forUp(int **_2D, int i);
int **forDown(int **_2D, int i);
Grid::Grid()
{
     score=0;
     matrix=new int*[SIZE];
     for(int i=0; i<SIZE; i++)
     {
	matrix[i]=new int[SIZE];
	for(int j=0; j< SIZE; j++)
	    matrix[i][j]=EMPTY;
     }
     newNumber();
}
Grid::~Grid()
{
     for(int i=0;i<SIZE;++i)
	delete matrix[i];
     delete matrix;
}
int Grid::isNextMovePossible()
{
    //IF any box empty or any two adjacent elements in matrix are equal then possible.
    //Checking of that is not implemented efficiently, can be optimized later.
    int i, j;
	for(i=0;i<SIZE;++i)
		for(j=0;j<SIZE;++j)
			if(matrix[i][j]==EMPTY)
				return TRUE;
    for(i=0; i< SIZE-1; ++i)
    {
	for(j=0; j< SIZE-1; ++j)
	    if(matrix[i][j] == matrix[i+1][j] ||
		matrix[i][j] == matrix[i][j+1])
			return TRUE;
    }
    return FALSE;
}
void Grid::move(int key)
{
    int i,j, k, noOfBlanks;
  /*  outtextxy(10, 20, "reached move");
	getch();*/
    if(!isNextMovePossible())
	return;
int temp[SIZE][SIZE];
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			temp[i][j]=matrix[i][j];
/*    outtextxy(20, 10, "next move possible");
	getch();*/
    int **p;
    switch(key)
    {
    case RIGHT:
		for(i=0;i<SIZE; ++i)
		{
			p=forRight(matrix, i);
			score+=action(p);
			delete p;
		  //	outtextxy(10, 10, "2");
		}
//		outtextxy(10, 10, "3");
		break;
	case LEFT:
		for(i=0;i<SIZE; ++i)
		{
			p=forLeft(matrix, i);
			score+=action(p);
			delete p;
		}
		break;
	case UP:
		for(i=0;i<SIZE; ++i)
		{
			p=forUp(matrix, i);
			score+=action(p);
			delete p;
		}
		break;
	case DOWN:
		for(i=0;i<SIZE; ++i)
		{
			p=forDown(matrix, i);
			score+=action(p);
			delete p;
		}
		break;
	}
	//Call newNumber to generate a random number somewhere.
	int flag=FALSE;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			if(temp[i][j]!=matrix[i][j])
			{     flag=TRUE; break; }
	if(flag==TRUE)
		newNumber();
}
void Grid::newNumber()
{
	int i, j, noOfBlanks=0;
	//Make an array of (i,j) where boxes are empty
	int emptyIJ[SIZE*SIZE][2];
	for(i=0; i< SIZE; ++i)
	{	for(j=0; j< SIZE; ++j)
		{
			if(matrix[i][j]==EMPTY)
			{
				emptyIJ[noOfBlanks][0]=i;
				emptyIJ[noOfBlanks][1]=j;
				noOfBlanks++;
			}
		}
	}
	if(noOfBlanks==0)
		return;
	//Generate two random numbers one for 2 or 4, other which will indicate position in the array.

	int val=random(4);//val takes 0,1,2,3
	if(val==3)
		val=4;
	else
		val=2;

	i=rand()%noOfBlanks;
	//Update that particular spot with val
	matrix[ (emptyIJ[i][0]) ][ (emptyIJ[i][1]) ]=val;
}
int** Grid::getMatrix()
{
	return matrix;
}
//io functions to class Grid
void Grid::save(fstream &file)
{
	file.write((char *)&score, sizeof(int));
	//int **m=g.getMatrix();
	for(int i=0; i<SIZE; ++i)
		for(int j=0; j<SIZE; ++j)
			file.write((char *)&matrix[i][j], sizeof(int));

}
void Grid::load(fstream &file)
{
	file.read((char *)&score, sizeof(int));
	//int **m=g.getMatrix();
	for(int i=0; i<SIZE; ++i)
		for(int j=0; j<SIZE; ++j)
			file.read((char *)&matrix[i][j], sizeof(int));
	//return file;
}
int Grid::getScore()
{
	return score;
}
void Grid::reset()
{
     score=0;
     for(int i=0; i<SIZE; i++)
     {
	    for(int j=0; j< SIZE; j++)
		 matrix[i][j]=EMPTY;
     }
     newNumber();
}
int **forRight(int **_2D, int i)//SIZExSIZE, to delete return value after ysing
{
	int **p=new int*[SIZE];
	for(int j=0;j<SIZE;++j)
		p[j]=&_2D[i][j];
	return p;
}
int **forLeft(int **_2D, int i)//SIZExSIZE, to delete return value after ysing
{
	int **p=new int*[SIZE];
	for(int j=SIZE-1;j>=0;--j)
		p[j]=&_2D[i][SIZE-1-j];
	return p;
}
int **forDown(int **_2D, int j)//SIZExSIZE, to delete return value after ysing
{
	int **p=new int*[SIZE];
	for(int i=0;i<SIZE;++i)
		p[i]=&_2D[i][j];
	return p;
}
int **forUp(int **_2D, int j)//SIZExSIZE, to delete return value after ysing
{
	int **p=new int*[SIZE];
	for(int i=SIZE-1 ; i>=0 ; --i)
		p[i]=&_2D[SIZE-1-i][j];
	return p;
}
void removeEmpty(int **p)
{
	int i, j, noOfBlanks;
	for(i=1, noOfBlanks=0; i<SIZE;++i)
		if(*p[i]==EMPTY)
			noOfBlanks++;
	for(i=SIZE-1; i>=1 && noOfBlanks > 0 ;--i)
	{
		if(*p[i]==EMPTY)
		{
			for(j=i; j>=1; --j)
			{
				*p[j]=*p[j-1];
				*p[j-1]=EMPTY;
			}
			--noOfBlanks;
		}
	}
}

int action(int **p)
{
	int i, addScore=0;
	//Step 1: Remove blank spaces at indices >= 1
	removeEmpty(p);
	//Step 2: If two equal numbers are adjacent add them and put in right most
	for(i=SIZE-1; i>=0; --i)
	{
		if(*p[i]==*p[i-1]&& *p[i] != EMPTY)
		{
			addScore+=(*p[i])*=2;
			*p[i-1]=EMPTY;
			--i;
		}
	}
	//Step 3: Remove blank spaces again
	removeEmpty(p);
	return addScore;
}
