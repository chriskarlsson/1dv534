/**********************************************************************/
// File:	TextTest.cpp
// Summary:	Test file for Lab 1, Step 3
//          The program will test functionality for class Texthandler, 
//			which is aimed to read a number of stories from a textfile,
//			in order to present them on the console screen.
// Version: Version 1.1 - 2013-05-02
// Author:	Christer Lundberg
// ------------------------------------------
// Log:		2003-09-25	Created the file. Christer
//			2013-05-02	Uppdate  Version 1.1 by Anne. 
//						Converted to English and VS 2012
//			2015-03-10	Revised by Anne. Converted to VS 2013
//			2018-04-05  Code tested for VS 2017, by Anne
/**********************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <cstring>
#include <iostream>
 using std::cin;
 using std::cout;
 using std::endl;
#include "Texthandler.h"


class App {
public:
	int run();
};


int App::run()
{
    // Enable memory leak flags
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int maxAntalPlatser = 20;
	int check[] = {7, 141, 246, 1157, 125, 84, 113, 9};		// För test-syfte

	try {
		Texthandler th("Historier.txt", maxAntalPlatser);	// Förutsätter textfilen i projektmappen
					 
		if (th.antalTexter() != check[0]) {
			cout << "Antal sparade historier „r " << th.antalTexter()
				  << " men borde vara " << check[0] << "!" << endl;
			cout << "Programmet avbryts!" << endl;
			return -1;
		}

		if (th.maxAntalTexter() != maxAntalPlatser) {
			cout << "Antal historier som ryms „r " << th.maxAntalTexter()
				  << " men borde vara " << maxAntalPlatser << "!" << endl;
			cout << "Programmet avbryts!" << endl;
			return -1;
		}

		int antal = th.antalTexter();
		int len;

		for (int i = 1; i <= antal; ++i) {
			len = (int)strlen(th.text(i));
			cout << "Text nr " << i << " inneh†ller " << len << " tecken.\n";

			if (len != check[i]) {
				cout << "FEL: L„ngden av texten borde ha varit " << check[i]
					  << "!" << endl;
			}
			cout << "----------------------------------------------------\n";
			cout << th.text(i) << endl << endl;
		}

		if (strcmp(th.text(7), "\nŽ™†„”\n\n") != 0)
			cout << "FEL:Din konvertering av bokst„ver fungerar inte!" << endl;
		if (th.text(0) != 0 || th.text(8)) 
			cout << "FEL:Du ska returnera NULL n„r man h„mtar en text som inte finns!" << endl;
		cout << "Tryck p† Enter f”r att avsluta programmet";

		char buf[20];
		cin.getline(buf, 20);
	}
	catch (...){
		// Fångar allt... Om något undantag kastas från TextHandler-klassen, fångas det här.
		cout << "An error occured during program execution. Program ended!" << endl;
		return 1;		
	}
	return 0;
}


int main()
{
	App app;
	return app.run();
}