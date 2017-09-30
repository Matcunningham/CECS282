// Mathew Cunningham
// CECS 282-05
// Prog 2 - myDate
// 9/29/2017

#include "mydate.h"
#include <iostream>
#include <string>
using namespace std;

string monthStr[] = { "January", "Febuary", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December" };

int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

myDate::myDate() //Default Constructor
{
	month = 5;
	day = 11;
	year = 1959;
}

myDate::myDate(int m, int d, int y) //Overloaded Constructor
{
	// Invalid date handling
	if (m > 12 || m < 1 || d < 1 || d > daysInMonth[m - 1] || y < -4713)
	{
		if (((y % 4 == 0 && !(y % 100 == 0)) || (y % 400 == 0)) && d == 29)
		{
			month = m;
			day = d;
			year = y;
		}
		else
		{
			month = 5;
			day = 11;
			year = 1959;
		}
	}
	else
	{
		month = m;
		day = d;
		year = y;
	}
}

void myDate::display()
{
	cout << monthStr[getMonth() - 1] << " " << getDay() << ", " << getYear();
}

void myDate::incrDate(int x)
{
	int jd = greg2Julian(month, day, year);
	jd += x;
	julian2Greg(jd, month, day, year);
}

void myDate::decrDate(int x)
{
	incrDate(-x);
}

int myDate::daysBetween(myDate d)
{
	int currentDate = greg2Julian(month, day, year);
	int givenDate = greg2Julian(d.getMonth(), d.getDay(), d.getYear());
	return givenDate - currentDate;
}

int myDate::getMonth()
{
	return month;
}

int myDate::getDay()
{
	return day;
}

int myDate::getYear()
{
	return year;
}

int myDate::dayOfYear()
{
	int dayCount = 0;
	int i = 0;
	// check if leap year and not January to add the extra day
	if (((year % 4 == 0 && !(year % 100 == 0)) || (year % 400 == 0)) && month >= 2)
	{
		if ((month == 2 && day > 29) || (month > 2))
		{
			dayCount++;
		}
	}
	while (i < month - 1)
	{
		dayCount = dayCount + daysInMonth[i];
		i++;
	}
	dayCount = dayCount + day;
	return dayCount;

}


string myDate::dayOfWeek()
{
	string weekDays[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	int jd = greg2Julian(month, day, year);
	return weekDays[jd % 7];
}

int myDate::greg2Julian(int month, int day, int year)
{
	int i = year;
	int j = month;
	int k = day;
	return k - 32075 + 1461 * (i + 4800 + (j - 14) / 12) / 4 + 367 * (j - 2 - (j - 14)
		/ 12 * 12) / 12 - 3 * ((i + 4900 + (j - 14) / 12) / 100) / 4;


}

void myDate::julian2Greg(int JD, int &m, int &d, int &y)
{
	int l = JD + 68569;
	int n = 4 * l / 146097;
	l = l - (146097 * n + 3) / 4;
	int i = 4000 * (l + 1) / 1461001;
	l = l - 1461 * i / 4 + 31;
	int j = 80 * l / 2447;
	int k = l - 2447 * j / 80;
	l = j / 11;
	j = j + 2 - 12 * l;
	i = 100 * (n - 49) + i + l;

	y = i;
	m = j;
	d = k;
}