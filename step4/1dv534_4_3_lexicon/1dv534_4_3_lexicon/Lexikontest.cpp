/**********************************************************************/
// File:		LexikonTest.cpp
// Summary:		Test file for Lab 3, Step 4
//				The program will test functionality of the 
//				English/Swedish Dictionary, implementated by the
//				Link classes TList and WList .
// Version:		1.0  -  2000-07-15
// Copyright:	2000-07-15, Dept. of Technology, University of Kalmar
// ------------------------------------------
// Log:			2013-05-17	Uppdate  Version 1.1 by Anne. 
//				Converted to VS 2012
//				2015-03-05	Revised by Anne. Converted to VS 2013
/**********************************************************************/


#include <iostream>
#include "List.h"

#include "MemoryLeakDetector.h"

using namespace std;


void show_translation ( char* wword )
{
	const TList* tp = WList::translate(wword);
	if (tp) {
		cout << "™vers„ttning av \"" << wword << "\" :";
		while (tp) {
			cout << '\t' << tp->getWord();
			tp = tp->getSuccessor();
		}
		cout << endl;
	}
	else
		cout << "Ordet \"" << wword << "\" finns ej registrerat!" << endl;
}


void facit ( char* stg )
{
	int i;
	char buf[10];
	cout << "=================================================================\n"
		 << "===        Texten ovan skall vara samma som texten nedan !    ===\n"
		 << "=================================================================\n"
		 << stg << endl << endl;
	for (i=0 ; i<8 ; i++ ) cout <<'\n';
	cout << "Tryck p† Retur s† g†r vi vidare !";
	cin.getline(buf,10);
	for (i=0 ; i<40 ; i++ ) cout <<'\n';
	cout << endl;
}


int main()
{
	if ( !WList::insert("house","hus") )		cout << "Insert 1 misslyckades" << endl;
	if ( !WList::insert("house","logi") )		cout << "Insert 2 misslyckades" << endl;
	if ( !WList::insert("house","koja") )		cout << "Insert 3 misslyckades" << endl;
	if ( !WList::insert("house","hus") )		cout << "Insert 4 misslyckades" << endl;
	if ( !WList::insert("weird","dum") )		cout << "Insert 5 misslyckades" << endl;
	if ( !WList::insert("weird","konstig") )	cout << "Insert 6 misslyckades" << endl;
	if ( !WList::insert("set","st„lla") )		cout << "Insert 7 misslyckades" << endl;
	if ( !WList::insert("set","apparat") )		cout << "Insert 8 misslyckades" << endl;
	if ( !WList::insert("pen","penna") )		cout << "Insert 9 misslyckades" << endl;
	if ( !WList::save("Dictionary.reg") )		cout << "Register dump failed"  << endl;
	facit("Insert 4 misslyckades");
	WList::showWlist();
	facit("Contents of Registry\n--------------------\nhouse :\thus\tkoja\tlogi\npen :\tpenna\nset :\tapparat\tst„lla\nweird :\tdum\tkonstig");
	if ( !WList::remove("pencil", "penna") )	cout << "Remove 1 misslyckades" << endl;
	if ( !WList::remove("pen", "gummi") )		cout << "Remove 2 misslyckades" << endl;
	if ( !WList::remove("pen", "penna") )		cout << "Remove 3 misslyckades" << endl;
	if ( !WList::remove("set", "st„lla") )		cout << "Remove 4 misslyckades" << endl;
	if ( !WList::remove("house", "logi") )		cout << "Remove 5 misslyckades" << endl;
	if ( !WList::remove("house", "penna") )	cout << "Remove 6 misslyckades" << endl;
	facit("Remove 1 misslyckades\nRemove 2 misslyckades\nRemove 6 misslyckades");
	WList::showWlist();
	facit("Contents of Registry\n--------------------\nhouse :\thus\tkoja\nset :\tapparat\nweird :\tdum\tkonstig");
	if ( !WList::load("Dictionary.reg") )           cout << "Laddning av register misslyckades"  << endl;
	WList::showWlist();
	facit("Contents of Registry\n--------------------\nhouse :\thus\tkoja\tlogi\npen :\tpenna\nset :\tapparat\tst„lla\nweird :\tdum\tkonstig");
	show_translation("house");
	show_translation("gadget");
	facit("™vers„ttning av \"house\" :\thus\tkoja\tlogi\nOrdet \"gadget\" finns ej registrerat!");
	WList::killWlist();
	for (int i=0 ; i<40 ; i++ ) cout <<'\n';
	cout << "*** D„rmed var testet klart! ***" << endl;
	return 0;
}
