//-----------------------------------------------------------------------------
// File:    measurements.cpp
// Summary: Presents statistics of the measurements in templog.txt
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------------
// Log:   2018-04-01 File created by Christoffer
//
//-----------------------------------------------------------------------------

// Preprocessor directives
#include <iostream> // cin and cout
#include <measurements.h>
#include <file-measurements.h>

// Usings
using std::cout;
using std::endl;
using std::ios;

//-----------------------------------------------------------------------------
// FileMeasurements()
//
// Summary: Constructor.
// Returns: -
//-----------------------------------------------------------------------------
FileMeasurements::FileMeasurements()
{
   const auto FILE_NAME = "templog.txt";
   _fileStream.open(FILE_NAME, ios::in);

   if (!_fileStream.is_open())
   {
       cout << "Failed to open the measeurements file." << endl
            << "Please make sure that " << FILE_NAME << " is present in "
            << "the directory and the user has read permissions."
            << endl;
       throw FileOpenFailed();
   }
}

//-----------------------------------------------------------------------------
// ~MeasurementsMock()0 when user stops execution.
//
// Summary: Close file stream member variable _fileStream.
// Returns: -
//-----------------------------------------------------------------------------
FileMeasurements::~FileMeasurements()
{
    _fileStream.close();
}

//-----------------------------------------------------------------------------
// void reset()
//
// Summary: Restores the read position.
// Returns: -
//-----------------------------------------------------------------------------
void FileMeasurements::reset()
{
    _fileStream.clear();
    _fileStream.seekg(0);
}

//-----------------------------------------------------------------------------
// bool next(double & out)
//
// Summary: Reads the next measurements value.
// Returns: True if read was successful.
//-----------------------------------------------------------------------------
bool FileMeasurements::next(double & out)
{
    if (_fileStream >> out)
    {
        return true;
    }
    else
    {
        return false;
    }
}
