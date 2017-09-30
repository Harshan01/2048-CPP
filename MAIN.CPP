#include<iostream.h>
#include<conio.h>
#include"CONSTANT.H"
#include"GRID.CPP"
#include<graphics.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>


class grid
{
    Grid gm; fstream file;

public:

    void paint(); //Paint the grid

    int isNextMovePoss(); //Calculates if next move is possible

    void input(); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(); //Save game and store in binary file

    void load(); //Load saved game
	
    fstream retfile()
    {
        return file;	    
    }

};

void main()
{
    grid g;
    clrscr();
    // Get the HIGH SCORE for displaying on home screen
    // SAVEDATA.DAT
    int high=0;
    fstream f=g.retfile();	
    f.open(*SAVEPATH,ios::binary|ios::in|ios::ate);
    f.read((char*)&high, sizeof(int));
    //

    // Initialize graphics component
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    //
    
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


void grid::paint()
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
    
    return gm.isNextMovePossible();
}

void grid::input()
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
    } while(inp!=keyx&&inp!=keyX&&isNextMovePoss());
}

void grid::update(int ctrl)
{
    //UPDATE PROCESS
    gm.move(ctrl);
    paint();
    input();
    //Call paint() at end of update
}

void grid::save()
{
    file.seekg(sizeof(int),ios::beg);
    file.write((char*)gm,sizeof(Grid));
}

void grid::load()
{
    file.seekg(sizeof(int),ios::beg);
    
    file.read((char*)&gm,sizeof(Grid));
    //gm=temp;
    paint();
}
