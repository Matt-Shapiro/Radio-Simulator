#include "Song.h"
Song::Song(){
	likeability = 0;
}

Song::Song(string songTitle, string artist, Time runtime){
	this -> songTitle = songTitle;
	this -> artist = artist;
	this -> runtime = runtime;
	runtime.setDay(0);
	runtime.setHours(0);
	likeability = 0;
}

istream& operator>>(istream& in, Song &s){
	char space;
	int minutes, seconds;
	string songTitle;
	
	in.ignore();
	getline(in, s.songTitle, ',');
	in.ignore();
	
	getline(in, s.artist, ',');
	in.ignore();
	
	in >> minutes;
	in >> space;
	
	in >> seconds;
	Time rt(0, minutes, seconds, 0);
	s.runtime = rt;
}

ostream& operator<< (ostream& out, const Song& s){
	out << s.songTitle << " by " << s.artist;
}

Time Song::getRuntime(){
	return runtime;
}
void Song::setLastPlayedAt(Time t){
	lastPlayedAt = t;
}
Time Song::getLastPlayedAt(){
	return lastPlayedAt;
}
int Song::getLikeability(){
	return likeability;
}
string Song::getSongTitle(){
	return songTitle;
}
void Song::setLikeability(int l){
	this -> likeability = l;
}
string Song::getArtist(){
	return artist;
}