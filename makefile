all:	Radio

Radio:	Time.o Song.o MusicPlayer.o driver.o 
	g++ Time.o Song.o MusicPlayer.o driver.o -o Radio.exe

Time.o Song.o MusicPlayer.o driver.o:	Time.cpp Song.cpp MusicPlayer.cpp driver.cpp
	g++ -c Time.cpp Song.cpp MusicPlayer.cpp driver.cpp

clean:	
	rm -f *.o Time.o Song.o driver.o MusicPlayer.o Radio.exe


