// Mathew Cunningham
// CECS 282-05
// Prog 2 - myDate
// 9/29/2017

#ifndef _MYDATE
#define _MYDATE
#include <iostream>
using namespace std;

class myDate
{
private:
	int month;
	int day;
	int year;

public:
	myDate();
	myDate(int, int, int);
	void display();
	void incrDate(int);
	void decrDate(int);
	int daysBetween(myDate);
	int getMonth();
	int getDay();
	int getYear();
	int dayOfYear();
	string dayOfWeek();
	static int greg2Julian(int, int, int);
	static void julian2Greg(int JD, int &m, int &d, int &y);
};
#endif

