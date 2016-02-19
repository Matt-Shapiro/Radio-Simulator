#include "MusicPlayer.h"
MusicPlayer::MusicPlayer(){
	initSet = false; //init may only be set one time
}

MusicPlayer::~MusicPlayer(){
	for (int i = 0; i < numSongs; i++){
		int hash = hashFunction(library[i].getSongTitle());	//find index of song in hash table
		node* np;
		for(np = hashTable[hash]; np != NULL; np = np -> next){
			if (np -> index == i && np != NULL)
				delete np;				//deletes each element of the linked list at the hash location
		}
	}
	delete[] library;
	delete[] hashTable;
}

void MusicPlayer::run(char filename[]){
	string command;
	char space;
	fstream x(filename);
	while(!x.eof() && command != "QUIT"){			//while loop that accepts commands from a file until QUIT
		x >> command;
		if (command == "QUIT"){
			cout << "entering quit function" << endl;
			break;
		}
		if (command == "INIT"){				
				Time t;			
				x >> t;				//time cin operator is overloaded
				x >> maxSongs;
				this -> init(t, maxSongs);
		}
		if (command == "ADD"){
			Song s;
			x >> s;					//Song cin operator is overloaded
			this -> add(s);
		}	
		if (command == "REST"){
			Time t;
			x >> t;
			this -> rest(t);
		}
		if (command == "LIKE"){
			string title;
			int check = x.peek();			//peek() takes the next character without advancing the stream 
			if (isblank(check)>0){			//Differentiates between liking song titles or liking the last played
				x >> title;		
			}
			else {title = "";}			//If title is blank, the LIKE function likes the last played song
			like(title);
		}

		if (command == "DISLIKE"){
			string title;
			int check = x.peek();
			if (isblank(check) > 0)			//Differentiates between disliking song titles or disliking the last played
				x>> title;
			else {title = "";}
			this -> dislike(title);
		}
		if (command == "PLAY"){
			int n;
			x >> n; 
			this -> play(n);
		}
		x.ignore(256,'\n');		//ignores any extra spaces/characters that might be at the end of a command
	}
	x.close();	
}

void MusicPlayer::init(Time t, int maxSongs){
	if (!initSet){
		cout << "Time set by INIT: " << t << endl << "Max Songs: " << maxSongs << endl;
		library = new Song[maxSongs]; 
		hashTable = new node*[maxSongs];		//I'm using chaining for this hash table
		for (int i = 0; i < maxSongs; i++){
			hashTable[i] = NULL;			//initialize every character to NULL
		}
		this -> maxSongs = maxSongs;			
		recentlyPlayedIndex = 0;
		numSongs = 0;
		time = t;
		initSet = true;
	}else{
		cout << "INIT has already been set" << endl;
	}
}

void MusicPlayer::add(Song s){
	if (initSet){
		cout << "Add song: " << s << endl;		
		library[numSongs] = s;				//likeability will always be 0 for new songs, add to back of the heap
		library[numSongs].setLastPlayedAt(time);	//lastPlayed time for new songs will be when it was added
		maxHeapify(numSongs);				//if likeability of a song is less than 0, maxHeapify will move it behind new songs
		
		int hash = hashFunction(library[numSongs].getSongTitle());	//add to hashTable
		cout << "hash: " << hash << endl;
		node* n = new node;
		n -> index = numSongs;						//keep track of index to support O(1) runtime
		n -> next = hashTable[hash];					//add to the beginning of the hash index
		hashTable[hash] = n;
		numSongs++;
	} else {
		cout << "INIT has not been set yet" << endl;
	}
}

