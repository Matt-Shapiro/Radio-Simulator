#include "MusicPlayer.h"
MusicPlayer::MusicPlayer(){
	initSet = false;
}

MusicPlayer::~MusicPlayer(){
	for (int i = 0; i < numSongs; i++){
		int hash = hashFunction(library[i].getSongTitle());
		node* np;
		for(np = hashTable[hash]; np != NULL; np = np -> next){
			if (np -> index == i && np != NULL)
				delete np;
		}
	}
	delete[] library;
	delete[] hashTable;
}

void MusicPlayer::run(char filename[]){
	string command;
	char space;
	fstream x(filename);
	while(!x.eof() && command != "QUIT"){
		x >> command;
		if (command == "QUIT"){
			cout << "entering quit function" << endl;
			break;
		}
		if (command == "INIT"){
				Time t;
				x >> t;
				x >> maxSongs;
				this -> init(t, maxSongs);
		}
		if (command == "ADD"){
			Song s;
			x >> s;
			this -> add(s);
		}	
		if (command == "REST"){
			Time t;
			x >> t;
			this -> rest(t);
		}
		if (command == "LIKE"){
			string title;
			int check = x.peek();
			if (isblank(check)>0){
				x >> title;
			}
			else {title = "";}
			like(title);
		}

		if (command == "DISLIKE"){
			string title;
			int check = x.peek();
			if (isblank(check) > 0)
				x>> title;
			else {title = "";}
			this -> dislike(title);
		}
		if (command == "PLAY"){
			int n;
			x >> n; 
			this -> play(n);
		}
		x.ignore(256,'\n');	
	}
	x.close();	
}

void MusicPlayer::init(Time t, int maxSongs){
	if (!initSet){
		cout << "Time set by INIT: " << t << endl << "Max Songs: " << maxSongs << endl;
		library = new Song[maxSongs]; 
		hashTable = new node*[maxSongs];
		for (int i = 0; i < maxSongs; i++){
			hashTable[i] = NULL;
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
		library[numSongs] = s;
		library[numSongs].setLastPlayedAt(time);
		maxHeapify(numSongs);
		
		int hash = hashFunction(library[numSongs].getSongTitle());	
		cout << "hash: " << hash << endl;
		node* n = new node;
		n -> index = numSongs;
		n -> next = hashTable[hash];
		hashTable[hash] = n;
		numSongs++;
	} else {
		cout << "INIT has not been set yet" << endl;
	}
}

void MusicPlayer::play(int n){	
	for (int i = 0; i < n; i++){
		Song songPlayed = library[0];
		cout << time << ' ' << songPlayed << endl;
		time = time + songPlayed.getRuntime();
		library[0].setLastPlayedAt(time);
		int newIndex = maxHeapify(0);
		recentlyPlayedIndex = newIndex;
	}
}
void MusicPlayer::like(string title){
	int hash = hashFunction(title);
	//cout << "hash: " << hash << endl;
	if (title.empty()){ 
		cout << "Like most recently played song: " << library[recentlyPlayedIndex].getSongTitle() << endl;
		library[recentlyPlayedIndex].setLikeability(library[recentlyPlayedIndex].getLikeability() + 1);
		//cout << "likeability: " << library[recentlyPlayedIndex].getLikeability() << endl;
	} else {
		//cout << "Hash: " << hash << endl;
		node* np;
		for (np = hashTable[hash]; np != NULL; np = np -> next){
			int ind = np -> index;
			string st = library[ind].getSongTitle();
			int blank;
			for (int j = 0; j < st.length()-1; j++){
				if (st[j] == ' ')
					blank = j;
			}
			st = st.substr(0, blank);
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
void MusicPlayer::dislike(string title){
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
int MusicPlayer::hashFunction(string title){
	int seed = 103; 
	int hash = 0;
	for(int i = 0; i < title.length(); i++){
		if (title[i] == ' ')
			break;
		else 
			hash = (hash * seed) + title[i];			
	}
	if (hash < 0)
		hash = hash * (-1);
	return hash % maxSongs;
}

