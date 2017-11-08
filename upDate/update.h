// Mathew Cunningham
// CECS 282-05
// Prog 4 - Overloading Operators
// 11/07/2017

#ifndef _UPDATE
#define _UPDATE
#include <iostream>
#include <string>
using namespace std;

class upDate
{
private:
	int *dptr;
	static int count;

public:
	// Constructors and Descructor
	upDate();
	upDate(int, int, int);
	upDate(const upDate&);
	~upDate();

	// Operator Overloading
	friend upDate operator+(int, upDate);
	friend ostream& operator<<(ostream&, const upDate&);
	void operator=(const upDate&);
	upDate operator+(int);
	upDate operator-(int);
	int operator-(upDate);
	upDate operator++(int);
	upDate operator++();
	upDate operator--(int);
	upDate operator--();
	bool operator==(upDate);
	bool operator<(upDate);
	bool operator>(upDate);

	// Other Functions
	void setDate(int, int, int);
	void incrDate(int);
	void decrDate(int);
	int julian();
	int daysBetween(upDate);
	int getMonth();
	int getDay();
	int getYear();
	int dayOfYear();
	string dayOfWeek();
	string getMonthName();

	// Static Methods
	static int GetDateCount();
	static int greg2Julian(int, int, int);
	static void julian2Greg(int JD, int &m, int &d, int &y);

};
#endif