#include "card.h"
#include <iostream>
using namespace std;

string names[] = { "Ace", "Two","Three", "Four", "Five", "Six", "Seven",
				   "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

Card::Card()
{
	rank = "z";
	suit = "z";
}

Card::Card(string r, string s)
{
	rank = r;
	suit = s;
}

void Card::setCard(string r, string s)
{
	rank = r;
	suit = s;
}

int Card::getValue()
{
	string values[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	for (int i = 0; i < 13; i++)
	{
		if (rank == values[i])
		{
			return i + 1; // returns index number plus one to get card value
		}
	}
	return 0;
}

void Card::showCard()
{
	cout << "\t" << names[getValue() - 1] << " of " << suit << endl; // Prints card as string
	if (suit == "Spades")
	{
		cout << "---------" << endl;
		if (rank == "10")
		{
			cout << "|" << rank << "     |" << endl;
		}
		else
		{
			cout << "|" << rank << "      |" << endl;
		}
		cout << "|   *   |" << endl;
		cout << "|  * *  |" << endl;
		cout << "| ***** |" << endl;
		cout << "|*  *  *|" << endl;
		cout << "|   *   |" << endl;
		if (rank == "10")
		{
			cout << "|     " << rank << "|" << endl;
		}
		else
		{
			cout << "|      " << rank << "|" << endl;
		}
		cout << "---------\n" << endl;
	}

	else if (suit == "Clubs")
	{
		cout << "---------" << endl;
		if (rank == "10")
		{
			cout << "|" << rank << "     |" << endl;
		}
		else
		{
			cout << "|" << rank << "      |" << endl;
		}
		cout << "|   *   |" << endl;
		cout << "|*  *  *|" << endl;
		cout << "| * * * |" << endl;
		cout << "|   *   |" << endl;
		cout << "|   *   |" << endl;
		if (rank == "10")
		{
			cout << "|     " << rank << "|" << endl;
		}
		else
		{
			cout << "|      " << rank << "|" << endl;
		}
		cout << "---------\n" << endl;
	}

	else if (suit == "Hearts")
	{
		cout << "---------" << endl;
		if (rank == "10")
		{
			cout << "|" << rank << "     |" << endl;
		}
		else
		{
			cout << "|" << rank << "      |" << endl;
		}
		cout << "| ** ** |" << endl;
		cout << "|*  *  *|" << endl;
		cout << "| *   * |" << endl;
		cout << "|  * *  |" << endl;
		cout << "|   *   |" << endl;
		if (rank == "10")
		{
			cout << "|     " << rank << "|" << endl;
		}
		else
		{
			cout << "|      " << rank << "|" << endl;
		}
		cout << "---------\n" << endl;
	}

	else
	{
		cout << "---------" << endl;
		if (rank == "10")
		{
			cout << "|" << rank << "     |" << endl;
		}
		else
		{
			cout << "|" << rank << "      |" << endl;
		}
		cout << "|   *   |" << endl;
		cout << "|  * *  |" << endl;
		cout << "| *   * |" << endl;
		cout << "|  * *  |" << endl;
		cout << "|   *   |" << endl;
		if (rank == "10")
		{
			cout << "|     " << rank << "|" << endl;
		}
		else
		{
			cout << "|      " << rank << "|" << endl;
		}
		cout << "---------\n" << endl;
	}
	
}