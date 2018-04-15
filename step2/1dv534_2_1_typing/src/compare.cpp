//-----------------------------------------------------------------------------
// File:    compare.cpp
// Summary: Compares two char *.
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------------
// Log:   2018-04-14 File created by Christoffer
//
//-----------------------------------------------------------------------------

// Preprocessor directives
#include <compare.h>
#include <cstring> // strlen

// Usings
using std::strlen;

//-----------------------------------------------------------------------------
// bool equal(const char * FIRST, const char * SECOND)
//
// Summary: Compares two char *.
// Returns: True if equal.
//-----------------------------------------------------------------------------
bool Compare::equal(const char * FIRST, const char * SECOND)
{
    if (strlen(FIRST) != strlen(SECOND))
    {
        return false;
    }

    for (int i = 0; FIRST[i] != '\0'; i++)
    {
        if (FIRST[i] != SECOND[i])
        {
            return false;
        }
    }

    return true;
}
