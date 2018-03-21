/**********************************************************************/
// File:	Clock.cpp
// Summary: This class represents a clock, that can be used to
//			read the correct time. The clock gets its time from
//			your computer's system clock, and returns it in the 
//			form of a MyTime-object.
// Version:	Version 1.2 - 2013-03-17
// Owner:	Christer Lundberg 
// -------------------------------------------
// Log:	1998-06-23	Created the file. Christer
//		2003-08-11	Uppdate Version 1.1 by Christer. The class was
//					suited to the newer naming standard for header files. 
//					(Previously named time.h is now ctime.)
//		2013-03-17	Uppdate  Version 1.2 by Anne. Converted to English and VS 2012 
//		2015-03-05 Revised by Anne. Converted to VS 2013
/**********************************************************************/

 #include <ctime>
 #include <MyTime.h>
 #include <Clock.h>


 MyTime Clock::give_me_the_time()
 {
	 time_t     t = time(0);
	 struct tm *p = localtime(&t);
	 
	 return MyTime(p->tm_hour, p->tm_min, p->tm_sec);
 }


 Clock::operator MyTime()
 {
	 return give_me_the_time();
 }

