# Radio-Simulator
Simulates the functions of an online radio in O(1) runtime

Data Structures:

Heap 
- Stores songs with priority value as a key
- Priority is based off of the time since the last song was played and how much the user liked the song

Hash Table 
- Hash keys are based off of the song's title
- Stores the heap index of songs in order to access songs in the heap in constant runtime
- Updates indexes of the songs after they are played

MusicPlayer.cpp contains the implementation of every action
Song.cpp and Time.cpp contain mostly just overloading operators, making it easier to read commands using cin

Accepts the following actions and parameters in the following format:
RUN [filename]            
- Runs a file with filename
- A new command should appear on each line

INIT [Time] [MaxSongs]
- Initializes the current time and sets the max number of songs (the length of the heap array)
- Can only be set once (returns a warning if user attempts to set it again)
- Time takes the format of hours:minutes:seconds

ADD [Song Title], [Artist], [Runtime]
- Adds a song to the back of the heap
- Note the commas between the parameters
- Runtime follow the format minutes:seconds

PLAY [N]
- Plays the next N songs from the hash table
- Prints out songs in the following format: [Day n: hours:minutes:seconds] SongTitle by Artist

REST [Time]
- Advances current time by Time

LIKE [Song Title]
- Likes the song specified by Song Title
- Like is a factor in the song's priority

LIKE
- Likes the most recent song played

DISLIKE[Song TItle]
- Dislikes the song specified by Song Title

DISLIKE
- Dislikes the most recently played song

QUIT
- Ends the program
