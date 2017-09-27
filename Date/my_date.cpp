#include "my_date.h"
#include <iostream>
#include <string>
using namespace std;

string monthStr[] = { "January", "Febuary", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December" };

myDate::myDate()
{
	month = 5;
	day = 11;
	year = 1959;
}

myDate::myDate(int m, int d, int y)
{
	//TODO invalid date handling
	month = m;
	day = d;
	year = y;
}

void myDate::display()
{
	cout << monthStr[getMonth() + 1] << " " << getDay() << ", " << getYear();
}

void mydate::incrdate(int x)
{
	//todo gets?
	int jd = greg2julian(month, day, year);
	jd += x;
	julian2greg(jd, month, day, year);
}

void myDate::decrDate(int x)
{
	incrDate(-x);
}

int myDate::daysBetween(myDate d)
{

}