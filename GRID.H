#include"constants.h"
class Grid
{
    int matrix[SIZE][SIZE];
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
};