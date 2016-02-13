#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Time.h"
#include "Song.h"

struct node{
	node* next;
	int index;
};

using namespace std;
class MusicPlayer{
	
	private:
		int maxSongs;
		int numSongs;
		Song* library;
		node** hashTable;
		Time time;
		int recentlyPlayedIndex;
		bool initSet;
		
	public:
		MusicPlayer();
		~MusicPlayer();
		void run(char filename[]);
		void init(Time t, int maxSongs);
		void add(Song s);
		void play(int n);
		void like(string title);
		void dislike(string title);
		int getMaxSongs();
		Time getTime();
		Song getSong(int index);
		int hashFunction(string title);
		void rest(Time t);
		int maxHeapify(int index);
		void swap(int a, int b);
		int getPriority(Song s);
		int getNumSongs();
};



