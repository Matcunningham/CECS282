#ifndef _MY_DATE
#define _MY_DATE
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
};
#endif

