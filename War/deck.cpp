#include "card.h"
#include "deck.h"
using namespace std;

string suits[] = { "Spades", "Clubs", "Hearts", "Diamonds" };
string values[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

Deck::Deck()
{
	refreshDeck();
}

void Deck::showDeck() // Shows all cards in deck
{
	for (int i = topCard; i < 52; i++)
	{
		storage[i].showCard();
	}
}

bool Deck::canShuffle()
{
	if (topCard > 0)
	{
		return false;
	}
	return true;
}

void Deck::shuffle()
{
	int x; 
	int y;
	Card temp;
	for (int i = 0; i < 10000; i++)
	{
		x = rand() % 52;
		y = rand() % 52;
		temp = storage[x];
		storage[x] = storage[y];
		storage[y] = temp;

	}
}

void Deck::refreshDeck()
{
	topCard = 0;
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			storage[count].setCard(values[j], suits[i]);
			count++;
		}

	}
}

Card Deck::deal()
{
	topCard++;
	return storage[topCard - 1];

}

int Deck::cardsLeft()
{
	return 52 - topCard;
}