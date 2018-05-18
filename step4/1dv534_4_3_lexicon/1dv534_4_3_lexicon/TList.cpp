#include "List.h"

TList::TList(const char* tword, TList* tnext)
{
    _word = tword;
    _next = tnext;
}

TList::~TList()
{
//    free(_word);
    delete _next;
}