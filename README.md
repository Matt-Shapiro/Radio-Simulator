# Radio-Simulator
Simulates the functions of an online radio in constant time

Data Structures:

Heap - Stores songs with priority value as a key
Priority is based off of the time since the last song was played and how much the user liked the song

Hash Table - Hash keys are based off of the song's title
Stores the heap index of songs in order to access songs in the heap in constant runtime
Updates indexes of the songs after they are played

Accepts the following functions and parameters
RUN <filename>            
- Runs a file with a command on each line

INIT <Time> <MaxSongs>
- Initializes the current time and sets the max number of songs (the length of the heap array)
- Can only be set once (returns a warning if user attempts to set it again)

ADD <Song>, <Artist> <Runtime>
