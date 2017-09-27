// Mathew Cunningham
// CECS 282-05
// Prog 1 - WAR
// 9/19/2017

#include "card.h"
#include "deck.h"
#include <iostream>
using namespace std;

int main()
{
	Deck myDeck;
	bool menuLoop = true;
	while (menuLoop)
	{
		cout << "1) Get a new card deck\n"
				"2) Show all remaining cards in the deck\n"
				"3) Shuffle\n"
				"4) Play WAR!\n"
				"5) Exit\n";
		int choice;
		cin >> choice;
		while (!cin)
		{
			cin.clear();
			cin.ignore();
			cout << "Error, Please enter a number 1-5\n";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
		{
			myDeck = Deck();
			cout << "You now have a new deck of cards\n";
			break;
		}
		case 2:
		{
			myDeck.showDeck();
			break;
		}
		case 3:
		{
			if (myDeck.canShuffle())
			{
				myDeck.shuffle();
				cout << "Shuffling Complete\n\n";
				break;
			}
			else
			{
				cout << "You may not shuffle a partial deck\n\n";
				break;
			}
		}
		case 4:
		{
			Card you;
			Card me;
			string playAgain;
			bool playLoop = true;

			cout << "Get ready to play WAR!!!\n";
			while (playLoop)
			{
				if (myDeck.cardsLeft() < 2)
				{
					cout << "Not enough cards in deck\n\n";
					break;
				}
				else
				{
					cout << "There are " << myDeck.cardsLeft() << " cards in the deck\n"
						"...dealing...\n";
					you = myDeck.deal();
					me = myDeck.deal();
					cout << "One for you...\n";
					you.showCard();
					cout << "One for me...\n";
					me.showCard();
					if (me.getValue() < you.getValue())
					{
						cout << "You Win!!!\n\n";
					}
					else if (me.getValue() > you.getValue())
					{
						cout << "I Win!!!\n\n";
					}
					else
					{
						cout << "It's a tie!!!\n\n";
					}
					cout << "Wanna play again? (y/n)\n";
					cin >> playAgain;
					if (playAgain == "n" || playAgain == "N")
					{
						break;
					}
				}
			}
			break;

		}
		case 5:
		{
			cout << "Goodbye";
			menuLoop = false;
			break;
		}
		default:  // handles unexpected integer value
		{
			cout << "You must enter a number (1-5)\n";
			break;
		}
		}
	}
	return 0;
}