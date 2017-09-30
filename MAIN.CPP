#include<iostream.h>
#include<conio.h>
#include"CONSTANT.H"
#include"GRID.CPP"
#include<graphics.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

fstream file;

class grid
{
    int mat[SIZE][SIZE];

public:

    void paint(); //Paint the grid

    int isNextMovePoss(); //Calculates if next move is possible

    void input(); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(); //Save game and store in binary file

    void load(); //Load saved game

    int* retmat(){return &mat[0][0];}

    grid();

};

void main()
{
    clrscr();
    // Get the HIGH SCORE for displaying on home screen
    // SAVEDATA.DAT
    int high=0;
    file.open("SAVEDATA.DAT",ios::binary|ios::in|ios::ate);
    file.read((char*)&high, sizeof(int));
    //

    // Initialize graphics component
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    //
    grid g;
    char inp;
    cout<<"\t\t\t2048 GAME\n\n";
    cout<<"HIGH SCORE: "<<high<<"\n\n\n"; //<--high score
    cout<<"Enter the choice: \n";
    cin>>inp;
    switch(inp)
    {
	case 'N':
	case 'n':   //NEW GAME
		    g.paint();
		    g.input();
		    break;
	case 'L':
	case 'l':   //LOAD GAME
		    g.load();
		    g.paint();
		    g.input();
		    break;
    }
    getch();
    closegraph();

}


void grid::paint()
{
    //Each box dimension is 100px x 100px
    cleardevice();
    setfillstyle(SOLID_FILL,BLUE);
    int startx=getmaxx()/2 - (int)((float)SIZE*100/2);
    int endx=getmaxx()/2 + (int)((float)SIZE*100/2);
    int starty=getmaxy()/2 - (int)((float)SIZE*100/2);
    int endy=getmaxy()/2 + (int)((float)SIZE*100/2);
    int vert[]={startx,starty,endx,starty,endx,endy,startx,endy};
    fillpoly(4,vert);

    for(int i=0;i<SIZE;i++)
    {
	for(int j=0;j<SIZE;j++)
	{
	    if(mat[i][j]<0)
		outtextxy(startx+100*i+49,starty+100*j+49,"");
	    else
		outtextxy(startx+100*i+49,starty+100*j+49,mat[i][j]+"");
	}
    }
}

int grid::isNextMovePoss()
{   //Calculation of whether next move is possible or not

    return 0;
}

void grid::input()
{
    char inp;
    do
    {
	inp=getch();
	switch(inp)
	{
		case 'n'://NEW GAME
		case 'N':for(int i=0;i<SIZE;i++)
			     for(int j=0;j<SIZE;j++)
				 mat[i][j]=-1;
			 paint();
			 input();
			 break;

		case 'p'://SAVE GAME
		case 'P':save();
			 break;

		case 'l'://LOAD GAME
		case 'L':load();
			 break;

		case 'x'://EXIT GAME
		case 'X':exit(0);
			 break;

		case 'w':
		case 'W':update(UP);
			 break;

		case 'a':
		case 'A':update(LEFT);
			 break;

		case 's':
		case 'S':update(DOWN);
			 break;

		case 'd':
		case 'D':update(RIGHT);
			 break;
	}
    } while(inp!='w'&&inp!='W'&&inp!='a'&&inp!='A'&&inp!='s'&&inp!='S'&&inp!='d'&&inp!='D');
}

void grid::update(int ctrl)
{
    //UPDATE PROCESS

    //Call paint() at end of update
}

void grid::save()
{
    file.seekg(sizeof(int),ios::beg);
    file.write((char*)this,sizeof(grid));
}

void grid::load()
{
    file.seekg(sizeof(int),ios::beg);
    grid temp;
    file.read((char*)&temp,sizeof(temp));
    int *t=temp.retmat();
    for(int i=0; i<SIZE;i++)
	for(int j=0;j<SIZE;j++)
	{
	    mat[i][j]=*t; t++;
	}
    paint();
}

grid::grid()
{
    for(int i=0;i<SIZE;i++)
	for(int j=0;j<SIZE;j++)
	    mat[i][j]=-1;
}
