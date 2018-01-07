#ifndef DB_H
#define DB_H

#include <cstring>
#include <fstream>
#include "myutil.h"
#include "song.h"

const int MAX_NUM = 101;
const int GROWTH_FACTOR = 2;

class songidx
{
public:

	songidx();
	void selection(songidx& sidx);

	~songidx();

	void displayindex(songidx sidx, int songcount); 
	void searchalbum(songidx sidx);
	void searchartist(songidx sidx, int songcount);
	void assignarray(songidx& sidx); 



private:

	int songcount;
	int currcapacity;
	int idxcount = 0;

	struct node
	{
		song data;
		node * next;
	};
	node * head, *tail;

	//need to get rid of all the array stuff and change them to node stuff
	//song * list;  //[MAX_NUM];

	int numofsongs();

	//will need to cycle through 
	void writeindex();
	
	//void songidx::growarray(); //wont need this

};

#endif 
