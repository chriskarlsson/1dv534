/**********************************************************************/
// File:	UserInput.cpp
// Summary: Helper class getting input from user.
// Version:	0.0
// Owner:	Christoffer Karlsson
// -------------------------------------------
// Log:     2018-04-06 File created by Christoffer
/**********************************************************************/

// Preprocessor directives
#include <iostream>

// Usings
using std::cin;
using std::cout;
using std::endl;

const int MAX_READ_INPUT_LENGTH = 100;

//-----------------------------------------------------------------
// unsigned int getIntegerFromUser(const char *question)
//
// Summary: Poses a question to the user and returns the answer as an integer
// Returns: A positive integer
//-----------------------------------------------------------------
unsigned int getIntegerFromUser(const char *question)
{
    unsigned int value;

    while (true)
    {
        // Pose question and read answer
        cout << question << ": ";
        cin >> value;

        if (cin.fail())
        {
            // Explain what went wrong
            cout << "Invalid input. Please enter a positive integer." << endl;
            // Clear error
            cin.clear();
            // Clear input (this has to be done after error clearing)
            cin.ignore(MAX_READ_INPUT_LENGTH, '\n');
        }
        else
        {
            // Clear input 
            cin.ignore(MAX_READ_INPUT_LENGTH, '\n');
            return value;
        }
    }
}

//-----------------------------------------------------------------
// bool userYesOrNo(char *question)
//
// Summary: Asks the user the supplied question.
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------
bool userYesOrNo(const char *question)
{
    char input[MAX_READ_INPUT_LENGTH];

    // Ask the user if program should re-run and read input
    cout << endl << question << " (Y/n): ";
    cin.getline(input, MAX_READ_INPUT_LENGTH);
    cout << endl;

    // Check if answer is negative
    auto answer = toupper(input[0]) != 'N';

    return answer;
}