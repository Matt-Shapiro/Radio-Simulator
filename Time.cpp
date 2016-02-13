#include "Time.h"
Time::Time(){
	day = 1;
}

Time::Time(int hours, int minutes, int seconds, int day){
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
	this->day = day;
}

void Time::showTime(){
	cout << hours << ":" << minutes << ":" << seconds << endl;
}

void Time::start(){
	time_t timer;
	timer = time(NULL);
}

void Time::setHours(int h){
	hours = h;
}
void Time::setMinutes(int m){
	minutes = m;
}
void Time::setSeconds(int s){
	seconds = s;
}
void Time::setDay(int d){
	day = d;
}
int Time::getHours(){
	return hours;
}
int Time::getMinutes(){
	return minutes;
}
int Time::getSeconds(){
	return seconds;
}
int Time::getDay(){
	return day;
}
Time Time::operator+(Time t){
	int newHours = 0;
	int newMinutes = 0;
	int newSeconds = 0;
	int newDay = 0;
	newSeconds = t.seconds + seconds;
	if (newSeconds > 59){
		newSeconds = newSeconds - 60;
		newMinutes++;
	}
	newMinutes = newMinutes + t.minutes + minutes;
	if (newMinutes > 59){
		newMinutes = newMinutes - 60;
		newHours++;
	}
	newHours = newHours + t.hours + hours;
	if (newHours > 23){
		newHours = newHours - 24;
		newDay++;
	}
	newDay = newDay + t.day + day;
	Time newTime(newHours, newMinutes, newSeconds, newDay);
	return newTime;
}

Time Time::operator-(Time t){
	int newHours = 0;
	int newMinutes = 0;
	int newSeconds = 0;
	int newDay = 0;
	newSeconds = seconds - t.seconds;
	if (newSeconds < 0){
		newSeconds = 60 + newSeconds; 
		newMinutes--;
	}
	newMinutes = newMinutes + (minutes - t.minutes);
	if (newMinutes < 0){
		newMinutes = 60 + newMinutes;
		newHours--;
	}
	newHours = newHours + (hours - t.hours);
	if (newHours < 0){
		newHours = 24 + newHours;
		newDay--; 
	}
	newDay = newDay + (day - t.day); 
	Time newTime(newHours, newMinutes, newSeconds, newDay);
	return newTime;
}

ostream& operator<< (ostream& out, const Time& t){
	bool pm = false;
	int h;
	if (t.hours > 12){
		pm = true;
		h = t.hours - 12;
	} else if (t.hours == 12){
		pm = true;
		h = t.hours;
	} else if (t.hours == 0){
		h = 12;
	} else {
		h = t.hours;
	}
	
	out << "[Day " << t.day << ": " << h << ":" << t.minutes << ":" << t.seconds;
	if (pm){
		out << "pm]";
	} else {
		out << "am]";
	}
}

istream& operator>> (istream& in, Time& t){
	char colon;
	in >> t.hours;
	in >> colon;		//passes the colon
	in >> t.minutes;
	in >> colon;
	in >> t.seconds;
	//in >> colon;
}