#define _CRT_SECURE_NO_WARNINGS
#include "db.h"
#include "myutil.h"
#include "song.h"


/*
void songidx::growarray()
{


	//allocate bigger array
	currcapacity = currcapacity * GROWTH_FACTOR;
	song * temp = new song[currcapacity];

	//copy over the elements
	for (int index = 0; index < songcount; index++)
	{
		this->list[index] = list[index];
	}

	//delete original array
	delete[] list;

	//point to new array
	list = temp;

}
*/

songidx::songidx()
{
	songcount = numofsongs();
	//currcapacity = numofsongs();
	//list = new song[currcapacity]; //wont need this
	head = nullptr;
	tail = nullptr;

}

songidx::~songidx()
{
	

	//destroy the linked list
	
	/*
	node * curr = head;
	while (curr != nullptr)
	{
		head = curr->next;
		delete curr;
		curr = head;

	}

	tail = nullptr;
	
	*/

}

void songidx::writeindex()
{
	
	fstream out;
	int idx = 0;
	node * curr = head;

	out.open("songs.txt", ios::out);
	if (out.is_open())
	{
		//just use single pointer traverse and cout while(curr)...

		while (idx != songcount) //idx != songcount changed from this
		{

			out << curr->data.title << ";";
			out << curr->data.artist << ";";
			out << curr->data.min << ";";
			out << curr->data.sec << ";";
			out << curr->data.album << endl;
			idx++;

			curr = curr->next;

		}
	}
	out.clear();
	out.close();
	
}

//Load index to memory

//Filling the fields using ";" and a delimeter

void songidx::assignarray(songidx& sidx) {
	fstream in;

	in.open("songs.txt", ios::in); //Index file check
	if (!in.is_open())
	{
		cout << endl;
		cout << "No songs.txt index file." << endl;
		cout << endl;
	}

	if (in.is_open())
	{
		char line[MAX_CHAR];
		int time;
		int section = 0;
		int idx = 0;
		int count = 0;
		node * curr = head;

		ifstream in("songs.txt");
		if (in.is_open())
		{
			while (idx != songcount) 
			{
				node * newnode = new node;
				newnode->next = nullptr;
				node * pre = nullptr;
				curr = head; 

				in.getline(line, MAX_CHAR, ';');
				delete[] newnode->data.title; //deallocate pointer memory 				
				newnode->data.title = new char[strlen(line) + 1]; //change string size
				strcpy(newnode->data.title, line); //copy string 

				in.getline(line, MAX_CHAR, ';');
				delete[] newnode->data.artist; //deallocate pointer memory
				newnode->data.artist = new char[strlen(line) + 1]; //change string size
				strcpy(newnode->data.artist, line);

				in.getline(line, MAX_CHAR, ';');
				time = atoi(line);
				newnode->data.min = time;

				in.getline(line, MAX_CHAR, ';');
				time = atoi(line);
				newnode->data.sec = time;

				in.getline(line, MAX_CHAR, '\n');
				delete[] newnode->data.album; //deallocate pointer memory
				newnode->data.album = new char[strlen(line) + 1]; //change string size
				strcpy(newnode->data.album, line);
				section = 0;
				idx++;

				//append to end
				if (!head)
				{
					head = newnode;
					tail = newnode; //added this
				}
				else
				{
					while (curr->next != nullptr) 
					{
						curr = curr->next;
					}
					curr->next = newnode;
					tail = newnode;
				}

				newnode->data.index = idxcount;
				idxcount++;

			}
			in.close();
			cout << endl;
		}
	}
	in.clear();
	in.close();
}

//Number of songs in index

//counting the newline char at the end of every song line

int songidx::numofsongs() {
	int songcount = 0;
	char byte;
	fstream in;

	in.open("songs.txt", ios::in); //Index file check
	if (!in.is_open())
	{
		cout << endl;
		cout << "No songs.txt index file." << endl;
		cout << endl;
	}

	if (in.is_open())
	{
		while ((byte = in.get()) != EOF)
		{
			if (byte == '\n')
			{
				++songcount;
			}
		}
		in.close();
		cout << endl;
	}

	in.clear();
	in.close();

	return songcount;
}

//Looping menu

