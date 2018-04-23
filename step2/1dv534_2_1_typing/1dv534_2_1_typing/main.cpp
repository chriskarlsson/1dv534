//-----------------------------------------------------------------------
// File:    main.cpp
// Summary: The main function of 1dv534_1_1_miserable
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2018-04-01 File created by Christoffer
//-----------------------------------------------------------------------

#include "typing.h"

class Main {
public:
    Main() = default;
    ~Main() = default;
    int run(Typing & typing) {
        return typing.run();
    }
};

//-----------------------------------------------------------------------------
// int main()
//
// Summary: Presents statistics of the measurements in templog.txt.
// Returns: 0 when user stops execution. 1 if templog.txt cannot be opened.
//-----------------------------------------------------------------------------
int main()
{
    // Setup
    Main main;

    auto typing = new Typing();

    // Run application
    auto result = main.run(*typing);

    // Free memory
    delete typing;

    return result;
}
