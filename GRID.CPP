#include"GRID.H"
#include"CONSTANT.H"
#include"stdlib.h"
int **forRight(int **_2D, int i);
int action(int **p);
int **forLeft(int **_2D, int i);
int **forUp(int **_2D, int i);
int **forDown(int **_2D, int i);
Grid::Grid()
{
     score=0;
     matrix=new int*[SIZE];
     for(int i=0; i<SIZE; i++)
     {
	matrix[i]=new int[SIZE];
	for(int j=0; j< SIZE; j++)
	    matrix[i][j]=EMPTY;
     }
     newNumber();
}
Grid::~Grid()
{
     for(int i=0;i<SIZE;++i)
	delete matrix[i];
     delete matrix;
}
int Grid::isNextMovePossible()
{
    //IF any box empty or any two adjacent elements in matrix are equal then possible.
    //Checking of that is not implemented efficiently, can be optimized later.
    int i, j;
    for(i=0; i< SIZE-1; ++i)
    {
	for(j=0; j< SIZE-1; ++j)
	    if(matrix[i][j]==EMPTY || matrix[i][j] == matrix[i+1][j] ||
		matrix[i][j] == matrix[i][j+1])
			return TRUE;
    }
    return FALSE;
}
void Grid::move(int key)
{
    int i,j, k, noOfBlanks;
    if(!isNextMovePossible())
	return;

    int **p;
    switch(key)
    {
    case RIGHT:
		for(i=0;i<SIZE; ++i)
		{
			p=forRight(matrix, i);
			score+=action(p);
			delete p;
		}
		break;
	case LEFT:
		for(i=0;i<SIZE; ++i)
		{
			p=forLeft(matrix, i);
			score+=action(p);
			delete p;
		}
		break;
	case UP:
		for(i=0;i<SIZE; ++i)
		{
			p=forUp(matrix, i);
			score+=action(p);
			delete p;
		}
		break;
	case DOWN:
		for(i=0;i<SIZE; ++i)
		{
			p=forDown(matrix, i);
			score+=action(p);
			delete p;
		}
		break;
	}
	//Call newNumber to generate a random number somewhere.
	newNumber();
}
void Grid::newNumber()
{
	int i, j, noOfBlanks=0;
	//Make an array of (i,j) where boxes are empty
	int emptyIJ[SIZE*SIZE][2];
	for(i=0; i< SIZE; ++i)
		for(j=0; j< SIZE; ++j)
		{
			if(matrix[i][j]==EMPTY)
			{
				emptyIJ[noOfBlanks][0]=i;
				emptyIJ[noOfBlanks][1]=j;
				noOfBlanks++;
			}
		}
	//Generate two random numbers one for 2 or 4, other which will indicate position in the array.
	randomize();
	int val=random(4);//val takes 0,1,2,3
	if(val==3)
		val=4;
	else
		val=2;
	i=random(noOfBlanks);
	//Update that particular spot with val
	matrix[ emptyIJ[i][0] ][ emptyIJ[i][1] ]=val;
}
int** Grid::getMatrix()
{
	return matrix;
}
int Grid::getScore()
{
	return score;
}
void Grid::reset()
{
     score=0;
     for(int i=0; i<SIZE; i++)
     {
	    for(int j=0; j< SIZE; j++)
		 matrix[i][j]=EMPTY;
     }
     newNumber();
}
int **forRight(int **_2D, int i)//SIZExSIZE, to delete return value after ysing
{
	int **p=new int*[SIZE];
	for(int j=0;j<SIZE;++j)
		p[j]=&_2D[i][j];
	return p;
}
int **forLeft(int **_2D, int i)//SIZExSIZE, to delete return value after ysing
{
	int **p=new int*[SIZE];
	for(int j=SIZE-1;j>=0;--j)
		p[j]=&_2D[i][SIZE-1-j];
	return p;
}
int **forDown(int **_2D, int j)//SIZExSIZE, to delete return value after ysing
{
	int **p=new int*[SIZE];
	for(int i=0;i<SIZE;++i)
		p[i]=&_2D[i][j];
	return p;
}
int **forUp(int **_2D, int j)//SIZExSIZE, to delete return value after ysing
{
	int **p=new int*[SIZE];
	for(int i=SIZE-1 ; i>=0 ; --i)
		p[i]=&_2D[SIZE-1-i][j];
	return p;
}
void removeEmpty(int **p)
{
	int i, j, noOfBlanks;
	for(i=1, noOfBlanks=0; i<SIZE;++i)
		if(*p[i]==EMPTY)
			noOfBlanks++;
	for(i=SIZE-1; i>=1 && noOfBlanks > 0 ;--i)
	{
		if(*p[i]==EMPTY)
		{
			for(j=i; j>=1; --j)
			{
				*p[j]=*p[j-1];
				*p[j-1]=EMPTY;
			}
			--noOfBlanks;
		}
	}
}

int action(int **p)
{
	int i, addScore=0;
	//Step 1: Remove blank spaces at indices >= 1
	removeEmpty(p);
	//Step 2: If two equal numbers are adjacent add them and put in right most
	for(i=SIZE-1; i>=0; --i)
	{
		if(*p[i]==*p[i-1])
		{
			addScore+=(*p[i])*=2;
			*p[i-1]=EMPTY;
			--i;
		}
	}
	//Step 3: Remove blank spaces again
	removeEmpty(p);
	return addScore;
}
