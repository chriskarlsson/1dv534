#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

class Texthandler
{
public:
    Texthandler(char const * FILENAME, int NUMBER_OF_TEXTS);
    inline ~Texthandler();
    inline int antalTexter();
    inline int maxAntalTexter();
    inline const char * text(const int INDEX);
private:
    char** _texts;
    int _numberOfTexts = 0;
    int _maxNumberOfTexts = 0;
    const int _TEXT_MAX_SIZE = 10000;
};

//-----------------------------------------------------------------------------
// ~Texthandler()
//
// Summary: Destructor.
// Returns: -
//-----------------------------------------------------------------------------
inline Texthandler::~Texthandler()
{
    for (int i = 0; i < _numberOfTexts; i++)
    {
        delete[] _texts[i];
    }

    delete[] _texts;
};

//-----------------------------------------------------------------------------
// int antalTexter()
//
// Summary: Keeps track of how many texts has been read from file.
// Returns: The number of stored texts.
//-----------------------------------------------------------------------------
inline int Texthandler::antalTexter()
{
    return _numberOfTexts;
};

//-----------------------------------------------------------------------------
// int maxAntalTexter()
//
// Summary: Store the maximum number of texts that are read from file.
// Returns: The maximum number of stored texts.
//-----------------------------------------------------------------------------
inline int Texthandler::maxAntalTexter()
{
    return _maxNumberOfTexts;
};

//-----------------------------------------------------------------------------
// const char * text(const int INDEX)
//
// Summary: Texts kept in memory. Indexed start at 1.
// Returns: The text.
//-----------------------------------------------------------------------------
inline const char * Texthandler::text(const int INDEX)
{
    return INDEX < 1 || INDEX > _numberOfTexts ? nullptr : _texts[INDEX - 1];
};

#endif /* TEXT_HANDLER_H */