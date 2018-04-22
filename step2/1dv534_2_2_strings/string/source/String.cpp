//-----------------------------------------------------------------------------
// File:    String.cpp
// Summary: Class allowing a set of operations (+, =, ==, >> and <<) on
//          strings.
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------------
// Log:   2018-04-22 File created by Christoffer
//
//-----------------------------------------------------------------------------

// Preprocessor directives
#include <cstring> // strlen, strcpy, strcat
#include <ostream> // ostream
#include <istream> // istream
#include <String.h>

// Usings
using std::strlen;
using std::strcpy;
using std::strcat;
using std::isblank;
using std::iscntrl;

//-----------------------------------------------------------------------------
// String()
//
// Summary: Constructor taking a string.
// Returns: -
//-----------------------------------------------------------------------------
String::String(const String& string)
{
   _strLen = string.getLength();
   _strPtr = new char[_strLen + 1]{0};
   strcpy(_strPtr, string.toC_str());
}

//-----------------------------------------------------------------------------
// String()
//
// Summary: Constructor taking a const char*.
// Returns: -
//-----------------------------------------------------------------------------
String::String(const char* cString)
{
    _strLen = strlen(cString);
    _strPtr = new char[_strLen+1]{0};
    strcpy(_strPtr, cString);
}

//-----------------------------------------------------------------------------
// const String operator+ (const String& string) const
//
// Summary: Concatenates two strings.
// Returns: The resulting string.
//-----------------------------------------------------------------------------
const String String::operator+ (const String& string) const
{
    auto tempCString = new char[string.getLength() + _strLen + 1]{0};
    strcpy(tempCString, _strPtr);
    strcat(tempCString, string.toC_str());

    String tempString(tempCString);

    delete [] tempCString;

    return tempString;
}

//-----------------------------------------------------------------------------
// const String operator+ (const char* cString) const
//
// Summary: Concatenates a string and a const char *.
// Returns: The resulting string.
//-----------------------------------------------------------------------------
const String String::operator+ (const char* cString) const
{
    auto tempCString = new char[strlen(cString) + _strLen + 1]{0};
    strcpy(tempCString, _strPtr);
    strcat(tempCString, cString);

    String tempString(tempCString);

    delete [] tempCString;

    return tempString;
}

//-----------------------------------------------------------------------------
// void operator=(const String& string)
//
// Summary: Copies the members of string to this object.
// Returns: -
//-----------------------------------------------------------------------------
void String::operator=(const String& string)
{
    delete [] _strPtr;
    _strLen = string.getLength();
    _strPtr = new char[_strLen + 1]{0};
    strcpy(_strPtr, string.toC_str());
}

//-----------------------------------------------------------------------------
// void operator= (const char* cString)
//
// Summary: Copies the members of cString to this object.
// Returns: -
//-----------------------------------------------------------------------------
void String::operator= (const char* cString)
{
    delete [] _strPtr;
    _strLen = strlen(cString);
    _strPtr = new char[_strLen + 1]{0};
    strcpy(_strPtr, cString);
}

//-----------------------------------------------------------------------------
// bool operator== (const String& string) const
//
// Summary: Comparison of a string and a const char*.
// Returns: True if equal.
//-----------------------------------------------------------------------------
bool String::operator== (const String& string) const
{
    auto compare = strcmp(_strPtr, string.toC_str());
    return compare == 0;
}

//-----------------------------------------------------------------------------
// bool operator== (const char* cString) const
//
// Summary: Comparison of two strings.
// Returns: True if equal.
//-----------------------------------------------------------------------------
bool String::operator== (const char* cString) const
{
    auto compare = strcmp(_strPtr, cString);
    return compare == 0;
}

//-----------------------------------------------------------------------------
// String operator+ (const char* cString, const String& string)
//
// Summary: Extends const char * with concatenatination with a string.
// Returns: The resulting string.
//-----------------------------------------------------------------------------
String operator+ (const char* cString, const String& string)
{
    auto tempCString = new char[strlen(cString) + string._strLen + 1]{0};
    strcpy(tempCString, cString);
    strcat(tempCString, string._strPtr);

    String tempString(tempCString);

    delete [] tempCString;

    return tempString;
}

//-----------------------------------------------------------------------------
// bool operator== (const char* cString, const String& string)
//
// Summary: Extends const char * with comparision with a string.
// Returns: The resulting string.
//-----------------------------------------------------------------------------
bool operator== (const char* cString, const String& string)
{
    auto compare = (strcmp(cString, string._strPtr));
    return compare == 0;
}

//-----------------------------------------------------------------------------
// ostream& operator<< (ostream& outputStream, const String&  string)
//
// Summary: Extends ostream with insertion operator from a string.
// Returns: The resulting ostream.
//-----------------------------------------------------------------------------
ostream& operator<< (ostream& outputStream, const String&  string)
{
    outputStream << string._strPtr;
    return outputStream;
}

//-----------------------------------------------------------------------------
// istream& operator>>(istream& inputStream, String&  string)
//
// Summary: Extends istream with extraction operator to a string.
// Returns: The calling istream.
//-----------------------------------------------------------------------------
istream& operator>>(istream& inputStream, String&  string)
{
    // Delete the current value
    delete [] string._strPtr;

    // Setup
    int BUFFER_SIZE = 20;
    auto bufferCString = new char[BUFFER_SIZE]{0};
    auto index = 0;

    // Loop the input stream
    while (true)
    {
        // Take one char from the stream
        char c = inputStream.get();

        // Increase the size of the buffer if needed
        if (index >= BUFFER_SIZE - 1)
        {
            BUFFER_SIZE *= 2;
            auto tempCString = new char[BUFFER_SIZE]{0};
            strcpy(tempCString, bufferCString);
            delete [] bufferCString;
            bufferCString = tempCString;
        }

        // Break if blank or ctrl char is detected
        if (isblank(c) || iscntrl(c))
        {
            inputStream.putback(c);
            break;
        }

        // Add char to string
        bufferCString[index] = c;
        index++;
    }

    // Transfer the string to the string object
    string._strLen = strlen(bufferCString);
    string._strPtr = new char[string._strLen + 1]{0};
    strcpy(string._strPtr, bufferCString);

    // Free the buffer
    delete [] bufferCString;

    return inputStream;
}
