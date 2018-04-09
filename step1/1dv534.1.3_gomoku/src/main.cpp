//-----------------------------------------------------------------------
// File:    main.cpp
// Summary: The main function of 1dv534_1_3_gomoku
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2018-04-01 File created by Christoffer
//-----------------------------------------------------------------------

#include <gomoku.h>

class Main {
public:
    Main() = default;
    ~Main() = default;
    int run(Gomoku * gomoku) {
        return gomoku->run();
    }
};

//-----------------------------------------------------------------------------
// int main()
//
// Summary: Runs gomoku.
// Returns: 0 when user stops execution. 1 if templog.txt cannot be opened.
//-----------------------------------------------------------------------------
int main()
{
    // Check for memory leaks in Windows.
    // Run application with Valgrind if using Linux.
#ifdef _WIN32
#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <cstdlib>
    #include <crtdbg.h>
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
#endif // _WIN32

    // Setup
    Main main;
    auto gomoku = new Gomoku();

    // Run application
    auto result = main.run(gomoku);

    // Free memory
    delete gomoku;

    // Output memory leaks to output window if any
#ifdef _WIN32
#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG
#endif // _WIN32

    return result;
}
