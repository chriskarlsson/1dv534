//-----------------------------------------------------------------------
// File:    main.cpp
// Summary: The main function of 1dv534_1_1_miserable
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2018-04-01 File created by Christoffer
//-----------------------------------------------------------------------

#include <miserable.h>
#include <file-measurements.h>

class Main {
public:
    Main() = default;
    ~Main() = default;
    int run(Miserable * miserable) {
        return miserable->run();
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
    FileMeasurements *fileMeasurements;

    try
    {
        fileMeasurements = new FileMeasurements();
    } catch(FileMeasurements::FileOpenFailed&) {
        return 1;
    }

    auto miserable = new Miserable(fileMeasurements);

    // Run application
    auto result = main.run(miserable);

    // Free memory
    delete miserable;

    // Output memory leaks to output window if any
#ifdef _WIN32
#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG
#endif // _WIN32

    return result;
}
