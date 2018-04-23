#pragma once
#ifndef STRING_H // String.h
#define STRING_H

#include <ostream> // ostream
#include <istream> // istream

using std::ostream;
using std::istream;

class String
{
    friend String operator+ (const char* cString, const String& string);
    friend bool operator== (const char* cString, const String& string);
    friend ostream& operator<< (ostream& os, const String& string);
    friend istream& operator>>(istream& is, String&  string);
public:
    inline String();
    String(const String& str);
    String(const char* c);
    inline ~String();
    const String operator+(const String& string) const;
    const String operator+(const char* cString) const;
    void operator=(const String& string);
    void operator=(const char* cString);
    bool operator==(const String& string) const;
    bool operator==(const char* cString) const;
    inline const char* toC_str() const;
    inline size_t getLength() const;
private:
    char* _strPtr;
    size_t _strLen;
};

//-----------------------------------------------------------------------------
// String()
//
// Summary: Default constructor.
// Returns: -
//-----------------------------------------------------------------------------
inline String::String()
{
    _strPtr = new char[1]{ 0 };
    _strLen = 0;
}

//-----------------------------------------------------------------------------
// ~String()
//
// Summary: Destructor.
// Returns: -
//-----------------------------------------------------------------------------
inline String::~String()
{
    delete[] _strPtr;
}

//-----------------------------------------------------------------------------
// const char* toC_str() const
//
// Summary: CString representaion of String object.
// Returns: String as CString.
//-----------------------------------------------------------------------------
inline const char* String::toC_str() const
{
    return _strPtr;
}

//-----------------------------------------------------------------------------
// int String::getLength() const
//
// Summary: Length of String excluding trailing null char.
// Returns: Length of String.
//-----------------------------------------------------------------------------
inline size_t String::getLength() const
{
    return _strLen;
}

#endif /* STRING_H */
