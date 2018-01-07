#ifndef SONG_H
#define SONG_H
#include "myutil.h"
//Song information

const int MAX_CHAR = 101;

class song
{
public:

		char * title;
		char * artist;
		int min;
		int sec;
		char * album;
		int index;

	song();
	const song& song::operator= (const song& song);
	~song();

private:


};

#endif

