#include "List.h"

#include <cstring>
using std::strcmp;
using std::strlen;
using std::strncpy;
using std::strtok;
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;

WList* WList::_whead = nullptr;

WList::WList(char* wword, char* tword, WList* wnext)
{
    _word = wword;
    _thead = new TList(tword, nullptr);
    _next = wnext;
}

WList::~WList()
{
//    delete _word;
    delete _thead;
    delete _next;
}

bool WList::insertTword(char* tword)
{
    auto previous = getPreviousInList(tword, _thead);

    if (previous == nullptr)
    {
        _thead = new TList(tword, _thead);
        return true;
    }
    else if (strcmp(tword, previous->getWord()) == 0)
    {
        return false;
    }
    else
    {
        previous->setSuccessor(new TList(tword, previous->getSuccessor()));
        return true;
    }
}

WList* WList::insert(char* wword, char* tword)
{
    auto previous = getPreviousInList(wword, _whead);

    if (previous == nullptr)
    {
        _whead = new WList(wword, tword, _whead);
        return _whead;
    }
    else if (strcmp(wword, previous->getWord()) == 0)
    {
        if (previous->insertTword(tword))
        {
            return previous;
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        previous->_next = new WList(wword, tword, previous->_next);
        return previous->_next;
    }
}

template <typename T>
T* WList::getPreviousInList(const char* word, T* currentList)
{
    if (currentList == nullptr || strcmp(word, currentList->getWord()) < 0)
    {
        return nullptr;
    }
    else if (currentList->getSuccessor() == nullptr || strcmp(word, currentList->getSuccessor()->getWord()) < 0)
    {
        return currentList;
    }
    else
    {
        return getPreviousInList(word, currentList->getSuccessor());
    }
}

template <typename T>
T* WList::getMatch(const char* word, T* currentList)
{
    if (currentList == nullptr || strcmp(word, currentList->getWord()) > 0)
    {
        return nullptr;
    }
    else if (strcmp(word, currentList->getWord()) == 0)
    {
        return currentList;
    }
    else
    {
        return getMatch(word, currentList->getSuccessor());
    }
}

bool WList::remove(char* wword, char* tword)
{
    if (_whead == nullptr)
    {
        return false;
    }

    auto previousWList = getPreviousInList(wword, _whead);

    if (previousWList == nullptr)
    {
        if (strcmp(wword, _whead->getWord()) == 0)
        {
            auto result = removeTList(_whead, tword);

            _whead = removeEmptyWList(_whead);

            return result;
        }
        else
        {
            return false;
        }
    }
    else if (previousWList->getSuccessor() != nullptr && strcmp(wword, previousWList->getSuccessor()->getWord()) == 0)
    {
        auto result = removeTList(previousWList->getSuccessor(), tword);

        previousWList->_next = removeEmptyWList(previousWList->getSuccessor());
    }
    else
    {
        return false;
    }
}

bool WList::removeTList(WList* wWList, const char* tword)
{
    auto previousTList = getPreviousInList(tword, wWList->_thead);

    if (previousTList == nullptr)
    {
        if (strcmp(tword, wWList->_thead->getWord()) != 0)
        {
            return false;
        }

        if (wWList->_thead->getSuccessor() == nullptr)
        {
            delete wWList->_thead;
            wWList->_thead = nullptr;
            return true;
        }
        else
        {
            auto tempPtr = wWList->_thead;
            wWList->_thead = tempPtr->getSuccessor();
            delete tempPtr;
            return true;
        }
    }
    else if (previousTList->getSuccessor() != nullptr && strcmp(tword, previousTList->getSuccessor()->getWord()) == 0)
    {
        auto tempPtr = previousTList->getSuccessor();
        previousTList->setSuccessor(tempPtr->getSuccessor());
        delete tempPtr;
        return true;
    }
    else
    {
        return false;
    }
}

WList* WList::removeEmptyWList(WList* wList)
{
    if (wList->_thead == nullptr)
    {
        auto tempPtr = wList;
        wList = wList->getSuccessor();
        delete wList;
    }

    return wList;
}

void WList::killWlist()
{
    delete _whead;
    _whead = nullptr;
}

void WList::showWlist()
{
    cout << "Contents of Registry" << endl
         << "--------------------" << endl
         << asStringStream().str() << endl;
}

stringstream WList::asStringStream()
{
    stringstream string;

    if (_whead != nullptr)
    {
        auto wList = _whead;

        do
        {
            string << wList->toStringStream().str() << endl;
            wList = wList->getSuccessor();
        } while (wList != nullptr);
    }

    return string;
}

stringstream WList::toStringStream() const
{
    stringstream string;
    
    string << _word << " :";

    auto tList = _thead;

    do
    {
        string << "\t" << tList->getWord();
        tList = tList->getSuccessor();
    } while (tList != nullptr);

    return string;
}

const TList* WList::translate(char* wword)
{
    auto wList = getMatch(wword, _whead);

    return wList == nullptr ? nullptr : wList->_thead;
}

bool WList::save(char* filename)
{
    ofstream fileStream(filename);

    if (!fileStream.is_open())
    {
        cout << "Failed to create the dictionary file." << endl
             << "Please make sure that the user has write permissions in the directory."
             << endl;
        return false;
    }

    fileStream << asStringStream().str();

    fileStream.close();

    return true;
}

bool WList::load(char* filename)
{
    killWlist();

    ifstream fileStream(filename);

    if (!fileStream.is_open())
    {
        cout << "Failed to open the measeurements file." << endl
             << "Please make sure that " << filename << " is present in "
             << "the directory and the user has read permissions."
             << endl;
        return false;
    }

    //char wordBuffer[_MAX_WORD_LENGTH] = {};
    //char myBuffer[_MAX_WORD_LENGTH] = {};
    //WList* wListPtr;

    //while (fileStream >> wordBuffer)
    //{
    char rowBuffer[_MAX_ROW_LENGTH] = {};
    WList* wListPtr;

    while (fileStream.getline(rowBuffer, _MAX_ROW_LENGTH))
    {
        char wordBuffer[_MAX_WORD_LENGTH] = {};

        char * delimiter = " :\t";
        char *start, *stop;

        /* get the first word */
        start = rowBuffer;
        stop = strtok(rowBuffer, delimiter);
        stop = strtok(nullptr, delimiter);

        auto length = stop - start - strlen(delimiter);

        auto wWord = new char[length + 1]{ 0 };
        strncpy(wWord, start, length);

        delimiter = "\t";
        start = stop;
        stop = strtok(nullptr, delimiter);

        length = stop - start - strlen(delimiter);

        auto tWord = new char[length + 1]{ 0 };
        strncpy(tWord, start, length);

        wListPtr = insert(wWord, tWord);

        /* walk through other tokens */
        while (true) {
            start = stop;
            stop = strtok(nullptr, delimiter);

            if (stop == nullptr)
            {
                break;
            }

            length = stop - start - strlen(delimiter);

            auto tWord = new char[length + 1]{ 0 };
            strncpy(tWord, start, length);

            wListPtr->insertTword(tWord);
        }

        length = strlen(start);

        tWord = new char[length + 1]{ 0 };
        strncpy(tWord, start, length);

        wListPtr->insertTword(tWord);
    }

    fileStream.close();

    return true;
}
