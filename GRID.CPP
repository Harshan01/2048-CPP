#ifndef GRIDCPP
#define GRIDCPP

#include"GRID.H"

//Constructor initializes the ptr to ptr with a 2D array filled with EMPTY
Grid :: Grid()
{
    score = 0;
    matrix = new int*[SIZE];
    for(int i = 0; i < SIZE; i++)
    {
		matrix[i] = new int[SIZE];
		for(int j = 0; j < SIZE; j++)
			matrix[i][j] = EMPTY;
    }
    newNumber();
}

//Destructor frees up the dynamically allocated memory.
Grid :: ~Grid()
{
    for(int i = 0; i < SIZE; ++i)
		delete matrix[i];
    delete matrix;
}

//Function return TRUE if any new move can be made, FALSE otherwise which is used to compute end of the game.
int Grid :: isNextMovePossible()
{
    //IF any box empty or any two adjacent elements in matrix are equal then possible.
    //Checking of that is not implemented efficiently, can be optimized later.
    int i, j;
	for(i = 0 ; i < SIZE ; ++i)
		for(j = 0 ; j < SIZE ; ++j)
			if(matrix[i][j] == EMPTY)
				return TRUE;
    for(i = 0; i < SIZE ; ++i)
    {
		for( j = 0; j < SIZE - 1 ; ++j)
			if(	matrix[i][j] == matrix[i][j+1])
				return TRUE;
    }
	for(i = 0; i < SIZE-1 ; ++i)
    {
		for( j = 0; j < SIZE ; ++j)
			if(matrix[i][j] == matrix[i + 1][j])
				return TRUE;
    }
    return FALSE;
}

//This function is called whenever any move is made.
//Argument is an integer which represents direction of move.
void Grid :: move(int key)
{
    int i,j, k, noOfBlanks;
	//Just in case, if no move is possible, revert.
    if(!isNextMovePossible())
		return;
	//Make a copy of the current state. This will be used to compare later so that if any new move has been made,
	int temp[SIZE][SIZE];
	for(i = 0; i < SIZE; ++i)
		for(j = 0; j < SIZE; ++j)
			temp[i][j] = matrix[i][j];
	/*
	**Working Rule: Whatever may be the move direction we have to operate on the matrix row by row
	**or column by column. And functions should be passsed the addresses to get the changes reflected.
	**So an array of pointers for each row is created in order such that a right move on 
	**the array treated as row is equivalent to the desired move on the row or column.
	**
	**Since each for[Direction]() returns a dynamically allocated array, it is necessary to free the memory back
	**before any another assignment to the pointer.
	**/
    int **p;
	for(i = 0; i < SIZE; ++i)
	{
		p = forDirection(matrix, key, i);
		score += action(p);
		delete p;
	}
	//Call newNumber to generate a random number somewhere, if move was actually made.
	int flag=FALSE;
	for(i = 0; i < SIZE && !flag ; ++i)
		for(j = 0; j < SIZE && !flag ; ++j)
			if(temp[i][j] != matrix[i][j])
			{
				flag = TRUE;
			}
	if(flag)
		newNumber();
}


//This function is called to generate a random number somewhere in the matrix.
void Grid :: newNumber()
{
	int i, j, noOfBlanks = 0;
	//Make an array of (i,j) where boxes are empty. ie numbers can be inserted only on empty boxes.
	int emptyIJ[SIZE * SIZE][2];
	for(i = 0; i < SIZE; ++i)
	{	for(j = 0; j < SIZE; ++j)
		{
			if(matrix[i][j] == EMPTY)
			{
				emptyIJ[noOfBlanks][0]=i;
				emptyIJ[noOfBlanks][1]=j;
				noOfBlanks++;
			}
		}
	}
	//If there is no room to create a number, then don't!
	if(noOfBlanks == 0)
		return;
	//Generate two random numbers one for 2 or 4, other which will indicate position in the array.
	//By design, 2 occurs thrice as likely as 4 occuring. So at 25% probability, assign val=4. Rest of the cases, 2
	int val = random(4);//val takes 0,1,2,3
	if(val == 3)
		val = 4;
	else
		val = 2;
	//Generate a random number which indicates a blank space in the previously generated list.
	i = rand() % noOfBlanks;
	//Update that particular spot with val
	matrix[ (emptyIJ[i][0]) ][ (emptyIJ[i][1]) ]=val;
}

