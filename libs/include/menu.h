#ifndef MENU_H
#define MENU_H

#include <iostream>

using std::cout;
using std::endl;
using std::istream;
using std::ostream;


class Menu {
public:
    Menu(const char * HEADER, const char** MENU_ITEMS, const int NUMBER_OF_ITEMS) :
         _HEADER(HEADER), _MENU_ITEMS(MENU_ITEMS), _NUMBER_OF_ITEMS(NUMBER_OF_ITEMS) {}
    ~Menu() {
        delete[] _MENU_ITEMS;
    }
    int getMenuSelection() const;
private:
    const char * _HEADER;
    const char ** _MENU_ITEMS;
    const int _NUMBER_OF_ITEMS;
};

#endif // MENU_H
