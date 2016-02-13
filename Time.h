using namespace std;
#ifndef _Time_H_
#define _Time_H_

class Time;

#include <ctime>
#include <iostream>
#include <stdlib.h>

class Time{
	private:
		int hours;
		int minutes;
		int seconds;
		int day;

	public:
		Time();
		Time(int hours, int minutes, int seconds, int day);
		void showTime();
		void start();
		void setHours(int h);
		void setMinutes(int m);
		void setSeconds(int s);
		void setDay(int d);
		int getHours();
		int getMinutes();
		int getSeconds();
		int getDay();
		Time operator+(Time t);
		Time operator-(Time t);
		friend ostream& operator<<(ostream &out, const Time &t);
		friend istream& operator>>(istream &in, Time &t);
};
#endif