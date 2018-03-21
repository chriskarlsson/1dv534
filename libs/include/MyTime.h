/**********************************************************************/
// File:	MyTime.h
// Summary:	This class represents a specific time (0-24) with a 
//			resolution of hours, minutes and seconds. It supports
//			input and output via iostream and subtraction
//			between MyTime objects.
// Version:	Version 1.2 - 2015-03-05
// Owner:	Christer Lundberg 
// -------------------------------------------
// Log:	1998-06-23	Created the file. Christer
//		2002-08-28	Uppdate Version 1.1 by Christer. The class is now
//					adapted to work with std::iostream, ie. the new
//					iostream class located in the header file <iostream>
//		2013-03-17	Uppdate  Version 1.2 by Anne. Converted to English and VS 2012
//		2015-03-05	Revised by Anne. Converted to VS 2013
/**********************************************************************/


 #ifndef MYTIME_H
 #define MYTIME_H

 #include <iostream>
 using std::cout;
 using std::endl;
 using std::istream;
 using std::ostream;


 class MyTime {
	 friend std::ostream& operator<<( std::ostream&, const MyTime& );
	 friend std::istream& operator>>( std::istream&,       MyTime& );
 public:
	 MyTime(                         ): hh(0), mm(0), ss(0)          {}
	 MyTime( int h, int m, int s = 0 ): hh(h), mm(m), ss(s)          {}
	 MyTime( const MyTime& t         ): hh(t.hh), mm(t.mm), ss(t.ss) {}
	 MyTime( const char* );
	 MyTime  operator-( const MyTime& ) const;
	 MyTime& operator=( const MyTime& );
 private:
	int hh;
	int mm;
	int ss;
 };

 #endif
