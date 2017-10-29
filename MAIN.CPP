#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<fstream.h>

#include"CONSTANT.H"
#include"GRID.CPP"
#include"DISPLAY.CPP"

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
    settextstyle(14, HORIZ_DIR, 1);
    Display g;
    g.paint();
    g.input();
    getch();
    f.close();
    closegraph();

}


