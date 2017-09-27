#ifndef _DECK
#define _DECK

class Deck
{
	private:
		Card storage[52];
		int topCard;

	public:
		Deck();
		void showDeck();
		bool canShuffle();
		void shuffle();
		void refreshDeck();
		Card deal();
		int cardsLeft();
};
#endif
