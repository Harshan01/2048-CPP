#include"GRID.H"
#include"stdlib.h"
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

    //Working rule:
    //In the direction of movement, remove empty space between, add elements if possible, remove empty space again
    switch(key)
    {
    case RIGHT:
	for(i=0;i<SIZE; ++i)
	{
	    //Step 1: Remove blank spaces at indices >= 1
	    for(j=1, noOfBlanks=0; j<SIZE;++j)
			if(matrix[i][j]==EMPTY)
				noOfBlanks++;
	    for(j=SIZE-1; j>=1 && noOfBlanks > 0 ;++j)
	    {
			if(matrix[i][j]==EMPTY)
			{
				for(k=j; k>=1; --k)
				{
				matrix[i][k]=matrix[i][k-1];
				matrix[i][k-1]=EMPTY;
				}
				--noOfBlanks;
			}
	    }
	    //Step 2: If two equal numbers are adjacent add them and put in right most
	    for(j=0; j< SIZE-1; ++j)
	    {
			if(matrix[i][j]==matrix[i][j+1])
			{
				score+=matrix[i][j+1]*=2;
				matrix[i][j]=EMPTY;
				++j;
			}
	    }
	    //Step 3:Remove spaces again
	    for(j=1, noOfBlanks=0; j<SIZE;++j)
			if(matrix[i][j]==EMPTY)
				noOfBlanks++;
	    for(j=SIZE-1; j>=1 && noOfBlanks > 0 ;++j)
	    {
			if(matrix[i][j]==EMPTY)
			{
				for(k=j; k>=1; --k)
				{
					matrix[i][k]=matrix[i][k-1];
					matrix[i][k-1]=EMPTY;
				}
				--noOfBlanks;
			}
	    }
	}
	break;
	//for left
	case LEFT:
	for(i=0;i<SIZE; ++i)
	{
	    //Step 1: Remove blank spaces at indices <= size -2
	    for(j=SIZE-2, noOfBlanks=0; j>=0;--j)
			if(matrix[i][j]==EMPTY)
				noOfBlanks++;
	    for(j=0; j<=SIZE-2 && noOfBlanks > 0 ;--j)
	    {
			if(matrix[i][j]==EMPTY)
			{
				for(k=j; k<=SIZE-2; ++k)
				{
					matrix[i][k]=matrix[i][k+1];
					matrix[i][k+1]=EMPTY;
				}
				--noOfBlanks;
			}
	    }
	    ////////////////////////////////////////
	    for(j=SIZE - 1; j> 0; --j)
	    {
			if(matrix[i][j]==matrix[i][j-1])
			{
				score+=matrix[i][j-1]*=2;
				matrix[i][j]=EMPTY;
				--j;
			}
	    }
	    //Step 3:Remove spaces again
	    for(j=SIZE-2, noOfBlanks=0; j>=0;--j)
			if(matrix[i][j]==EMPTY)
				noOfBlanks++;
	    for(j=0; j<=SIZE-2 && noOfBlanks > 0 ;--j)
	    {
			if(matrix[i][j]==EMPTY)
			{
				for(k=j; k<=SIZE-2; ++k)
				{
				matrix[i][k]=matrix[i][k+1];
				matrix[i][k+1]=EMPTY;
				}
				--noOfBlanks;
			}
	    }
	}
	break;

	//for up, replace matrix[a][b] with matrix[b][a] in left
	case UP:
	for(i=0;i<SIZE; ++i)
	{
	    //////////////////////////////////////
	    for(j=SIZE-2, noOfBlanks=0; j>=0;--j)
			if(matrix[j][i]==EMPTY)
				noOfBlanks++;
	    for(j=0; j<=SIZE-2 && noOfBlanks > 0 ;--j)
	    {
			if(matrix[j][i]==EMPTY)
			{
				for(k=j; k<=SIZE-2; ++k)
				{
					matrix[k][i]=matrix[k+1][i];
					matrix[k+1][i]=EMPTY;
				}
				--noOfBlanks;
			}
	    }
	    ////////////////////////////////////////////
	    for(j=SIZE - 1; j> 0; --j)
	    {
			if(matrix[j][i]==matrix[j-1][i])
			{
				score+=matrix[j-1][i]*=2;
				matrix[j][i]=EMPTY;
				--j;
			}
	    }
	    /////////////////////////////////
	     for(j=SIZE-2, noOfBlanks=0; j>=0;--j)
			if(matrix[j][i]==EMPTY)
				noOfBlanks++;
	    for(j=0; j<=SIZE-2 && noOfBlanks > 0 ;--j)
	    {
			if(matrix[j][i]==EMPTY)
			{
				for(k=j; k<=SIZE-2; ++k)
				{
					matrix[k][i]=matrix[k+1][i];
					matrix[k+1][i]=EMPTY;
				}
				--noOfBlanks;
			}
	    }
	}
	break;
	 case DOWN:
	for(i=0;i<SIZE; ++i)
	{
	    /////////////////////////
	    for(j=1, noOfBlanks=0; j<SIZE;++j)
			if(matrix[j][i]==EMPTY)
				noOfBlanks++;
	    for(j=SIZE-1; j>=1 && noOfBlanks > 0 ;++j)
	    {
			if(matrix[j][i]==EMPTY)
			{
				for(k=j; k>=1; --k)
				{
				matrix[k][i]=matrix[k-1][i];
				matrix[k-1][i]=EMPTY;
				}
				--noOfBlanks;
			}
	    }
	   ///////////////
	    for(j=0; j< SIZE-1; ++j)
	    {
			if(matrix[j][i]==matrix[j+1][i])
			{
				score+=matrix[j+1][i]*=2;
				matrix[j][i]=EMPTY;
				++j;
			}
	    }
	     /////////////////////////
	    for(j=1, noOfBlanks=0; j<SIZE;++j)
			if(matrix[j][i]==EMPTY)
				noOfBlanks++;
	    for(j=SIZE-1; j>=1 && noOfBlanks > 0 ;++j)
	    {
			if(matrix[j][i]==EMPTY)
			{
				for(k=j; k>=1; --k)
				{
				matrix[k][i]=matrix[k-1][i];
				matrix[k-1][i]=EMPTY;
				}
				--noOfBlanks;
			}
	    }
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
