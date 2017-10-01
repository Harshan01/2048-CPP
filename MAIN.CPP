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
	int startx,starty,endx,endy;

public:

  Display()
  {
     file.open(SAVEPATH,ios::binary|ios::in|ios::ate);
     startx=getmaxx()/2 - (int)((float)SIZE*PIXEL/2);
     endx=getmaxx()/2 + (int)((float)SIZE*PIXEL/2);
     starty=getmaxy()/2 - (int)((float)SIZE*PIXEL/2);
     endy=getmaxy()/2 + (int)((float)SIZE*PIXEL/2);
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
	    f.open(SAVEPATH, ios::binary|ios::out);
	    f.write((char*)(new int(0)), sizeof(int));
	    Grid t;
	    f.write((char *)&t, sizeof(Grid));
    }
    f.seekg(0,ios::beg);
    f.read((char*)&high, sizeof(int));



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
    closegraph();

}


void Display::paint()
{
    
    cleardevice();
    //setfillstyle(SOLID_FILL,LIGHTBLUE);
    
    //int vert[]={startx,starty,endx,starty,endx,endy,startx,endy};
    //fillpoly(4,vert);
    rectangle(startx,starty,endx,endy);	
    char *temp;

    for(int i=0;i<SIZE;i++)
    {
	    line(startx, starty+PIXEL*(i+1), endx, starty+PIXEL*(i+1));
	    line(startx+PIXEL*(i+1), starty, startx+PIXEL*(i+1), endy);
	for(int j=0;j<SIZE;j++)
	{

	    sprintf(temp, "%d", gm.getMatrix()[i][j]);
	    if(gm.getMatrix()[i][j]==EMPTY)
		outtextxy(startx+PIXEL*j+PIXEL/2,starty+PIXEL*i+PIXEL/2," ");
	    else
		outtextxy(startx+PIXEL*j+PIXEL/2,starty+PIXEL*i+PIXEL/2,temp);

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
	paint();
    } while(inp!=keyx && inp!=keyX && isNextMovePoss());
	//***************************************************display gameover message.

    clrscr();
	cout<<"\n\n\n\t\t\tGAME OVER!!! No other possible moves left! Your score is : "<<gm.getScore();
	file.seekg(0,ios::beg);
	int high;
	file.read((char*)&high, sizeof(int));
	if(gm.getScore()>high)
	{
	    cout<<"\n\n\nNEW HIGH SCORE!!!";
		file.seekg(0,ios::beg);
	    file.write((char*)&high,sizeof(int));	
	}

}

void Display::update(int ctrl)
{
    //UPDATE PROCESS
    gm.move(ctrl);
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
