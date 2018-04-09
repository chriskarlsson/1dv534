/**********************************************************************/
// File:	debug.cpp
// Summary:	Practice file for Lab 1, Step 1
//			The program reads a string of characters. Prints all 
//			occurrences of letters and numbers, sorted in alphabetical 
//			and numerical order. Letters will be converted to uppercase.
//			Other characters are filtered out, while number of white 
//			spaces are counted.
// Version: Version 1.1 - 2013-03-17
// Author:	Anne Norling
// -------------------------------------------
// Log:	2003-08-11	Created the file. Anne
//		2013-03-17	Uppdate  Version 1.1 by Anne. 
//					Converted to English and VS 2012 
//		2015-03-05	Revised by Anne. Converted to VS 2013
//      2018-04-02  Debugged by Christoffer
/**********************************************************************/

// Preprocessor directives
#include <iostream>
#include <cstring>
#include <debug.h>

// Usings
using std::cin;
using std::cout;
using std::endl;
using std::strlen;

//-----------------------------------------------------------------------------
// int debug()
//
// Summary: Extracts alpha numerics and sorts them.
// Returns: 0
//-----------------------------------------------------------------------------
int debug()
{
    const int SIZE = 100;

    char str[SIZE] = "", newStr[SIZE] = "";
    int whitespaces;

	cout << "Enter a number of mixed characters: ";
    cin.getline(str, SIZE);

    whitespaces = getAlphaNumerics(str, newStr);

    cout << strlen(str) - strlen(newStr) << " characters were filtered out,"
         << " out of which " << whitespaces << " whitespaces were encountered.\n";
	
    sortString(newStr);

    cout << "New sorted string: " << newStr << endl;
	
	return 0;
}

//-----------------------------------------------------------------------------
// int GetAlphaNumerics(const char * str, char * newStr)
//
// Summary: Extracts alpha numerics and from str to newStr
// Returns: Number of whitespaces in str
//-----------------------------------------------------------------------------
int getAlphaNumerics(const char * str, char * newStr)
{
    int count = 0;
    char *pStr, ch;
    pStr = (char*)str;

    auto index = 0;
    while (*pStr != '\0')
    {
        if (isalnum(*pStr))
        {
            ch = toupper(*pStr);
            newStr[index++] = ch;
        }
        else if (*pStr == ' ')
        {
            count++;
        }

        pStr++;
    }

    newStr[index] = '\0';

    return count;
}

//-----------------------------------------------------------------------------
// void SortString(char * newStr)
//
// Summary: Sorts newStr
// Returns: -
//-----------------------------------------------------------------------------
void sortString(char * newStr)
{
    int temp, i, j, stringLength;
    stringLength = strlen(newStr);
    for (i = 0; i < stringLength; i++)
    {
        for (j = i + 1; j < stringLength; j++)
        {
            if (newStr[j] < newStr[i])	// sorts in alphabetical
            {						// and numerical order
                temp = newStr[i];
                newStr[i] = newStr[j];
                newStr[j] = temp;
            }
        }
    }
}
