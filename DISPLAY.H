#ifndef DISPLAYHPP
#define DISPLAYHPP


#include<string.h>
#include<graphics.h>
#include"CONSTANT.H"
#include"GRID.H"

char *SAVEPATH="SAVEDATA.DAT";

class Display
{
	Grid gm;
	fstream file;
	int startx,starty,endx,endy;

public:

	Display();

    void paint(); //Paint the grid

    int isNextMovePoss(); //Calculates if next move is possible

    void input(); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(); //Save game and store in binary file

    void load(); //Load saved game

	~Display();

};
#endif