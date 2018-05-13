// Preprocessor directives
#ifndef BLACKJACKPLAYER_H
#define BLACKJACKPLAYER_H

// Usings
#include "IPlayer.h"
#include "IGame.h"

class BlackjackPlayer : public IPlayer {
public:
    BlackjackPlayer(int money) : _money(money) {}
    bool setGame(IGame* game);
    bool play(int numberOfTimes);
    inline int getMoney() const;
    inline int getBetCount() const;
private:
    IGame* _game = nullptr;
    int _money;
    int _betCount = 0;
    const int CRAP_ID = 123456;
    int _placeBet();
    void _printScore(int win) const;
};

inline int BlackjackPlayer::getMoney() const
{
    return _money;
}

inline int BlackjackPlayer::getBetCount() const
{
    return _betCount;
}

#endif