#ifndef DISPLAYCPP
#define DISPLAYCPP

#include"DISPLAY.H"
#include<fstream.h>

Display::Display()
  {
     file.open(SAVEPATH, ios::binary | ios::in | ios::ate | ios::out);
     startx=getmaxx()/2 - (int)(SIZE*PIXEL/2);
     endx=getmaxx()/2 + (int)(SIZE*PIXEL/2);
     starty=getmaxy()/2 - (int)(SIZE*PIXEL/2);
     endy=getmaxy()/2 + (int)(SIZE*PIXEL/2);
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
    inp=getch();
    cleardevice();
	//***************************************************display gameover message.
  //  cleardevice();

   // clrscr();
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
Display::~Display()
{
      file.close();
}
#endif