int** Grid :: getMatrix() {
	return matrix;
}

//save function saves score and the matrix. This is called only after seeking to the desired position in file.
void Grid :: save(fstream &file)
{
	file.write((char *)&score, sizeof(int));
	for(int i = 0; i < SIZE; ++i)
		for(int j = 0; j < SIZE; ++j)
			file.write((char *)&matrix[i][j], sizeof(int));
}

//load function loads the score and the matrix. This also assumes the file pointer is already at appropriate position.
void Grid :: load(fstream &file)
{
	file.read((char *)&score, sizeof(int));
	for(int i = 0; i < SIZE; ++i)
		for(int j = 0; j < SIZE; ++j)
			file.read((char *)&matrix[i][j], sizeof(int));
}

int Grid :: getScore() {
	return score;
}

//This function resets score to zero and fills each cell in the matrix with EMPTY.
//After that, this also calls newNumber to place a new number somewhere.
void Grid :: reset()
{
     score = 0;
     for(int i = 0; i < SIZE; i++)
     {
	    for(int j = 0; j < SIZE; j++)
		 matrix[i][j] = EMPTY;
     }
     newNumber();
}

/**
** As mentioned earlier, these forRight, forLeft, forUp, forDown functions take the matrix 
** and the ith row or column as argument and creates an array of pointers on which if right move 
** is performed becomes equivalent.
**/
int** forDirection(int** matrix, int direction, int i)
{
	switch(direction)
	{
		//break statement not needed here.
		case UP: return forUp(matrix, i);
		case DOWN: return forDown(matrix, i);
		case LEFT: return forLeft(matrix, i);
		case RIGHT: return forRight(matrix, i);
	}
}
int **forRight(int **_2D, int i)//SIZExSIZE, to delete return value after ysing
{
	int **p = new int*[SIZE];
	for(int j = 0; j < SIZE;++j)
		p[j] = &_2D[i][j];
	return p;
}
int **forLeft(int **_2D, int i)//SIZExSIZE, to delete return value after ysing
{
	int **p = new int*[SIZE];
	for(int j = SIZE - 1 ; j >= 0; --j)
		p[j] = &_2D[i][SIZE - 1 - j];
	return p;
}
int **forDown(int **_2D, int j)//SIZExSIZE, to delete return value after ysing
{
	int **p = new int*[SIZE];
	for(int i = 0; i < SIZE; ++i)
		p[i] = &_2D[i][j];
	return p;
}
int **forUp(int **_2D, int j)//SIZExSIZE, to delete return value after ysing
{
	int **p = new int*[SIZE];
	for(int i = SIZE-1 ; i >= 0 ; --i)
		p[i] = &_2D[SIZE - 1 - i][j];
	return p;
}

//This function takes an array of pointers (representing eq. right array) and pushes elements to right
// removing blanks.
//This removes blank spaces at indices >= 1.
void removeEmpty(int **p)
{
	int i, j, noOfBlanks;
	//Since many blanks may be consecutive, counting no of blanks and then looping for each one will be
	//better than looping each element.
	for(i = 1, noOfBlanks = 0; i < SIZE; ++i)
		if(*p[i] == EMPTY)
			noOfBlanks++;
		
	for(i = SIZE - 1; noOfBlanks > 0 ;)
	{
		//If any empty cell is encountered, shift the entire array in the left to the right by 1 place,
		//leaving the leftmost one with an EMPTY.
		if(*p[i] == EMPTY)
		{
			for(j = i; j >= 1; --j)
			{
				*p[j] = *p[j - 1];
				*p[j - 1] = EMPTY;
			}
			--noOfBlanks;
		}
		//Else, move on to the next cell.
		else
			--i;
	}
}

//This takes the equivalent right movable array of pointers and performs the right move.
//Returns the resultant increase in score.
int action(int **p)
{
	int i, addScore = 0;
	//Step 1: Remove blank spaces at indices >= 1
	removeEmpty(p);
	//Step 2: If two equal numbers are adjacent add them and put in right most. Also reflect it in score.
	for(i = SIZE - 1; i >= 0; --i)
	{
		if(*p[i] == *p[i - 1] && *p[i] != EMPTY)
		{
			addScore += (*p[i]) *= 2;
			*p[i-1] = EMPTY;
			--i;
		}
	}
	//Step 3: Remove blank spaces again
	removeEmpty(p);
	return addScore;
}
#endif