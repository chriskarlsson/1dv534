//
// File:	Clock.h
// Summary: This class represents a clock, that can be used to
//			read the correct time. The clock gets its time from
//			your computer's system clock, and returns it in the 
//			form of a MyTime-object.
// Version:	Version 1.2 - 2015-03-05 
// Owner:	Christer Lundberg 
// -------------------------------------------
// Log:	1998-06-23 Created the file. Christer
//		2013-03-17 Uppdate Version 1.2 by Anne. Converted to English and VS 2012
//		2015-03-05 Revised by Anne. Converted to VS 2013
/**********************************************************************/


 #ifndef CLOCK_H
 #define CLOCK_H


 class MyTime;

 class Clock {
 public:
	 Clock() {}
	 MyTime give_me_the_time();
	 operator MyTime();
 };

 #endif
