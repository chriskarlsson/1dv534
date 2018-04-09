/**********************************************************************/
// File:	menu.cpp
// Summary: Generic menu class that display the menu header and items
//          defined in the constructor and returns the user selection.
// Version:	0.0
// Owner:	Christoffer Karlsson
// -------------------------------------------
// Log:     2018-04-01 File created by Christoffer
/**********************************************************************/

// Preprocessor directives
#include <iostream> // cin and cout
#include <menu.h>

// OS specific adjustments
#ifdef _WIN32
    // Windows
    #define CLEARSCREEN system("cls")
#elif __APPLE__
    // Mac OS
    #define CLEARSCREEN system("clear")
#elif __linux__
    // Linux
    #define CLEARSCREEN system("clear")
#else
   error "Unknown compiler"
#endif

// Usings
using std::cin;
using std::cout;
using std::endl;

//-----------------------------------------------------------------------------
// int Menu::getMenuSelection() const
//
// Summary: Displays _HEADER and _ITEMS and loops until user selection is
//          correct.
// Returns: The index (starting at 1) of the chosen item.
//-----------------------------------------------------------------------------
int Menu::getMenuSelection() const
{
    int menuSelection;
    const int FIRST_ITEM = 1;

    // Display menu
    CLEARSCREEN;
    cout << _HEADER << endl;

    for (int item = 0; item < _NUMBER_OF_ITEMS; item++)
    {
        cout << item + 1 << ". " << _MENU_ITEMS[item] << endl;
    }

    cout << endl
         << "Make your choice: ";

    // Loop until input is correct
    while (!(cin >> menuSelection) ||
           menuSelection < FIRST_ITEM ||
           menuSelection > _NUMBER_OF_ITEMS)
    {
        // Clean cin
        if (!cin)
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Invalid input. Please try again." << endl;
    }

    // Clean cin
    cin.ignore(1000, '\n');

    return menuSelection;
}