void MusicPlayer::play(int n){	
	for (int i = 0; i < n; i++){				
		Song songPlayed = library[0];					//Song with highest priority will be at heap index 0
		cout << time << ' ' << songPlayed << endl;
		time = time + songPlayed.getRuntime();				//advances the current time by the runtime of the song
		library[0].setLastPlayedAt(time);				//update the lastPlayedTime of the song to current time
		int newIndex = maxHeapify(0);					
		recentlyPlayedIndex = newIndex;					//keep track of this for LIKE recently played song
	}
}
void MusicPlayer::like(string title){
	int hash = hashFunction(title);
	if (title.empty()){ 		//user hasn't specified a title, like most recently played
		cout << "Like most recently played song: " << library[recentlyPlayedIndex].getSongTitle() << endl;
		library[recentlyPlayedIndex].setLikeability(library[recentlyPlayedIndex].getLikeability() + 1);
	} else {			//user specified a title
		node* np;
		for (np = hashTable[hash]; np != NULL; np = np -> next){	//search hashTable for title at hash value
			int ind = np -> index;					
			string st = library[ind].getSongTitle();
			int blank;
			for (int j = 0; j < st.length()-1; j++){
				if (st[j] == ' ')
					blank = j;				//find first blank character
			}
			st = st.substr(0, blank);				//hash function only checks up to the first blank character in a title
			if (title == st){
				if (library[ind].getLikeability() >= 0)	
					library[ind].setLikeability(library[ind].getLikeability()+1);
				if (library[ind].getLikeability() < 0)
					library[ind].setLikeability(0);
			cout << "Like Song: " << library[ind].getSongTitle() << endl;
			cout << "Likeability: " << library[ind].getLikeability() << endl;
			}
		}
	}
}
void MusicPlayer::dislike(string title){			//same implementation as like, but with decreasing likeability
	int hash = hashFunction(title);
	if (title.empty()){
		cout << "Dislike most recently played song: " << library[recentlyPlayedIndex].getSongTitle() << endl;
		library[recentlyPlayedIndex].setLikeability(library[recentlyPlayedIndex].getLikeability() - 1);
	} else {
		node* np;
		for (np = hashTable[hash]; np != NULL; np = np -> next){
			int ind = np -> index;
			string st = library[ind].getSongTitle();
			int blank;
			for (int j = 0; j < st.length(); j++){
				if (st[j] == ' ')
					blank = j;
			}
			st = st.substr(0, blank);
			if (title == st){
				if (library[ind].getLikeability() <= 0)
					library[ind].setLikeability(library[ind].getLikeability()-1);
				else if (library[ind].getLikeability() > 0)
					library[ind].setLikeability(0);
			cout << "Dislike Song: " << library[ind].getSongTitle() << endl;
			cout << "Likeability: " << library[ind].getLikeability() << endl;
			}
		}
	}
}
void MusicPlayer::rest(Time t){
	cout<<'['<<t.getHours()<<':'<<t.getMinutes()<<':'<<t.getSeconds()<<"] Rest" << endl;
	this -> time = time + t;
}

int MusicPlayer::getMaxSongs(){
	return maxSongs;
}

Time MusicPlayer::getTime(){
	return time;
}

Song MusicPlayer::getSong(int index){
	return library[index];
}

int MusicPlayer::maxHeapify(int index){
	int largest;
	int left = (2*index+1);
	int right = (2*index+2);
	if (left < numSongs && getPriority(library[left]) > getPriority(library[index])){
		largest = left;
	} else {
		largest = index;
	}
	if (right < numSongs && getPriority(library[right]) > getPriority(library[largest])){
		largest = right;
	}
	if (largest != index){
		swap(index, largest);
		return maxHeapify(largest);		
	}
}

void MusicPlayer::swap(int a, int b){
	int hashA = hashFunction(library[a].getSongTitle());
	int hashB = hashFunction(library[b].getSongTitle());
	node* np;
	for (np = hashTable[hashA]; np != NULL; np = np -> next){
		if (np -> index == a){
			//cout << "Old index song: " << library[np -> index].getSongTitle() << endl;
			np -> index = b;
			//cout << "New index song: " << library[np -> index].getSongTitle() << endl; 
		}
	}
	for (np = hashTable[hashB]; np != NULL; np = np -> next){
		if (np -> index == b){
			//cout << "Old index song: " << library[np -> index].getSongTitle() << endl;
			np -> index = a;
			//cout << "New index song: " << library[np -> index].getSongTitle() << endl; 
		}
	}
	Song temp = library[b];
	library[b] = library[a];
	library[a] = temp;
} 

int MusicPlayer::getPriority(Song s){
	int secondsSinceLP;
	Time sinceLP = time - s.getLastPlayedAt();
	secondsSinceLP = (sinceLP.getHours() * 60 * 60) + (sinceLP.getMinutes() * 60) + (sinceLP.getSeconds()) + (sinceLP.getDay() * 24 * 60 * 60);
	//cout << "Seconds since last played: " << secondsSinceLP << endl;
	return secondsSinceLP + (1000 * s.getLikeability());
}

int MusicPlayer::getNumSongs(){
	return numSongs;
}
int MusicPlayer::hashFunction(string title){		//hash key is the title string
	int seed = 103; 				//insignificant prime number, avoids more collisions
	int hash = 0;
	for(int i = 0; i < title.length(); i++){
		if (title[i] == ' ')			//only calculate hash up to the first space in title
			break;
		else 
			hash = (hash * seed) + title[i];		
	}
	if (hash < 0)
		hash = hash * (-1);
	return hash % maxSongs;				
}

