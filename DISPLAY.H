#ifndef DISPLAYHPP
#define DISPLAYHPP

#include"CONSTANT.H"
#include"GRID.H"

char *SAVEPATH = "SAVEDATA.DAT";

class Display
{
protected:
	Grid grid;
	fstream file;

public:

	Display();

    void paint(); //Paint the grid

    void input(); //Input data from user

    void update(int); //Update the grid tiles and move

    void save(); //Save game and store in binary file

    void load(); //Load saved game

	~Display();

};
#endif