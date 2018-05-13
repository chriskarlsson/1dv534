/**********************************************************************/
// File:	BlackjackGame.cpp
// Summary: A Blackjack game
// Version:	0.0
// Owner:	Christoffer Karlsson
// -------------------------------------------
// Log:     2018-04-06 File created by Christoffer
/**********************************************************************/

// Preprocessor directives
#include <iostream> //cin, cout, endl
#include <iomanip> // setw
#include <ctime> // time
#include "UserInput.h"
#include "BlackjackGame.h"

// OS specific adjustments
#ifdef _WIN32
// Windows
#define CLEARSCREEN system("cls")
#elif __APPLE__
// Mac OS
#define CLEARSCREEN system("clear")
#elif __linux__
// Linux#define CLEARSCREEN system("clear")
#else
error "Unknown compiler"
#endif

// Usings
using std::bad_alloc;
using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::time;

//-----------------------------------------------------------------
// CrapGameWrapper()
//
// Summary: Constructor
// Returns: -
//-----------------------------------------------------------------
BlackjackGame::BlackjackGame()
{
    // Setup the deck that is to be used
    auto numberOfDecks = getIntegerFromUser("How many decks are to be used?");
    _numberOfCards = numberOfDecks * NUMBER_OF_CARDS_IN_DECK;
    _getShuffledDeck(_cards, _numberOfCards);
}

//-----------------------------------------------------------------
// ~CrapGameWrapper()
//
// Summary: Destructor
// Returns: -
//-----------------------------------------------------------------
BlackjackGame::~BlackjackGame()
{
    // Cleanup
    delete[] _cards;
}

//-----------------------------------------------------------------
// int play(char* bet, int amount)
//
// Summary: Place amount money on position bet and return winnings
// Returns: The amount that was won.
//-----------------------------------------------------------------
int BlackjackGame::play(char* bet, int amount)
{
    int *dealerCards = nullptr;
    int *playerCards = nullptr;
    int numberOfDealerCards = 0;
    int numberOfPlayerCards = 0;

    _dealInitialCards(dealerCards, numberOfDealerCards, playerCards, numberOfPlayerCards);

    _printTable(dealerCards, numberOfDealerCards, playerCards, numberOfPlayerCards, true);

    while (_bestValue(playerCards, numberOfPlayerCards) < BLACKJACK && userYesOrNo("Hit?"))
    {
        _dealCard(playerCards, numberOfPlayerCards);
        _printTable(dealerCards, numberOfDealerCards, playerCards, numberOfPlayerCards, true);
    }

    // Deal cards to dealer until at least 17
    int dealerScore = _bestValue(dealerCards, numberOfDealerCards);
    const int DEALER_STOP_SCORE = 17;
    while (dealerScore < DEALER_STOP_SCORE)
    {
        _dealCard(dealerCards, numberOfDealerCards);
        dealerScore = _bestValue(dealerCards, numberOfDealerCards);
    }

    _printTable(dealerCards, numberOfDealerCards, playerCards, numberOfPlayerCards, false);

    auto win = _calculateWin(dealerScore, numberOfDealerCards, playerCards, numberOfPlayerCards, amount);

    // Cleanup
    delete[] dealerCards;
    delete[] playerCards;

    return win;
}