void songidx::selection(songidx& sidx) {

	int idxnum;
	char keyword[MAX_CHAR];
	bool stop = false;

	do {
		displaymenu();

		cin >> keyword;

		if (strcmp(keyword, "quit") == 0)
		{
			cin.ignore(100, '\n');

			cout << "Saving song index and exiting." << endl;

			writeindex();
			stop = true;
			break;
		}

		else if (strcmp(keyword, "display") == 0)
		{
			cin.ignore(100, '\n');
			cout << endl;
			displayindex(sidx, songcount);
		}

		else if (strcmp(keyword, "artist") == 0)
		{
			cin.ignore(100, '\n');
			cout << endl;
			searchartist(sidx, songcount);
		}

		else if (strcmp(keyword, "album") == 0)
		{
			cin.ignore(100, '\n');
			cout << endl;
			searchalbum(sidx);
		}

		else if (strcmp(keyword, "new") == 0)
		{
			cin.ignore(100, '\n');
			//newsong(sidx, songcount);
		}

		else if (strcmp(keyword, "delete") == 0)
		{
			cin.ignore(100, '\n');
			cout << "Whats the song's index #? " << endl << endl;
			cin >> idxnum;
			while (!cin)
			{
				cin.clear();
				cin.ignore(MAX_CHAR, '\n');
				cout << "Thats no number! Try again.";
				cin >> idxnum;
			}

			//delsong(idxnum, sidx, songcount);
		}

		else
		{
			cin.clear();
			cin.ignore(MAX_CHAR, '\n');
			cout << endl;
			cout << keyword << " isn't a valid selection." << endl;
			cout << "Try a valid selection this time." << endl;
			cout << "i.e.: display, artist, album, new, quit." << endl;
			cout << endl;
		}

	} while (stop == false);

}

//Display song list

void songidx::displayindex(songidx sidx, int songcount) {

	int idx = 0;
	node * curr = head;

	cout << "There are currently " << songcount << " songs on file." << endl << endl;

	while (idx != songcount)  
	{


		cout << "Index #: " << curr->data.index << endl;
		cout << "Title: " << curr->data.title << endl;
		cout << "Artist: " << curr->data.artist << endl;
		cout << "Duration: " << curr->data.min << ":" << curr->data.sec << endl;
		cout << "Album: " << curr->data.album << endl << endl;
		idx++;

		curr = curr->next;
	}
	cout << endl;

}

//Delete song from index

//will need to do an index # compare

/*
void songidx::delsong(int idxnum, songidx& sidx, int& songcount) {

	char keyword[MAX_CHAR];
	bool stop = false;

	cout << "Index #: " << idxnum << endl;
	cout << "Title: " << sidx.list[idxnum].title << endl;
	cout << "Artist: " << sidx.list[idxnum].artist << endl;
	cout << "Duration: " << sidx.list[idxnum].min << ":" << sidx.list[idxnum].sec << endl;
	cout << "Album: " << sidx.list[idxnum].album << endl << endl;
	cout << "Are you sure you want to delete this song from the index?" << endl;
	cout << "yes or no to exit." << endl << endl;

	do
	{
		cin >> keyword;
		cout << endl;

		

		if (strcmp(keyword, "yes") == 0)
		{
			for (int idx = idxnum; idx < songcount; idx++)
			{
				delete[] sidx.list[idx].title;
				sidx.list[idx].title = new char[strlen(sidx.list[idx + 1].title) + 1];
				strcpy(sidx.list[idx].title, sidx.list[idx + 1].title);

				delete[] sidx.list[idx].artist;
				sidx.list[idx].artist = new char[strlen(sidx.list[idx + 1].artist) + 1];
				strcpy(sidx.list[idx].artist, sidx.list[idx + 1].artist);

				sidx.list[idx].min = sidx.list[idx + 1].min;
				sidx.list[idx].sec = sidx.list[idx + 1].sec;

				delete[] sidx.list[idx].album;
				sidx.list[idx].album = new char[strlen(sidx.list[idx + 1].album) + 1];
				strcpy(sidx.list[idx].album, sidx.list[idx + 1].album);
			}
			songcount--;
			stop = true;
		}

		else if (strcmp(keyword, "no") == 0)
		{
			stop = true;
		}

		else
		{
			cout << keyword << " isn't a valid option." << endl;
			cout << "yes or no to exit." << endl;
		}
	} while (stop == false);
}

*/

//Add new songs to the list

