#include<iostream.h>
#include<conio.h>
#include"CONSTANT.H"
#include"GRID.CPP"
#include<graphics.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

//fstream file;

/*class grid
{
    int mat[SIZE][SIZE];

public:

    void paint(); //Paint the grid

    int isNextMovePoss(); //Calculates if next move is possible

    void input(); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(); //Save game and store in binary file

    void load(); //Load saved game

    //int* retmat(){return &mat[0][0];}
};*/

void main()
{
    clrscr();
    // Get the HIGH SCORE for displaying on home screen
    // SAVEDATA.DAT
    int high=0;
    fstream file;	
    file.open(*SAVEPATH,ios::binary|ios::in|ios::ate);
    file.read((char*)&high, sizeof(int));
    //

    // Initialize graphics component
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    //
    Grid g;
    char inp;
    cout<<"\t\t\t2048 GAME\n\n";
    cout<<"HIGH SCORE: "<<high<<"\n\n\n"; //<--high score
    cout<<"Enter the choice: \n";
    cin>>inp;
    switch(inp)
    {
	case keyN:
	case keyn:   //NEW GAME
		    g.paint();
		    g.input();
		    break;
	case keyL:
	case keyl:   //LOAD GAME
		    g.load();
		    g.paint();
		    g.input();
		    break;
    }
    getch();
    closegraph();

}


void Grid::paint()
{
    
    cleardevice();
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    int startx=getmaxx()/2 - (int)((float)SIZE*PIXEL/2);
    int endx=getmaxx()/2 + (int)((float)SIZE*PIXEL/2);
    int starty=getmaxy()/2 - (int)((float)SIZE*PIXEL/2);
    int endy=getmaxy()/2 + (int)((float)SIZE*PIXEL/2);
    int vert[]={startx,starty,endx,starty,endx,endy,startx,endy};
    fillpoly(4,vert);

    for(int i=0;i<SIZE;i++)
    {
	for(int j=0;j<SIZE;j++)
	{
	    if(mat[i][j]==EMPTY)
		outtextxy(startx+PIXEL*i+PIXEL/2,starty+PIXEL*j+PIXEL/2,"");
	    else
		outtextxy(startx+PIXEL*i+PIXEL/2,starty+PIXEl*j+PIXEL/2,matrix[i][j]+"");
	}
    }
}

/*int grid::isNextMovePoss()
{   //Calculation of whether next move is possible or not
    
    return Grid::isNextMovePossible();
}*/

void Grid::input()
{
    char inp;
    do
    {
	inp=getch();
	switch(inp)
	{
		case keyn://NEW GAME
		case keyN:for(int i=0;i<SIZE;i++)
			     for(int j=0;j<SIZE;j++)
				 matrix[i][j]=EMPTY;
			 paint();
			 input();
			 break;

		case keyp://SAVE GAME
		case keyP:save();
			 break;

		case keyl://LOAD GAME
		case keyL:load();
			 break;

		case keyx://EXIT GAME
		case keyX:exit(0);
			 break;

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
    } while(inp!=keyw&&inp!=keyW&&inp!=keya&&inp!=keyA&&inp!=keys&&inp!=keyS&&inp!=keyd&&inp!=keyD);
}

/*void grid::update(int ctrl)
{
    //UPDATE PROCESS
    Grid::move();
    //Call paint() at end of update
}*/

void Grid::save(fstream file)
{
    file.seekg(sizeof(int),ios::beg);
    file.write((char*)this,sizeof(Grid));
}

void Grid::load(fstream file)
{
    file.seekg(sizeof(int),ios::beg);
    grid temp;
    file.read((char*)&temp,sizeof(temp));
    int *t=temp.getMatrix();
    for(int i=0; i<SIZE;i++)
	for(int j=0;j<SIZE;j++)
	{
	    mat[i][j]=t[i][j]; 
	}
    paint();
}
