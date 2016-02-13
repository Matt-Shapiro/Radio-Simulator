#ifndef _Song_H_
#define _Song_H_

class Song;

#include <string>
#include "Time.h"
using namespace std;
class Song{

	private:
		Time runtime;
		Time lastPlayedAt;
		string songTitle;
		string artist;
		int likeability;
		
	public:
		Song();
		Song(string songTitle, string artist, Time runtime);
		friend istream& operator>>(istream &in, Song &s);
		friend ostream& operator<< (ostream& out, const Song& s);
		Time getRuntime();
		int getLikeability();
		void setLikeability(int l);
		void setLastPlayedAt(Time t);
		Time getLastPlayedAt();
		string getSongTitle();
		string getArtist();
		
};
#endif