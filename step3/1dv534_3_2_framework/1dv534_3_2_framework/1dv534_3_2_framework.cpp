/**********************************************************************/
// File:	1dv534_3_2_framework.cpp
// Summary: Main file for running a collection of games.
// Version:	0.0
// Owner:	Christoffer Karlsson
// -------------------------------------------
// Log:     2018-04-06 File created by Christoffer
/**********************************************************************/

// Preprocessor directives
#pragma comment( lib, "C:\\repo\\1dv534\\libs\\lib\\menu.lib")
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "IGame.h"
#include "IPlayer.h"
#include "BlackjackPlayer.h"
#include "BlackjackGame.h"
#include "CrapPlayer.h"
#include "CrapGameWrapper.h"
#include "UserInput.h"
#include "menu.h"
#include "GameFramework.h"
#include "1dv534_3_2_framework.h"

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
using std::cout;
using std::cin;
using std::endl;

//-----------------------------------------------------------------------------
// void main()
//
// Summary: Runs the game framework.
// Returns: -
//-----------------------------------------------------------------------------
int main()
{
    // Make sure there are no memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Loop to main menu until user exits
    while (true)
    {
        auto choice = mainMenu();

        switch (choice)
        {
        case 1:
            gameSelection = gameSelectionMenu();
            break;
        case 2:
            CLEARSCREEN;
            turns = getIntegerFromUser("How many turns that are to be played");
            break;
        case 3:
            CLEARSCREEN;
            money = getIntegerFromUser("How much money should the user have");
            break;
        case 4:
            showStatus();
            break;
        case 5:
            startGame();
            break;
        case 6:
            return 0;
        }
    }
}

//-----------------------------------------------------------------------------
// void mainMenu()
//
// Summary: Shows the main menu.
// Returns: User menu selection.
//-----------------------------------------------------------------------------
int mainMenu()
{
    const int NUMBER_OF_ITEMS = 6;
    const char * HEADER = "Welcome to My Game Collection\n---------------------\nWhat do you want to do?";
    const char ** MENU_ITEMS = new const char*[NUMBER_OF_ITEMS];
    MENU_ITEMS[0] = "Select a game (default Blackjack)";
    MENU_ITEMS[1] = "Select how many turns that are to be played (default 1)";
    MENU_ITEMS[2] = "Select the amount of money the player should have to start with (default 100)";
    MENU_ITEMS[3] = "Show status";
    MENU_ITEMS[4] = "Start the game";
    MENU_ITEMS[5] = "End the game";

    Menu menu(HEADER, MENU_ITEMS, NUMBER_OF_ITEMS);

    return menu.getMenuSelection();
}

//-----------------------------------------------------------------------------
// void gameSelectionMenu()
//
// Summary: Shows a game selection menu.
// Returns: User game selection.
//-----------------------------------------------------------------------------
Game gameSelectionMenu()
{
    const int NUMBER_OF_ITEMS = 2;
    const char * HEADER = "Please select a game";
    const char ** MENU_ITEMS = new const char*[NUMBER_OF_ITEMS];
    MENU_ITEMS[0] = "Blackjack";
    MENU_ITEMS[1] = "Craps";

    Menu menu(HEADER, MENU_ITEMS, NUMBER_OF_ITEMS);

    return (Game)menu.getMenuSelection();
}

void showStatus()
{
    CLEARSCREEN;

    switch (gameSelection)
    {
    case Blackjack:
        cout << "Selected game: Blackjack" << endl;
        break;
    case Craps:
        cout << "Selected game: Craps" << endl;
        break;
    default:
        break;
    }
    cout << "Number of turns: " << turns << endl;
    cout << "Amount of money: " << money << endl;

    cout << "Press enter to return ...";

    cin.get();
}

void startGame()
{
    CLEARSCREEN;

    auto result = 1;

    if (gameSelection == Blackjack)
    {
        BlackjackPlayer player(money);
        BlackjackGame game;
        GameFramework gameFramework(&player, &game);
        result = gameFramework.run(turns);
    }
    else if (gameSelection == Craps)
    {
        CrapPlayer player(money);
        CrapGameWrapper game;
        GameFramework gameFramework(&player, &game);
        result = gameFramework.run(turns);
    }
    else
    {
        cout << "Well this is embarassing. The selected game does not exist. Please select another." << endl;
        cout << "Press enter to return ...";
        cin.get();
    }

    if (result != 0)
    {
        cout << "Something went wrong. Please try again." << endl;
        cout << "Press enter to return ...";
        cin.get();
        return;
    }
}