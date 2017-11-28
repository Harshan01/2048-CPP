#include"CONSTANT.H"
#include"GRID.CPP"
#include"DISPLAY.CPP"

void main()
{
    clrscr();
    // Get the HIGH SCORE from file for displaying on home screen
    int high = 0;
    fstream f;
    f.open(SAVEPATH, ios::binary | ios::in | ios::ate);
	//If file doesnt exist (when game launched first time), create file with highscore=0;
    if(!f)
    {
	    f.open(SAVEPATH, ios::binary|ios::out|ios::in|ios::ate);
	    f.write( (char*)(new int(0)), sizeof(int) );
	    Grid t;
	    f.write( (char *)&t, sizeof(Grid) );
    }
    f.seekg(0, ios::beg);
    f.read( (char*)&high, sizeof(int) );
	f.close();

	//Without this Grid::newNumber() can't work.
    randomize();

    char inp;
    constream cout;
    cout << setclr(LIGHT_GREEN);
    cout << "                                    2048 GAME\n\n";
    cout << setclr(LIGHT_RED) << "    HIGH SCORE: " << high << "\n\n\n"; //<--high score
    cout << setclr(WHITE) << "    Help:\n" << setclr(LIGHT_AQUA) <<"    N-New game.\n    L-Load Game.\n    P-Save game.\n    X-Exit game.\n    Use WASD to move\n    Press any key to Start.\n    ";
    getch();

	//Instantiate Display object and boot the game.
    Display g;
	g.paint();
    g.input();

	//Game ended. :)
    getch();
}


