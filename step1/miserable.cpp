//-----------------------------------------------------------------------------
// File:    miserable.cpp
// Summary: Presents statistics of the measurements in templog.txt
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------------
// Log:   2018-04-01 File created by Christoffer
//
//-----------------------------------------------------------------------------

// Preprocessor directives
#include <iostream> // cin and cout
#include <iomanip> // setw and setprecision
#include <sstream> // stringstream
#include <miserable.h>

// OS specific adjustments
#ifdef _WIN32
    //code for Windows
    #define CLEARSCREEN system("clear")
    #define _CRTDBG_MAP_ALLOC

    #include <cstdlib>
    #include <crtdbg.h>

    #ifdef _DEBUG
        #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    #endif
    #define CLEARSCREEN system("cls")
#elif __APPLE__
    //code for mac
#elif __linux__
    //code for linux
    #define CLEARSCREEN system("clear")
#else
   error "Unknown compiler"
#endif


// Usings
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::stringstream;

//-----------------------------------------------------------------------------
// int run()
//
// Summary: Presents statistics of the measurements in templog.txt.
// Returns: 0 when user stops execution.
//-----------------------------------------------------------------------------
int Miserable::run()
{
    const auto NUMBER_OF_MEASUREMENTS = 24;
    const auto MEASUREMENTS_PER_ROW = 6;

    displayIntroduction();

    // Loop the menu until aborted by user
    while (true)
    {
        CLEARSCREEN;
        int menuSelection = getMenuSelection();

        switch (menuSelection)
        {
            case 1: // All measurements
                cout << getMeasurements(MEASUREMENTS_PER_ROW,
                                        NUMBER_OF_MEASUREMENTS);
                break;
            case 2: // Max and min values
                cout << getMaxMin();
                break;
            case 3: // Average
                cout << getAverage();
                break;
            case 4:
                cout << endl
                     << endl
                     << "Terminating the program." << endl;
                return 0;
            default:
                break;
        }

        cout << endl
             << endl
             << "Press Enter to continue:";
        cin.get();
    }
}

//-----------------------------------------------------------------------------
// void displayIntroduction()
//
// Summary: Presents an intro screen to the user.
// Returns: -
//-----------------------------------------------------------------------------
void Miserable::displayIntroduction() const
{
    cout << endl
         << endl
         << "Temperature Statistics" << endl
         << "----------------------" << endl
         << endl
         << "Reading logged values for processing and presentation..."
         << endl
         << endl
         << "Press Enter for menu: ";
    cin.get();
}

//-----------------------------------------------------------------------------
// int getMenuSelection()
//
// Summary: Presents the menu to the user and reads the menu selection.
// Returns: An integer corresponding to the menu item.
//-----------------------------------------------------------------------------
int Miserable::getMenuSelection() const
{
    int menuSelection;
    const int FIRST_ITEM = 1;
    const int LAST_ITEM = 4;

    // Display menu
    cout << endl
         << endl
         << "MENU" << endl
         << "----" << endl
         << endl
         << "1. Display temperature values" << endl
         << "2. View maximum and minimum temperatures" << endl
         << "3. View average temperature" << endl
         << "4. Quit" << endl
         << endl
         << "Make your choice: ";

    // Loop until input is correct
    while (!(cin >> menuSelection) ||
           menuSelection < FIRST_ITEM ||
           menuSelection > LAST_ITEM)
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

//-----------------------------------------------------------------------------
// void getMeasurements(const int MEASUREMENTS_PER_ROW,
//                      const int NUMBER_OF_MEASUREMENTS)
//
// Summary: Reads the last 24 measurements.
// Returns: A string containing the explanations and the values.
//-----------------------------------------------------------------------------
string Miserable::getMeasurements(const int MEASUREMENTS_PER_ROW,
                                  const int NUMBER_OF_MEASUREMENTS)
{
    stringstream output;
    double measurement;
    _measurements->reset();

    // Add header to output string
    output << endl
           << "Displaying the latest " << NUMBER_OF_MEASUREMENTS
           << " temperature values:" << endl
           << endl;

    // Loop over measurements
    for (int i = 0; i < NUMBER_OF_MEASUREMENTS; i++)
    {
        // New row after MEASUREMENTS_PER_ROW
        if (i % MEASUREMENTS_PER_ROW == 0)
        {
            output << endl;
        }

        // Read measurement
        if (_measurements->next(measurement))
        {
            // Add measurement to output string
            output << fixed << setprecision(2) << setw(8)
                   << measurement;
        }
        else // Break loop if reading fail
        {
            output << endl
                   << endl
                   << "Measurement file contains too few measurements. "
                   << "Expected: " << NUMBER_OF_MEASUREMENTS << ". "
                   << "Found: " << i + 1 << "." << endl;
            break;
        }
    }

    return output.str();
}

//-----------------------------------------------------------------------------
// void getMaxMin()
//
// Summary: Calculates the max and min of all measurements.
// Returns: A string containing the explanations and the max and min values.
//-----------------------------------------------------------------------------
string Miserable::getMaxMin()
{
    stringstream output;
    double measurement;
    auto max = 0.0;
    auto min = 0.0;
    _measurements->reset();

    output << endl
           << "Calculating the maximum and minimum temperature..."
           << endl;

    // Set max and min to the first measurement
    _measurements->next(measurement);
    max = min = measurement;

    // Loop over measurements
    while (_measurements->next(measurement))
    {
        if (measurement > max)
        {
            max = measurement;
        }
        else if (measurement < min)
        {
            min = measurement;
        }
    }

    // Add max and min to output string
    output << endl
           << "Maximum temperature: " << fixed << setprecision(2)
           << max << " degrees Celcius" << endl
           << endl
           << "Minimum temperature: " << min << " degrees Celcius"
           << endl;

    return output.str();
}

//-----------------------------------------------------------------------------
// void getAverage()
//
// Summary: Calculates the average of all measurements.
// Returns: A string containing the explanations and the average value.
//-----------------------------------------------------------------------------
string Miserable::getAverage()
{
    stringstream output;
    double measurement;
    auto measurementCounter = 0;
    auto sum = 0.0;
    _measurements->reset();

    output << endl
           << "Calculating average temperature..." << endl;

    // Loop over measurements
    while (_measurements->next(measurement))
    {
        measurementCounter++;
        sum += measurement;
    }

    // Calculate average
    auto average = sum / measurementCounter;

    // Add average to output string
    output << endl
           << "Average temperature: " << fixed << setprecision(2)
           << average << " degrees Celcius" << endl;

    return output.str();
}