//-----------------------------------------------------------------
// void _getShuffledDeck(int *&cards, int &numberOfCards)
//
// Summary: Populates the deck and allows the user to shuffle it
// Returns: -
//-----------------------------------------------------------------
void BlackjackGame::_getShuffledDeck(int *&cards, int &numberOfCards)
{
    try
    {
        cards = new int[numberOfCards];
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Assign values to each card
    for (int i = 0; i < numberOfCards; i++) {
        cards[i] = i + 1;
    }

    // Allow the user to choose how many times the deck should be shuffled
    do
    {
        cout << "Shuffling ..." << endl;
        _shuffleDeck(cards, numberOfCards);
    } while (userYesOrNo("Shuffle one more time?"));
}

//-----------------------------------------------------------------
// void _shuffleDeck(int *&cards, int &numberOfCards)
//
// Summary: Emulates shuffling of the deck
// Returns: -
//-----------------------------------------------------------------
void BlackjackGame::_shuffleDeck(int *&cards, int &numberOfCards)
{
    // Seed random number generator
    srand(time(NULL));

    // Split deck somewhere in the two middle quartiles
    int firstPartSize = numberOfCards / 4 + rand() % (numberOfCards / 2);
    int secondPartSize = numberOfCards - firstPartSize;

    // Create two arrays to hold the cards while shuffling
    int *firstDeckPart;
    int *secondDeckPart;
    try
    {
        firstDeckPart = new int[firstPartSize];
        secondDeckPart = new int[secondPartSize];
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Put first half of deck in first array
    int i;
    for (i = 0; i < firstPartSize; i++)
    {
        firstDeckPart[i] = cards[i];
    }

    // Put second half of deck in second array
    for (int j = 0; j < secondPartSize; i++, j++)
    {
        secondDeckPart[j] = cards[i];
    }

    // Shuffle
    for (int deckIndex = 0, partOneIndex = 0, partTwoIndex = 0; deckIndex < numberOfCards; deckIndex++)
    {
        // Get a random 0 or 1
        bool random = rand() % 2 - 1;

        // If random is 1, use card from 1 array if possible
        if ((random && partOneIndex < firstPartSize) || partTwoIndex >= secondPartSize)
        {
            cards[deckIndex] = firstDeckPart[partOneIndex++];
        }
        else
        {
            cards[deckIndex] = secondDeckPart[partTwoIndex++];
        }
    }

    // Cleanup
    delete[] firstDeckPart;
    delete[] secondDeckPart;
}

//-----------------------------------------------------------------
// void _dealInitialCards(int *&dealerCards, int &numberOfDealerCards, int *&playerCards, int &numberOfPlayerCards)
//
// Summary: Deal players and dealer 2 cards each
// Returns: -
//-----------------------------------------------------------------
void BlackjackGame::_dealInitialCards(int *&dealerCards, int &numberOfDealerCards, int *&playerCards, int &numberOfPlayerCards)
{
    const int NUMBER_OF_CARDS = 2;
    for (int i = 0; i < NUMBER_OF_CARDS; i++)
    {
        // Deal one card to the player
        _dealCard(playerCards, numberOfPlayerCards);

        // Deal one card to the dealer
        _dealCard(dealerCards, numberOfDealerCards);
    }
}

//-----------------------------------------------------------------
// void _dealCard(int *&receiverCards, int &numberOfReceiverCards)
//
// Summary: Takes a card from the top of the deck and gives it to the receiver
// Returns: -
//-----------------------------------------------------------------
void BlackjackGame::_dealCard(int *&receiverCards, int &numberOfReceiverCards)
{
    // Make sure that there are cards in the deck
    if (_numberOfCards <= 0)
    {
        cout << "Dealer is out of cards. Adding new deck ..." << endl;
        delete[] _cards;
        _numberOfCards = NUMBER_OF_CARDS_IN_DECK;
        _getShuffledDeck(_cards, _numberOfCards);
    }

    // Take card from top of deck
    int card = _pop(_cards, _numberOfCards);

    // Give it to the receiver
    _push(card, receiverCards, numberOfReceiverCards);
}

//-----------------------------------------------------------------
// void _push(int card, int *&cards, int &numberOfCards)
//
// Summary: Place the card at the beginning of the array
// Returns: -
//-----------------------------------------------------------------
void BlackjackGame::_push(int card, int *&cards, int &numberOfCards)
{
    // Create temp variables
    int *newArray;
    const int NEW_SIZE = numberOfCards + 1;

    try
    {
        // Allocate memory
        newArray = new int[NEW_SIZE];
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Place the card first
    newArray[0] = card;

    // Copy all values from the old array to the new array
    for (int i = 0; i < numberOfCards; i++)
    {
        newArray[i + 1] = cards[i];
    }

    // Cleanup old array
    if (cards != nullptr)
    {
        delete[] cards;
    }

    // Point old to the temp values
    cards = newArray;
    numberOfCards = NEW_SIZE;
}

//-----------------------------------------------------------------
// int _pop(int *&cards, int &numberOfCards)
//
// Summary: Removes the first card from the array
// Returns: The card as an integer
//-----------------------------------------------------------------
int BlackjackGame::_pop(int *&cards, int &numberOfCards)
{
    // Create temp variables
    int *newArray;
    const int NEW_SIZE = numberOfCards - 1;

    if (NEW_SIZE > 0)
    {
        try
        {
            // Allocate memory
            newArray = new int[NEW_SIZE];
        }
        catch (bad_alloc)
        {
            // Explain the issue and the terminate with error code 1
            cout << "Failed to allocate memory. Exiting ..." << endl;
            exit(1);
        }

        // Copy all values from the old array to the new array
        for (int i = 0; i < NEW_SIZE; i++)
        {
            newArray[i] = cards[i + 1];
        }
    }
    else
    {
        newArray = nullptr;
    }

    // Take the first card
    const int POPPED = cards[0];

    // Cleanup
    delete[] cards;

    // Point old to the temp values
    cards = newArray;
    numberOfCards = NEW_SIZE;

    return POPPED;
}

//-----------------------------------------------------------------
// int _calculateWin(int dealerScore, int numberOfDealerCards, int *playerCards, int numberOfPlayerCards, int bet) const
//
// Summary: Calculates if and how much the player win
// Returns: Win as integer
//-----------------------------------------------------------------
int BlackjackGame::_calculateWin(int dealerScore, int numberOfDealerCards, int *playerCards, int numberOfPlayerCards, int bet) const
{
    int const DRAW_LIMIT = 20;
    int const PLAYER_SCORE = _bestValue(playerCards, numberOfPlayerCards);

    // Calculate win
    if (PLAYER_SCORE <= BLACKJACK)
    {
        if (dealerScore < PLAYER_SCORE || dealerScore > BLACKJACK)
        {
            if (PLAYER_SCORE == BLACKJACK && numberOfPlayerCards == 2)
            {
                return bet * 1.5; // Blackjack
            }
            else
            {
                return bet * 2; // Player beat dealer
            }
        }
        else if (dealerScore == PLAYER_SCORE)
        {
            if (dealerScore < DRAW_LIMIT)
            {
                return 0; // Dealer wins draw lower than 20
            }
            else if (dealerScore == BLACKJACK && numberOfDealerCards > 2 && numberOfPlayerCards == 2)
            {
                return 1.5 * bet; // Player blackjack beats dealer 21
            }
            else
            {
                return bet; // Draw yields the money back
            }
        }
        else
        {
            return 0; // Dealer beats player
        }
    }
    else
    {
        return 0; // Player goes over 21
    }
}

//-----------------------------------------------------------------
// void _printTable(int *&dealerCards, int numberOfDealerCards, int *&playerCards, int &numberOfPlayerCards, bool printOnlyFirstDealerCard)
//
// Summary: Prints the whole table
// Returns: -
//-----------------------------------------------------------------
void BlackjackGame::_printTable(int *&dealerCards, int numberOfDealerCards, int *&playerCards, int &numberOfPlayerCards, bool printOnlyFirstDealerCard)
{
    // Clear the screen
    CLEARSCREEN;

    const int COLUMN_WIDTH = 9;
    const int MIDDLE = COLUMN_WIDTH / 2;
    const int MAX_CARD_STRING_LENGTH = 4;

    // Print dealer cards in the middle
    _printCards(dealerCards, numberOfDealerCards, MIDDLE, MAX_CARD_STRING_LENGTH, printOnlyFirstDealerCard);

    // Print the player cards
    _printCards(playerCards, numberOfPlayerCards, MIDDLE, MAX_CARD_STRING_LENGTH);
}

//-----------------------------------------------------------------
// void _printCards(int *&cards, int numberOfCards, const int MIDDLE_POSITION, const int MAX_CARD_STRING_LENGTH, bool printOnlyFirstDealerCard)
//
// Summary: Prints the dealer cards
// Returns: -
//-----------------------------------------------------------------
void BlackjackGame::_printCards(int *&cards, int numberOfCards, const int MIDDLE_POSITION, const int MAX_CARD_STRING_LENGTH, bool printOnlyFirstDealerCard)
{
    cout << setw(MIDDLE_POSITION) << "Dealer" << endl;

    // Print the cards
    int cardIndex = 0;
    do
    {
        char *card = new char[MAX_CARD_STRING_LENGTH];
        _getCard(cards[cardIndex++], card, MAX_CARD_STRING_LENGTH);
        cout << setw(MIDDLE_POSITION) << card << endl;
        delete[] card;
    } while (!printOnlyFirstDealerCard && cardIndex < numberOfCards);

    cout << endl;
}

//-----------------------------------------------------------------
// int _bestValue(int *&cards, int &numberOfCards) const
//
// Summary: Calculates the best value for a set of cards (closest
//          to but lower or equal to 21)
// Returns: The value as an integer
//-----------------------------------------------------------------
int BlackjackGame::_bestValue(int *&cards, int &numberOfCards) const
{
    int total = 0;
    int aces = 0;

    // Calculate the sum and the number of aces
    for (int i = 0; i < numberOfCards; i++)
    {
        int rank = _getRank(cards[i]);
        total += rank;

        if (rank == 11)
        {
            aces++;
        }
    }

    // Convert aces from 11 to 1 if needed
    while (total > BLACKJACK && aces > 0)
    {
        total -= 10;
        aces--;
    }

    return total;
}

//-----------------------------------------------------------------
// int _getRank(int card) const
//
// Summary: Calculates the rank (value) for a card
// Returns: The value as an integer
//-----------------------------------------------------------------
int BlackjackGame::_getRank(int card) const
{
    int rank = card % 13;

    if (rank < 1) // King
    {
        return 10;
    }
    else if (rank < 2) // Ace
    {
        return 11;
    }
    else if (rank < 11) // 2-10
    {
        return rank;
    }
    else // Jack and Queen
    {
        return 10;
    }
}

//-----------------------------------------------------------------
// void _getCard(int card, char *outCard, const int MAX_CARD_STRING_LENGTH)
//
// Summary: Converts the card integer value to a string. The string
//          outCard has to be able to hold at least 4 char
// Returns: -
//-----------------------------------------------------------------
void BlackjackGame::_getCard(int card, char *outCard, const int MAX_CARD_STRING_LENGTH)
{
    // Suit
    switch (card % 4)
    {
    case 0:
        strcpy_s(outCard, MAX_CARD_STRING_LENGTH, "S"); // Spades
        break;
    case 1:
        strcpy_s(outCard, MAX_CARD_STRING_LENGTH, "C"); // Club
        break;
    case 2:
        strcpy_s(outCard, MAX_CARD_STRING_LENGTH, "H"); // Heart
        break;
    case 3:
        strcpy_s(outCard, MAX_CARD_STRING_LENGTH, "D"); // Diamond
        break;
    }

    // Rank
    const int VALUE = card % 13;
    switch (VALUE)
    {
    case 0:
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, "K");
        break;
    case 1:
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, " ");
        break;
    case 11:
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, "J");
        break;
    case 12:
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, "Q");
        break;
    default:
        int const MAX_RANK_LENGTH = 3;
        char temp[MAX_RANK_LENGTH];
        _itoa_s(VALUE, temp, MAX_RANK_LENGTH, 10);
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, temp);
        break;
    }
}