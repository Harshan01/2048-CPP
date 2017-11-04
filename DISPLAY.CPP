#ifndef DISPLAYCPP
#define DISPLAYCPP

#include"DISPLAY.H"

//Constructor opens the file on which save/load can be performed any time.
Display :: Display()
{
    file.open(SAVEPATH, ios::binary | ios::in | ios::ate | ios::out);
}

//This function is constantly called to refresh the screen with score and grid.
void Display::paint()
{
	int i, j, val;
	//Create the string which represents the line break after each row.
	char rowBreak[5 * SIZE + 1]="+";
	const char *colBreak = "| ";
	for(i = 0 ; i < SIZE ; ++i)
	strcat(rowBreak, "----+");
	//Flush existing screen contents.
	clrscr();
	
	cout << "\n\n\n\n\t\tScore : " << grid.getScore() << endl;
	
	//SIZE+1 rowBreaks needed . so one out of loop
	cout << "\t\t" << rowBreak << endl <<"\t\t";
	for(i = 0 ; i < SIZE ; ++i)
	{
		for( j = 0 ; j < SIZE ; ++j)
		{
			val = grid.getMatrix()[i][j];
			cout << colBreak ;
			if(val == EMPTY)
				cout << setw(3) << " ";
			else
				cout << setw(3) << val;
		}
		//SIZE+1  colBreaks also needed. Similarly,
		cout << colBreak << endl << "\t\t" << rowBreak << endl <<"\t\t";
	}
}

/*This function is called once all initializations are over and the game has started. This takes input forever 
**till game ends or uses chooses to. */
void Display :: input()
{
	char inp;
	do
	{
		inp = getch();
		switch(inp)
		{
		case keyn://NEW GAME
		case keyN:
			grid.reset();
			paint();
			break;

		case keyp://SAVE GAME
		case keyP:
			save();
			break;
			
		case keyl://LOAD GAME
		case keyL:
			load();
			break;
				
		case keyw:
		case keyW:
			update(UP);
			break;

		case keya:
		case keyA:
			update(LEFT);
			break;

		case keys:
		case keyS:
			update(DOWN);
			break;

		case keyd:
		case keyD:
			update(RIGHT);
			break;
		}
		paint();
	} while(inp != keyx && inp != keyX && grid.isNextMovePossible());
	//Display game over message, high score(update if new highscore is made) and stuff.
	cout << "Game Over! Press any key.";
	inp = getch();
	int score = grid.getScore();
	clrscr();
	cout << "\n\n\nGAME OVER!!!\nYour score is : " << score;
	file.seekg(0, ios::beg);
	int high;
	file.read((char*)&high, sizeof(int));
	if(score > high)
	{
		cout << "\n\n\nNEW HIGH SCORE!!!";
		file.seekp(0, ios::beg);
		file.write((char*)&score, sizeof(int));
	}
	else
		cout << "\n\n\nHigh score:" << high;
}

void Display :: update(int ctrl)
{
    grid.move(ctrl);    
}

void Display :: save()
{
    file.seekp(sizeof(int), ios::beg);
    grid.save(file);
}

void Display :: load()
{
    file.seekg(sizeof(int), ios::beg);
    grid.load(file);
}
Display :: ~Display()
{
    file.close();
}

#endif