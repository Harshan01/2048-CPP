#include<iostream.h>
#include<conio.h>
#include"CONSTANT.H"
#include"GRID.CPP"
#include<graphics.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

fstream file;

class Display
{
    Grid grid;

public:

    void paint(); //Paint the grid

    int isNextMovePoss(); //Calculates if next move is possible

    void input(); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(); //Save game and store in binary file

    void load(); //Load saved game

    int** retmat(){return grid.getMatrix();}

    Display();

};

void main()
{
    clrscr();
    // Get the HIGH SCORE for displaying on home screen
    // SAVEDATA.DAT
    int high=0;
    file.open(SAVEPATH,ios::binary|ios::in|ios::ate);
    file.read((char*)&high, sizeof(int));
    //

    // Initialize graphics component
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    //
    Display g;
    char inp;
    cout<<"\t\t\t2048 GAME\n\n";
    cout<<"HIGH SCORE: "<<high<<"\n\n\n"; //<--high score
    cout<<"Help:\nN-New game.\nL-Load Game.\nP-Save game.\nX-Exit game.\nUse WASD to move\n";
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
	file.close();
    closegraph();

}


void Display::paint()
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
	    if(grid.getMatrix()[i][j]!=EMPTY)
		outtextxy(startx+100*i+49,starty+100*j+49,"");
	    else
		outtextxy(startx+100*i+49,starty+100*j+49,grid.getMatrix()[i][j]+"");
	}
    }
}

int Display::isNextMovePoss()
{   //Calculation of whether next move is possible or not

    return grid.isNextMovePossible();
}

void Display::input()
{
    char inp;
    do
    {
	inp=getch();
	switch(inp)
	{
		case keyn://NEW GAME
		case keyN:
			 grid.reset();
			 paint();
			 input();
			 break;

		case keyP://SAVE GAME
		case keyp:save();
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
    } while(inp!=keyx && inp!=keyX && isNextMovePoss());
	//***************************************************TODO display gameover message.
}

void Display::update(int ctrl)
{
    //UPDATE PROCESS
	grid.move(ctrl);
	paint();
    //Call paint() at end of update
}

void Display::save()
{
    file.seekg(sizeof(int),ios::beg);
    file.write((char*)&grid,sizeof(grid));
}

void Display::load()
{
    file.seekg(sizeof(int),ios::beg);
	file.read((char*)&grid,sizeof(grid));
    paint();
}

Display::Display()
{
    
}
