//-----------------------------------------------------------------------------
// File:    measurements-mock.cpp
// Summary: Mock class used to test miserable.cpp
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------------
// Log:   2018-04-01 File created by Christoffer
//
//-----------------------------------------------------------------------------

// Preprocessor directives
#include <measurements.h>
#include <measurements-mock.h>

//-----------------------------------------------------------------------------
// ~MeasurementsMock()
//
// Summary: Deletes member variable _MEASUREMENTS
// Returns: -
//-----------------------------------------------------------------------------
MeasurementsMock::~MeasurementsMock()
{
    delete _MEASUREMENTS;
}

//-----------------------------------------------------------------------------
// void reset()
//
// Summary: Restores the read position.
// Returns: -
//-----------------------------------------------------------------------------
void MeasurementsMock::reset()
{
    _index = 0;
}

//-----------------------------------------------------------------------------
// bool next(double & out)
//
// Summary: Reads the next measurements value.
// Returns: True if read was successful.
//-----------------------------------------------------------------------------
bool MeasurementsMock::next(double & out)
{
    if (_index < _SIZE)
    {
        out = _MEASUREMENTS[_index++];

        return true;
    }
    else
    {
        return false;
    }
}
