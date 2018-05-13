#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "IGame.h"

class BlackjackGame : public IGame{
public:
    BlackjackGame();
    ~BlackjackGame();
    int play(char* bet, int amount);
    inline int getID() const;
private:
    static const int GAME_ID = 123456;
    int _numberOfCards;
    int *_cards = nullptr;
    const int NUMBER_OF_CARDS_IN_DECK = 52;
    const int BLACKJACK = 21;
    void _getShuffledDeck(int *&cards, int &numberOfCards);
    void _shuffleDeck(int *&cards, int &numberOfCards);
    void _dealInitialCards(int *&dealerCards, int &numberOfDealerCards, int *&playerCards, int &numberOfPlayerCards);
    void _dealCard(int *&receiverCards, int &numberOfReceiverCards);
    void _push(int card, int *&cards, int &numberOfCards);
    int _pop(int *&cards, int &numberOfCards);
    int _calculateWin(int dealerScore, int numberOfDealerCards, int *playerCards, int numberOfPlayerCards, int bet) const;
    void _printTable(int *&dealerCards, int numberOfDealerCards, int *&playerCards, int &numberOfPlayerCards, bool printOnlyFirstDealerCard);
    void _printCards(int *&cards, int numberOfCards, const int MIDDLE_POSITION, const int MAX_CARD_STRING_LENGTH, bool printOnlyFirstCard = false);
    int _bestValue(int *&cards, int &numberOfCards) const;
    int _getRank(int card) const;
    void _getCard(int card, char *outCard, const int MAX_CARD_STRING_LENGTH);
};

inline int BlackjackGame::getID() const {
    return GAME_ID;
}

#endif