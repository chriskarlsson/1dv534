/**********************************************************************/
// File:    Texthandler.cpp
// Summary: Reads texts from file and store them in memory.
// Version: 0.0
// Author:  Christoffer Karlsson
// ------------------------------------------
// Log:     2018-05-03 File created by Christoffer
/**********************************************************************/

// Preprocessor directives#include <cstring> // strcmp, strcpy, strlen
#include <iostream> // cout, ios
#include <fstream> // fstream
#include <exception> // invalid_argument
#include "Texthandler.h"

// Usings
using std::cout;
using std::endl;
using std::fstream;
using std::invalid_argument;
using std::ios;
using std::strcmp;
using std::strcpy;
using std::strlen;

//-----------------------------------------------------------------------------
// Texthandler(char const * FILENAME, int NUMBER_OF_TEXTS)
//
// Summary: Constructor. Reads max NUMBER_OF_TEXTS from FILENAME.
// Returns: -
//-----------------------------------------------------------------------------
Texthandler::Texthandler(char const * FILENAME, int NUMBER_OF_TEXTS)
{
    _maxNumberOfTexts = NUMBER_OF_TEXTS;

    // Create the array
    _texts = new char*[NUMBER_OF_TEXTS];

    // Open the file
    fstream file(FILENAME, ios::in);

    if (file.is_open())
    {
        // Buffers
        const auto lineBuffer = new char[_TEXT_MAX_SIZE + 1] { 0 };
        const auto textBuffer = new char[_TEXT_MAX_SIZE + 1] { 0 };

        // Pointer to traverse text buffer
        auto textBufferPtr = textBuffer;

        // Loop file while there is new rows
        while (file.getline(lineBuffer, _TEXT_MAX_SIZE)
               && _numberOfTexts < _maxNumberOfTexts)
        {
            // Abort if text is too long
            if (strlen(textBuffer) + strlen(lineBuffer) >= _TEXT_MAX_SIZE)
            {
                cout << "Text nr " << _numberOfTexts + 1
                     << " contains too many characters. Only "
                     << _TEXT_MAX_SIZE << " per text is allowed." << endl;

                throw invalid_argument("Text contains too many characters");
            }
            else if (strcmp(lineBuffer, "%%%%%") != 0) // Add buffer to string
            {                                          // if end is not reached
                // Pointer to traverse line buffer
                auto lineBufferPtr = lineBuffer;

                // Copy to string and handle special chars
                while (*lineBufferPtr) {
                    switch (*lineBufferPtr)
                    {
                    case (-59):
                        *textBufferPtr = -113; // Å
                        break;
                    case (-60):
                        *textBufferPtr = -114; // Ä
                        break;
                    case (-42):
                        *textBufferPtr = -103; // Ö
                        break;
                    case (-27):
                        *textBufferPtr = -122; // å
                        break;
                    case (-28):
                        *textBufferPtr = -124; // ä
                        break;
                    case (-10):
                        *textBufferPtr = -108; // ö
                        break;
                    default:
                        *textBufferPtr = *lineBufferPtr;
                        break;
                    }

                    ++lineBufferPtr;
                    ++textBufferPtr;
                }

                // Add new line char
                *textBufferPtr = '\n';
                ++textBufferPtr;
            }
            else if (textBufferPtr != textBuffer) // Add non zero length
            {                                     // string to text collection
                // Add null termination
                *(textBufferPtr) = '\0';

                // Allocate space and copy string to text collection
                _texts[_numberOfTexts] = new char[textBufferPtr - textBuffer + 1]{ 0 };
                strcpy(_texts[_numberOfTexts], textBuffer);

                // Restore pointer
                textBufferPtr = textBuffer;

                // Increase text counter
                _numberOfTexts++;
            }
        }

        // Cleanup
        delete[] lineBuffer;
        delete[] textBuffer;

        file.close();
    }
}