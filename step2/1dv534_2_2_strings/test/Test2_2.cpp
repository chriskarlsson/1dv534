/**********************************************************************/
// File:	Test2_2.cpp
// Summary:	Test file for Lab 2, Step 2
//          The program will test functionality for class String, which
//			is aimed to handle a number of common string-operations.
//			If defined according to requirements in given specification,
//			the result of execution is expected to present console
//			outputs like examples suggested in comments to test code.
//			NO CHANGES of the predefined code are allowed, except those
//			needed to handle exceptions, if solving the optional task.
// Version: Version 1.1 - 2013-04-08
// Author:	Anne Norling
// ------------------------------------------
// Log:		2007-03-14	Created the file. Anne
//			2013-04-08	Uppdate  Version 1.1 by Anne.
//						Converted to English and VS 2012
//			2015-03-06	Revised by Anne. Converted to VS 2013
//			2018-04-05  Code tested for VS 2017, by Anne
/**********************************************************************/

#include <iostream>
#include <limits>
#include "String.h"
using std::cout;
using std::cin;
using std::endl;

class Application
{
public:
	int run();
    int runWithErrorHandling();
};

int Application::run()
{
	String str1("Hello ");
	String str2(str1);
	cout << str1 << str2 << endl;	// Shall print "Hello Hello "

	str2 = "my world!";
	cout << str1 << str2 << endl;	// Shall print "Hello my world!"

	String str3;
	cout << "Enter a name: ";
	cin >> str3;				// (... The user enters for instance "Pluto"...)
    str2 = str1 + str3;
    cout << str2 << endl;		// Shall print "Hello Pluto"
    str2 = "Goodbye " + str3;
    cout << str2 << endl;		// Shall print "Goodbye Pluto"
    cout << str1 << "and " << "Goodbye "
            << (str1 == "Goodbye " ? "is " : "is not ") << "the same word!\n";
                                // Shall print "Hello and Goodbye is not the same word!"

	return 0;
}

int Application::runWithErrorHandling()
{
    auto returnValue = 0;

    // Allocation exceptions thrown here has to be catched in main. These are
    // used in the rest of the program so continuing makes no sence.
    String str1("Hello ");
    String str2(str1);

    cout << str1 << str2 << endl;

    try
    {
        str2 = "my world!";
        cout << str1 << str2 << endl;
    }
    catch (bad_alloc)
    {
        returnValue = 1;
    }

    try
    {
        String str3;
        cout << "Enter a name: ";

        while (true)
        {
            cin >> str3;
            if (cin.fail() || str3.getLength() == 0)
            {
                // Explain what went wrong
                cout << "Invalid input. Please try again: ";
                // Clear error
                cin.clear();
                // Clear input (this has to be done after error clearing)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                // Clear input
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }

        str2 = str1 + str3;
        cout << str2 << endl;

        str2 = "Goodbye " + str3;
        cout << str2 << endl;
    }
    catch (bad_alloc)
    {
        returnValue = 1;
    }

    cout << str1 << "and " << "Goodbye "
            << (str1 == "Goodbye " ? "is " : "is not ") << "the same word!\n";

    return returnValue;
}

int main()
{
	Application myApp;
    myApp.run();

    try
    {
        return myApp.runWithErrorHandling();
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        return(1);
    }
}
