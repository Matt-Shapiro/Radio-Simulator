using namespace std;
#include "Song.h"
#include "Time.h"
#include "MusicPlayer.h"
#include <sstream>
#include <cstring>
int main(){
	MusicPlayer m;
	string input;
	string command;
	string arg1,arg2,arg3;
	while(command != "QUIT"){
		cout << "Command [RUN<filename>][INIT<Time><MaxSongs>][ADD<SongTitle><Artist><Runtime>][PLAY<N>][REST<Time>][LIKE{<SongTitle>}]";
		cout << "[DISLIKE{<SongTitle>}]: " << endl;
		string arg1,arg2,arg3;
		getline(cin, input);
		istringstream iss(input);
		Song so;
		int arg = 0;
		while(iss){
			if (arg == 0){
				iss >> command;
			} else if (arg == 1){
				if (command != "ADD"){
					iss >> arg1;
				}
				else {
					iss >> so;
				}
			} else if (arg == 2){
				if (command != "ADD" && command != "LIKE" && command != "DISLIKE"){
					iss >> arg2;
				}
			} else if (arg == 3){
				if (command != "ADD")
				iss >> arg3;
			} else if (arg == 4){
				break;
			}
			arg++;
		}
		if (command == "RUN"){
			char *filename = new char[arg1.length()-1];
			std::strcpy(filename, arg1.c_str());
			cout << filename;
			m.run(filename);
		} 
		else if (command == "INIT"){
			istringstream a(arg1);
			Time t;
			a >> t;
			int ms = atoi(arg2.c_str());	
			m.init(t, ms);
		}
		else if (command == "ADD"){
			m.add(so);
		} 
		else if (command == "PLAY"){
			int n = atoi(arg1.c_str());	
			m.play(n);
		}
		else if (command == "REST"){
			istringstream a(arg1);
			Time t;
			a >> t;
			m.rest(t);
		}
		else if (command == "LIKE"){
			string title = arg1;
			m.like(title);
		}
		else if (command == "DISLIKE"){
			m.dislike(arg1);
		}
	}
	
//	m.run("test");
	cout << endl;
	
	cout << "----------------------------------------------------------------" << endl << endl;
	cout << "Testing Time class operators" << endl;
	//Testing Time + Time operator
	Time t1(9,20,23,1);
	Time t2(2,11,15,2);
	Time t3 = t1 + t2;
	cout << t3 << endl;
	
	Time t4(23,40,40,1);
	Time t5(0,40,40,0);
	Time t6 = t4 + t5;
	cout << t6 << endl;
	
	//Testing Time - Time operator
	Time t7(9,40,30,1);
	Time t8(2,10,20,0);
	Time t9 = t7 - t8;
	cout << t9 << endl;
	
	Time t10(0,10,20,1);
	Time t11(1,0,0,0);
	Time t12 = t10 - t11;
	cout << t12 << endl;
		
		
	cout << "---------------------------------------------------------------" << endl << endl;
		
}
