all:	Radio

Radio:	Time.o Song.o MusicPlayer.o driver.o 
	g++ Time.o Song.o MusicPlayer.o driver.o -o Program2.exe

Time.o Song.o MusicPlayer.o driver.o:	Time.cpp Song.cpp MusicPlayer.cpp driver.cpp
	g++ -c Time.cpp Song.cpp MusicPlayer.cpp driver.cpp

clean:	
	rm -f *.o Time.o Song.o driver.o MusicPlayer.o Program2.exe


