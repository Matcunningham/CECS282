// Mathew Cunningham
// CECS 282-05
// Prog 4 - Overloading Operators
// 11/07/2017

#include "update.h"
#include <iostream>
using namespace std;

int upDate::count = 0;
const int MONTH = 0;
const int DAY = 1;
const int YEAR = 2;

string monthStr[] = { "January", "February", "March", "April", "May", "June", "July",
"August", "September", "October", "November", "December" };

int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

upDate::upDate() //Default Constructor
{
	count++;
	dptr = new int[3];
	dptr[MONTH] = 5;
	dptr[DAY] = 11;
	dptr[YEAR] = 1959;
}

upDate::upDate(int m, int d, int y) //Overloaded Constructor
{
	count++;
	dptr = new int[3];
	dptr[MONTH] = 5;
	dptr[DAY] = 11;
	dptr[YEAR] = 1959;
	if (m > 12 || m < 1 || d < 1 || d > daysInMonth[m - 1] || y < -4713)
	{
		// Allows leap days
		if (((y % 4 == 0 && !(y % 100 == 0)) || (y % 400 == 0)) && d == 29)
		{
			dptr[MONTH] = m;
			dptr[DAY] = d;
			dptr[YEAR] = y;
		}
	}
	else
	{
		dptr[MONTH] = m;
		dptr[DAY] = d;
		dptr[YEAR] = y;
	}
}

upDate::upDate(const upDate& D) // Copy Constructor
{
	count++;
	dptr = new int[3];
	dptr[MONTH] = D.dptr[MONTH];
	dptr[DAY] = D.dptr[DAY];
	dptr[YEAR] = D.dptr[YEAR];
}

upDate::~upDate() // Destructor
{
	count--;
	delete[] dptr;
}

upDate operator+(int n, upDate D)
{
	upDate temp(D);
	temp.incrDate(n);
	return temp;
}

ostream& operator<<(ostream& out, const upDate& D)
{
	out << D.dptr[MONTH] << "/" << D.dptr[DAY] << "/" << D.dptr[YEAR];
	return out;
}

void upDate::operator=(const upDate& D)
{
	dptr[MONTH] = D.dptr[MONTH];
	dptr[DAY] = D.dptr[DAY];
	dptr[YEAR] = D.dptr[YEAR];
}

upDate upDate::operator+(int n)
{
	upDate temp(*this);
	temp.incrDate(n);
	return temp;
}

upDate upDate::operator-(int n)
{
	upDate temp(*this);
	temp.decrDate(n);
	return temp;
}

int upDate::operator-(upDate D)
{
	return (*this).julian() - D.julian();
}

upDate upDate::operator++(int arb)
{
	++(*this);
	return *this;
}

upDate upDate::operator++()
{
	*this = *this + 1;
	return *this;
}

upDate upDate::operator--(int arb)
{
	*this = *this - 1;
	return *this;
}

upDate upDate::operator--()
{
	(*this)--;
	return *this;
}

bool upDate::operator==(upDate D)
{
	if ((*this).julian() == D.julian())
	{
		return true;
	}
	return false;
}

bool upDate::operator<(upDate D)
{
	if ((*this).julian() < D.julian())
	{
		return true;
	}
	return false;
}

bool upDate::operator>(upDate D)
{
	if ((*this).julian() > D.julian())
	{
		return true;
	}
	return false;
}

void upDate::setDate(int m, int d, int y)
{
	dptr[MONTH] = m;
	dptr[DAY] = d;
	dptr[YEAR] = y;
}

void upDate::incrDate(int x)
{
	int jd = greg2Julian(dptr[MONTH], dptr[DAY], dptr[YEAR]);
	jd += x;
	julian2Greg(jd, dptr[MONTH], dptr[DAY], dptr[YEAR]);
}

void upDate::decrDate(int x)
{
	incrDate(-x);
}

int upDate::julian()
{
	return greg2Julian(dptr[MONTH], dptr[DAY], dptr[YEAR]);
}

int upDate::daysBetween(upDate d)
{
	int currentDate = greg2Julian(dptr[MONTH], dptr[DAY], dptr[YEAR]);
	int givenDate = greg2Julian(d.getMonth(), d.getDay(), d.getYear());
	return givenDate - currentDate;
}

int upDate::getMonth()
{
	return dptr[MONTH];
}

int upDate::getDay()
{
	return dptr[DAY];
}

int upDate::getYear()
{
	return dptr[YEAR];
}

int upDate::dayOfYear()
{
	int dayCount = 0;
	int i = 0;

	// check if leap year and not January to add the extra day
	if (((dptr[YEAR] % 4 == 0 && !(dptr[YEAR] % 100 == 0)) || (dptr[YEAR] % 400 == 0)) && dptr[MONTH] >= 2)
	{
		if ((dptr[MONTH] == 2 && dptr[DAY] > 29) || (dptr[MONTH] > 2))
		{
			dayCount++;
		}
	}
	while (i < dptr[MONTH] - 1)
	{
		dayCount = dayCount + daysInMonth[i];
		i++;
	}
	dayCount = dayCount + dptr[DAY];
	return dayCount;

}


string upDate::dayOfWeek()
{
	string weekDays[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	int jd = greg2Julian(dptr[0], dptr[1], dptr[2]);
	return weekDays[jd % 7];
}

string upDate::getMonthName()
{
	return monthStr[dptr[MONTH] - 1];
}

int upDate::getDateCount()
{
	return count;
}

int upDate::greg2Julian(int month, int day, int year)
{
	int i = year;
	int j = month;
	int k = day;
	return k - 32075 + 1461 * (i + 4800 + (j - 14) / 12) / 4 + 367 * (j - 2 - (j - 14)
		/ 12 * 12) / 12 - 3 * ((i + 4900 + (j - 14) / 12) / 100) / 4;
}

void upDate::julian2Greg(int JD, int &m, int &d, int &y)
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