/*

void songidx::newsong(songidx& sidx, int& songcount) {

	bool write = false;
	bool stop = false;
	bool go = false;
	char keyword[MAX_CHAR], title[MAX_CHAR], artist[MAX_CHAR], album[MAX_CHAR];
	int min, sec;

	

	do
	{
		cout << "Enter the song title." << endl;
		cin.getline(title, MAX_CHAR, '\n');

		cout << "Enter the name of the artist/group." << endl;
		cin.getline(artist, MAX_CHAR, '\n');

		cout << "Song durration: Enter the number of minutes." << endl;
		cin >> min;
		while (!cin)
		{
			cin.clear();
			cin.ignore(MAX_CHAR, '\n');
			cout << "That's no number! Try again: ";
			cin >> min;
		}
		cin.ignore(MAX_CHAR, '\n');

		cout << "Song duration: Enter the number of seconds in 2 digits between 0 and 59." << endl;
		cout << "Example: 09" << endl;
		cin >> sec;

		while (sec < 0 || sec > 59)
		{
			cout << "Not a valid number. Try again." << endl << endl;
			cin >> sec;
		}

		while (!cin)
		{
			cin.clear();
			cin.ignore(MAX_CHAR, '\n');
			cout << "That's no number! Try again";
			cin >> min;
		}
		cin.ignore(MAX_CHAR, '\n');

		cout << "Enter the name of the album." << endl;
		cin.getline(album, MAX_CHAR, '\n');

		cout << endl;
		cout << "Title: " << title << endl;
		cout << "Artist: " << artist << endl;
		cout << "Duration: " << min << ":" << sec << endl;
		cout << "Album: " << album << endl << endl;
		cout << "Is the song information correct?" << endl;
		cout << "yes - To save information." << endl;
		cout << "quit - To exit." << endl;
		cout << "retry - To input informaion again" << endl << endl;

		do
		{
			go = false;

			cin >> keyword;

			while (!cin)
			{
				cin.clear();
				cin.ignore(MAX_CHAR, '\n');
				cout << "Not a valid responce. Try again." << endl;
				cin >> keyword;
			}

			if (strcmp(keyword, "yes") == 0)
			{
				cin.ignore(MAX_CHAR, '\n');
				stop = true;
				write = true;
				go = true;
				cout << "Saving new song." << endl << endl;
			}

			else if (strcmp(keyword, "quit") == 0)
			{
				cin.ignore(MAX_CHAR, '\n');
				stop = true;
				go = true;
				cout << "Exiting new song." << endl << endl;
				break;
			}

			else if (strcmp(keyword, "retry") == 0)
			{
				cin.ignore(MAX_CHAR, '\n');
				go = true;
			}

			else
			{
				cin.ignore(MAX_CHAR, '\n');
				cout << keyword << " isn't a valid option. Try again." << endl << endl;
			}

		} while (go == false);

	} while (stop == false);


	if (write == true)
	{
		sidx.list[songcount].title = new char[strlen(title) + 1];
		strcpy(sidx.list[songcount].title, title);

		sidx.list[songcount].artist = new char[strlen(artist) + 1];
		strcpy(sidx.list[songcount].artist, artist);

		sidx.list[songcount].min = min;
		sidx.list[songcount].sec = sec;

		sidx.list[songcount].album = new char[strlen(album) + 1];
		strcpy(sidx.list[songcount].album, album);

		songcount++;
	}
}

*/

//Search by album name



void songidx::searchalbum(songidx sidx) {

	//same as search artist

	int idx = 0;
	int match = 0;
	char name[MAX_CHAR];
	node * curr;
	curr = head;

	cout << "Enter the name of the album." << endl << endl;
	cin.getline(name, MAX_CHAR, '\n');
	cout << endl;

	while (idx != songcount)
	{
		if (strcmp(name, curr->data.album) == 0)
		{
			cout << "Index #: " << curr->data.index << endl;
			cout << "Title: " << curr->data.title << endl;
			cout << "Artist: " << curr->data.artist << endl;
			cout << "Duration: " << curr->data.min << ":" << curr->data.sec << endl;
			cout << "Album: " << curr->data.album << endl << endl;
			idx++;
			match++;
			curr = curr->next;
		}

		else
		{
			idx++;
			curr = curr->next;
		}
	}
	cout << "Found " << match << " matches for " << name << "." << endl;
	cout << endl;

}





void songidx::searchartist(songidx sidx, int songcount) {

	//get input artist loop through index and string compare if match cout and incriment else increment.

	int idx = 0;
	int match = 0;
	char name[MAX_CHAR];
	node * curr;
	curr = head;

	cout << "Enter the name of the artist." << endl << endl;
	cin.getline(name, MAX_CHAR, '\n');
	cout << endl;

	while (idx != songcount)
	{
		if (strcmp(name, curr->data.artist) == 0)
		{
			cout << "Index #: " << curr->data.index << endl;
			cout << "Title: " << curr->data.title << endl;
			cout << "Artist: " << curr->data.artist << endl;
			cout << "Duration: " << curr->data.min << ":" << curr->data.sec << endl;
			cout << "Album: " << curr->data.album << endl << endl;
			idx++;
			match++;
			curr = curr->next;
		}

		else
		{
			idx++;
			curr = curr->next;
		}
	}
	cout << "Found " << match << " matches for " << name << "." << endl;
	cout << endl;

}

	
