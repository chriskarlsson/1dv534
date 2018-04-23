//-----------------------------------------------------------------------------
// File:    typing.cpp
// Summary: Measure the time it takes for a user to type
//          abcdefghijklmnopqrstuvxyz
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------------
// Log:   2018-04-14 File created by Christoffer
//
//-----------------------------------------------------------------------------

// Preprocessor directives
#include <cstring> // strlen
#include <limits> // numeric_limits, streamsize
#include <iostream> // cin, cout, endl
#include "..\..\..\libs\include\Clock.h" // give_me_the_time
#include "..\..\..\libs\include\MyTime.h" // MyTime
#include "compare.h" // equal
#include "typing.h"

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
using std::strlen;
using std::numeric_limits;
using std::streamsize;

//-----------------------------------------------------------------------------
// int run()
//
// Summary: Measure the time it takes for a user to type
//          abcdefghijklmnopqrstuvxyz
// Returns: 0 when user stops execution.
//-----------------------------------------------------------------------------
int Typing::run()
{
    // Setup
    auto compare = new Compare();
    auto clock = new Clock();
    const char EXPECTED[] = "abcdefghijklmnopqrstuvxyz";
    _printIntroduction();

    // Execute
    do
    {
        char userInput[1000];

        auto start = clock->give_me_the_time();
        _printTask(EXPECTED);
        _getUserInput(userInput);
        auto stop = clock->give_me_the_time();

        CLEARSCREEN;

        if (compare->equal(EXPECTED, userInput))
        {
            cout << "It took: " << start - stop << " (hh:mm:ss)." << endl
                << "Good work!" << endl;
        }
        else
        {
            cout << "The strings didn't match." << endl;
        }
    } while (_userYesOrNo("Try again?"));

    // Cleanup
    delete compare;
    delete clock;

    return 0;
}

//-----------------------------------------------------------------------------
// void _printIntroduction()
//
// Summary: Prints an explanation of the purpose of the application.
// Returns: -
//-----------------------------------------------------------------------------
void Typing::_printIntroduction()
{
    CLEARSCREEN;

    cout << "This application will measure your typing speed." << endl
        << "When you hit enter the string will be shown and the measurement "
        << "will start." << endl;

    cin.get();
}

//-----------------------------------------------------------------------------
// void _printTask(const char * EXPECTED)
//
// Summary: Prints the task that the user should perform.
// Returns: -
//-----------------------------------------------------------------------------
void Typing::_printTask(const char * EXPECTED)
{
    CLEARSCREEN;

    cout << "Please type the following and then press enter:" << endl
        << EXPECTED << endl;
}

//-----------------------------------------------------------------------------
// bool userYesOrNo(const char *QUESTION)
//
// Summary: Asks the user the supplied question.
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------------------
bool Typing::_userYesOrNo(const char *QUESTION)
{
    char input[1000];

    // Ask the user if program should re-run and read input
    cout << endl << QUESTION << " (Y/n): ";
    _getUserInput(input);
    cout << endl;

    // Check if answer is negative
    auto answer = toupper(input[0]) != 'N';

    return answer;
}

//-----------------------------------------------------------------------------
// void _getUserInput(char * userInput)
//
// Summary: Reads first MAX_READ_INPUT_LENGTH chars of user input into
//          userInput and then clear cin buffer.
// Returns: -
//-----------------------------------------------------------------------------
void Typing::_getUserInput(char * userInput)
{
    cin.getline(userInput, numeric_limits<streamsize>::max());

    if (cin.fail())
    {
        // Clear error
        cin.clear();
        // Clear input (this has to be done after error clearing)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
