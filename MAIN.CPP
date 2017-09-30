#include<iostream.h>
#include<conio.h>
#include"CONSTANT.H"
#include"GRID.CPP"
#include<graphics.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>


class Display
{
	Grid gm;
	fstream file;

public:

  Display()
  {
     file.open(SAVEPATH,ios::binary|ios::in|ios::ate);//SAVEPATH itself is char * only
  }
  
    void paint(); //Paint the grid

    int isNextMovePoss(); //Calculates if next move is possible

    void input(); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(); //Save game and store in binary file

    void load(); //Load saved game
  
  void ~Display()
  {
      file.close();  
  }

    fstream retfile()
    {
        return file;	    
    }
};

void main()
{
    Display g;
    clrscr();
    // Get the HIGH SCORE for displaying on home screen
    // SAVEDATA.DAT
    int high=0;
    fstream f=g.retfile();	
    f.open(SAVEPATH, ios::binary|ios::in|ios::ate);
    f.read((char*)&high, sizeof(int));

    // Initialize graphics component
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    //

    char inp;
    cout<<"\t\t\t2048 GAME\n\n";
    cout<<"HIGH SCORE: "<<high<<"\n\n\n"; //<--high score
    cout<<"Help:\nN-New game.\nL-Load Game.\nP-Save game.\nX-Exit game.\nUse WASD to move\n";

    cin>>inp;
    switch(inp)
    {
	case keyL:
	case keyl:   //LOAD GAME
		    g.load();
		    break;
    }
    g.paint();
    g.input();
    getch();
    f.close();
    closegraph();

}


void Display::paint()
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
	    if(gm.getMatrix()[i][j]==EMPTY)
		outtextxy(startx+PIXEL*i+PIXEL/2,starty+PIXEL*j+PIXEL/2,"");
	    else
		outtextxy(startx+PIXEL*i+PIXEL/2,starty+PIXEl*j+PIXEL/2,gm.getMatrix[i][j]+"");

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
	switch(inp)
	{
		case keyn://NEW GAME
		case keyN:
			 grid.reset();
			 paint();
			 //input(); I think it May cause infinite recursion unnecessarily!!!
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
	paint();
    } while(inp!=keyx && inp!=keyX && isNextMovePoss());
	//***************************************************TODO display gameover message.

}

void Display::update(int ctrl)
{
    //UPDATE PROCESS
    gm.move(ctrl);
    //paint(); Moved to the just before do while ends
    //input(); Infinite recursion only.
    //Call paint() at end of update
}

void Display::save()
{
    file.seekg(sizeof(int),ios::beg);

    file.write((char*)&gm,sizeof(Grid));
}

void Display::load()
{
    file.seekg(sizeof(int),ios::beg);

    file.read((char*)&gm,sizeof(Grid));
    //gm=temp;
    //paint(); Moved to before do while ends
}
