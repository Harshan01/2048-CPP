#ifndef GRIDHPP
#define GRIDHPP

#include"CONSTANT.H"

int **forDirection(int **matrix, int, int);
int **forRight(int **matrix, int i);
int **forLeft(int **matrix, int i);
int **forUp(int **matrix, int i);
int **forDown(int **matrix, int i);
int action(int **p);

class Grid
{
private:
    int **matrix;
    int score;
public:
//Refer GRID.CPP for comments regarding what the functions do.
    Grid();
    void move(int key);
    int isNextMovePossible();
    void newNumber();
    int** getMatrix();
    int getScore();
    void reset();
	void save(fstream &file);
    void load(fstream &file);
    ~Grid();
};
#endif
