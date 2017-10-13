#include "myDate.h"
#include <string>
#include <iomanip>
using namespace std;

const int SIZE = 10;

struct Student
{
	char name[SIZE];
	int id;
	char grade;
	myDate bday;
	string homeTown;
};

void populateStudents(Student s[], int elements);
void displayStudents(Student **sptr);
void sortName(Student *sptr[]);
void sortId(Student *sptr[]);
void sortGrade(Student *sptr[]);
void sortAge(Student *sptr[]);
void sortTown(Student *sptr[]);
int menu();

int main()
{
	Student cecs282[SIZE];
	populateStudents(cecs282, SIZE); // Fills array with students
	// Arrays of pointers, pointing to the original array
	Student *orig[SIZE]; 
	Student *name[SIZE];
	Student *id[SIZE];
	Student *grade[SIZE];
	Student *age[SIZE];
	Student *hometown[SIZE];

	// Sets pointers
	for (int i = 0; i < SIZE; i++)
	{
		orig[i] = name[i] = age[i] = grade[i] = hometown[i] = id[i] = &cecs282[i];
	}

	bool userActive = true;
	while (userActive)
	{
		switch (menu())
		{
		case 0:
			displayStudents(orig);
			break;

		case 1:
			sortName(name);
			displayStudents(name);
			break;

		case 2:
			sortId(id);
			displayStudents(id);
			break;

		case 3:
			sortGrade(grade);
			displayStudents(grade);
			break;

		case 4:
			sortAge(age);
			displayStudents(age);
			break;

		case 5:
			sortTown(hometown);
			displayStudents(hometown);
			break;

		case 6:
			userActive = false;
			break;

		default:
			cout << "\n\ninvalid input\n\n"; // Handles invalid integer input
		}
	}
	return 0;
}

int menu()
{
	cout << "Enter a number 0-6\n"
		<< "0) Display original list\n"
		<< "1) Display list sorted by Name\n"
		<< "2) Display list sorted by Student ID\n"
		<< "3) Display list sorted by Grade\n"
		<< "4) Display list sorted by Birthday\n"
		<< "5) Display list sorted by Home Town\n"
		<< "6) Exit" << endl;

	int choice;
	cin >> choice;
	while (!cin) // Handles invalid character input
	{
		cin.clear();
		cin.ignore();
		cout << "\n\nError, please enter a number 0-6\n\n";
		cin >> choice;
	}
	return choice;
}

void populateStudents(Student s[], int elements)
{
	char names[SIZE][SIZE] = { "Zak", "Jack", "Sally", "Andrew", "Erick", "Anthony", "Billy", "Amber", "Beth", "John" };
	string hmTown[SIZE] = { "Long Beach", "San Antonio", "Cypress", "San Diego", "Irvine", "Fullerton", "Jacksonville", "Nashville", "Salt Lake City", "Detroit" };
	int month;
	int day;
	int year;
	char grades[] = "ABCDF";
	int jdLow = myDate::greg2Julian(1, 1, 1995); // Low range for random bday
	int jdUpper = myDate::greg2Julian(12, 31, 2000); // High range for random bday

	for (int i = 0; i < elements; i++)
	{
		int randGrade = rand() % 5;
		int randBDay = rand() % (jdUpper - jdLow) + jdLow;
		myDate::julian2Greg(randBDay, month, day, year);
		strcpy_s(s[i].name, names[i]);
		s[i].id = rand() % (9999 - 1000 + 1) + 1000;
		s[i].grade = grades[randGrade];
		s[i].bday = myDate(month, day, year);
		s[i].homeTown = hmTown[i];
	}
}

void displayStudents(Student **sptr)
{
	cout << left << setw(15) << "Name" 
		 << left << setw(15) << "Student ID" 
		 << left << setw(15) << "Grade" 
		 << left << setw(25) << "Birthday" 
		 << left << setw(15) << "Home Town" << endl;

	for (int i = 0; i < SIZE; i++)
	{
		cout << left << setw(15) << (*sptr)->name;
		cout << left << setw(15) << (*sptr)->id;
		cout << left << setw(15) << (*sptr)->grade;
		cout << left << setw(25) << ((*sptr)->bday).printDate();
		cout << left << setw(15) << (*sptr)->homeTown << "\n";
		sptr++;
	}
	cout << "\n";
}

// Bubble sort for sorting by name
void sortName(Student *sptr[])
{
	for (int i = SIZE - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (strcmp(sptr[j]->name, sptr[j + 1]->name) > 0)
			{
				Student *temp = sptr[j];
				sptr[j] = sptr[j + 1];
				sptr[j + 1] = temp;
			}
		}
	}
}

// Sort by ID
void sortId(Student *sptr[])
{
	for (int i = SIZE - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (sptr[j]->id > sptr[j + 1]->id)
			{
				Student *temp = sptr[j];
				sptr[j] = sptr[j + 1];
				sptr[j + 1] = temp;
			}
		}
	}
}

// Sorty by grade
void sortGrade(Student *sptr[])
{
	for (int i = SIZE - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (sptr[j]->grade > sptr[j + 1]->grade)
			{
				Student *temp = sptr[j];
				sptr[j] = sptr[j + 1];
				sptr[j + 1] = temp;
			}
		}
	}
}

// Sort by birthday
void sortAge(Student *sptr[])
{
	for (int i = SIZE - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			int jdLo = myDate::greg2Julian(sptr[j]->bday.getMonth(), sptr[j]->bday.getDay(), sptr[j]->bday.getYear());
			int jdHi = myDate::greg2Julian(sptr[j + 1]->bday.getMonth(), sptr[j + 1]->bday.getDay(), sptr[j + 1]->bday.getYear());
			if (jdLo > jdHi)
			{
				Student *temp = sptr[j];
				sptr[j] = sptr[j + 1];
				sptr[j + 1] = temp;
			}
		}
	}
}

// Sorty by home town
void sortTown(Student *sptr[])
{
	for (int i = SIZE - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (sptr[j]->homeTown.compare(sptr[j + 1]->homeTown) > 0)
			{
				Student *temp = sptr[j];
				sptr[j] = sptr[j + 1];
				sptr[j + 1] = temp;
			}
		}
	}
}

