#ifndef LIST_H
#define LIST_H

#include <sstream>
using std::stringstream;

class TList {
public:
    TList(const char* tword, TList* tnext);
    virtual ~TList();
    const char* getWord() const { return _word; }
    TList* getSuccessor() const { return _next; }
    void setSuccessor(TList* tnext) { _next = tnext; }
private:
    const char* _word;
    TList* _next;
};

class WList {
public:
    WList(char* wword, char* tword, WList* wnext);
    ~WList();
    bool insertTword(char* tword);
    const char* getWord() const { return _word; }
    WList* getSuccessor() const { return _next; }
    static WList* insert(char* wword, char* tword);
    static bool remove(char* wword, char* tword);
    static void killWlist();
    static void showWlist();
    static const TList* translate(char* wword);
    static bool save(char* filename);
    static bool load(char* filename);
private:
    static bool removeTList(WList* wList, const char* tword);
    static WList* removeEmptyWList(WList* wList);
    template <typename T>
    static T * getPreviousInList(const char* word, T* currentList);
    template <typename T>
    static T* getMatch(const char* word, T* currentList);
    static WList* _whead;
    static stringstream asStringStream();
    stringstream toStringStream() const;
    const char* _word;
    TList* _thead;
    WList* _next;
    static const int _MAX_WORD_LENGTH = 300;
    static const int _MAX_ROW_LENGTH = _MAX_WORD_LENGTH * 100;
};
#endif 