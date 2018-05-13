// Preprocessor directives
#ifndef CRAPGAMEWRAPPER_H
#define CRAPGAMEWRAPPER_H

// Usings
#include "../IGame.h"
#include "CrapGame.h"

class CrapGameWrapper : public IGame {
public:
    CrapGameWrapper();
    ~CrapGameWrapper();
    int play(char* bet, int amount);
    inline int getID() const;
private:
    CrapGame* _game;
};

inline int CrapGameWrapper::getID() const
{
    return _game->getID();
}

#endif