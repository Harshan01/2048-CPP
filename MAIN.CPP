#include<iostream.h>
#include<conio.h>
#include"CONSTANT.H"
#include"GRID.CPP"
#include<graphics.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

//fstream file;

class grid
{
    Grid gm;

public:

    void paint(); //Paint the grid

    int isNextMovePoss(); //Calculates if next move is possible

    void input(fstream); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(fstream); //Save game and store in binary file

    void load(fstream); //Load saved game

    //int* retmat(){return &mat[0][0];}
};

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
    grid g;
    char inp;
    cout<<"\t\t\t2048 GAME\n\n";
    cout<<"HIGH SCORE: "<<high<<"\n\n\n"; //<--high score
    cout<<"\n\nHelp: W-up, A-left, S-down, D-right\n\n";	
    cout<<"Enter the choice: (N-new game , L-load game)\n";
    cin>>inp;
    switch(inp)
    {
	case keyN:
	case keyn:   //NEW GAME
		    g.paint();
		    g.input(file);
		    break;
	case keyL:
	case keyl:   //LOAD GAME
		    g.load(file);
		    g.paint();
		    g.input(file);
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

int grid::isNextMovePoss()
{   //Calculation of whether next move is possible or not
    
    return Grid::isNextMovePossible();
}

void grid::input(fstream file)
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
			 input(file);
			 break;

		case keyp://SAVE GAME
		case keyP:save(file);
			 break;

		case keyl://LOAD GAME
		case keyL:load(file);
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

void grid::update(int ctrl)
{
    //UPDATE PROCESS
    gm.move(ctrl);
    paint();	
    //Call paint() at end of update
}

void grid::save(fstream file)
{
    file.seekg(sizeof(int),ios::beg);
    file.write((char*)gm,sizeof(Grid));
}

void grid::load(fstream file)
{
    file.seekg(sizeof(int),ios::beg);
    Grid temp;
    file.read((char*)&temp,sizeof(temp));
    gm=temp;
    paint();
}
