#ifndef _CARD
#define _CARD
#include <string>
using namespace std;

class Card
{
	private:
		string rank;
		string suit;

	public:
		Card();
		Card(string, string);
		void setCard(string, string);
		int getValue();
		void showCard();
};
#endif