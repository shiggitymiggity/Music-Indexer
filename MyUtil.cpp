#include "myutil.h"
#include "db.h"
#include "song.h"

//The menu options

void displaymenu() {

	cout << "SONG INDEX";
	cout << endl;
	cout << "What would you like to do?" << endl;
	cout << endl;
	cout << "display - Display information for all songs." << endl;
	cout << "artist - Display songs by artist." << endl;
	cout << "album - Display songs by album." << endl;
	cout << "new - Enter information for a new song." << endl;
	cout << "delete - Remove song from index." << endl;
	cout << "quit - Exit the program." << endl;
	cout << endl;

}


//Cstring char counter

int charcntr(char line[])
{
	int charcnt;
	int idx;

	charcnt = 0;
	for (idx = 0; line[idx]; idx++)
	{
		if (line[idx] != '\0')
		{
			charcnt++;
		}
	}

	return charcnt;
}
