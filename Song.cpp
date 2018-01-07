#define _CRT_SECURE_NO_WARNINGS
#include "song.h"
#include "myutil.h"


song::song()
{

	title = new char[1];
	artist = new char[1];
	min = 0;
	sec = 0;
	album = new char[1];
}

song::~song()
{
	if (this->title)
	{
		delete[] this->title;
	}

	if (this->artist)
	{
		delete[] this->artist;
	}

	if (this->album)
	{
		delete[] this->album;
	}



}

const song& song::operator= (const song& song)
{

	if (this == &song)
		return *this;

	if (this->title)
	{
		delete[] this->title;
	}

	if (this->artist)
	{
		delete[] this->artist;
	}

	if (this->album)
	{
		delete[] this->album;
	}


	this->title = new char[strlen(song.title) + 1];
	strcpy(this->title, song.title);

	this->artist = new char[strlen(song.artist) + 1];
	strcpy(this->artist, song.artist);

	this->album = new char[strlen(song.album) + 1];
	strcpy(this->album, song.album);

	this->min = song.min;

	this->sec = song.sec;

	return *this;

}
