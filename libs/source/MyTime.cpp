/**********************************************************************/
// File:	MyTime.cpp
// Summary:	This class represents a specific time (0-24) with a 
//			resolution of hours, minutes and seconds. It supports
//			input and output via iostream and subtraction
//			between MyTime objects.
// Version:	Version 1.2 - 2013-03-17
// Owner:	Christer Lundberg 
// -------------------------------------------
// Log:	1998-06-23	Created the file. Christer
//		2003-08-11	Uppdate Version 1.1 by Christer. The class was
//					suited to the newer naming standard for header files. 
//					(eg. Previously named string.h is now cstring.)
//		2013-03-17	Uppdate  Version 1.2 by Anne. Converted to English and VS 2012
//		2015-03-05	Revised by Anne. Converted to VS 2013
/**********************************************************************/


#include <cstring>
#include <cstdlib>
#include <MyTime.h>

MyTime::MyTime( const char* time )
{
	char str[50];
	char *ptr;

	strcpy(str, time);
	ptr = strtok(str, " :,.;");

	if (ptr)
		hh = atoi(ptr);
	else {
		hh = 0;
		mm = 0;
		ss = 0;
		return;
	}
	ptr = strtok(NULL, " :,.;");

	if (ptr)
		mm = atoi(ptr);
	else {
		mm = 0;
		ss = 0;
		return;
	}
	ptr = strtok(NULL, " :,.;");

	if (ptr)
		ss = atoi(ptr);
	else
		ss = 0;
}


MyTime MyTime::operator-( const MyTime& t ) const
{
	MyTime to;
	long tmp;

	tmp = (hh * 3600 + mm * 60 + ss) - (t.hh * 3600 + t.mm * 60 + t.ss);

	if (tmp < 0)
		tmp = -tmp;
	to.hh = tmp / 3600;
	tmp  %= 3600;
	to.mm = tmp / 60;
	tmp  %= 60;
	to.ss = tmp;

	return to;
}


MyTime& MyTime::operator=( const MyTime& t )
{
	hh = t.hh;
	mm = t.mm;
	ss = t.ss;

	return *this;
}


ostream& operator<<( ostream& os, const MyTime& t )
{
	if (t.hh < 10)
		os << '0';
	os << t.hh << ':';

	if (t.mm < 10)
		os << '0';
	os << t.mm << ':';

	if (t.ss < 10)
		os << '0';
	os << t.ss;

	return os;
}


istream& operator >> ( istream& is, MyTime& t )
{
	char stg[50];
	char *p;

	cout << "Mata in klockslaget p† formen tt:mm eller tt:mm:ss : ";
	is   >> stg;

	p = strtok(stg," :,.;");
	if (p)
		t.hh = atoi(p);
	else {
		t.hh = 0;
		t.mm = 0;
		t.ss = 0;
		return is;
	}
	p = strtok(NULL," :,.;");
	if (p)
		t.mm = atoi(p);
	else {
		t.mm = 0;
		t.ss = 0;
		return is;
	}
	p = strtok(NULL," :,.;");
	if (p)
		t.ss = atoi(p);
	else
		t.ss = 0;
	return is;
}
