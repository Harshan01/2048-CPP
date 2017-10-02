#include"CONSTANT.H"
#include<fstream.h>
class Grid
{
private:
    int **matrix;
    int score;
public:
    //Default constructor to intialize matrix elements to zero
    Grid();
    //Function is called when a move is made so as to update the matrix
    //Arguments: int key- integer specifying the direction . ref constants.h
    void move(int key);
    //Function is called to know if next move is possible.
    //Return value: TRUE if possible
    //		  : FALSE if not
    int isNextMovePossible();
    //Function to generate a random number at empty space every move
    void newNumber();
    //Function that returns the matrix as int **
    //Return value:matrix
    int** getMatrix();
    //Function to get the score
    //Return value: score
    int getScore();
    //Function to reset grid
    void reset();
	//functions  to read/write from/into files
   void save(fstream &file);
   void load(fstream &file);
    //Destructor to free up 2D array
    ~Grid();
};
//ostream& operator<<(ostream&, Grid&);
//istream& operator>>(istream&, Grid&);
