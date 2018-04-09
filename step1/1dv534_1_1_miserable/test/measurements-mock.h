#ifndef FILE_MEASUREMENTS_H
#define FILE_MEASUREMENTS_H

#include <measurements.h>
#include <fstream> //ifstream
#include <exception>

class MeasurementsMock : public Measurements
{
public:
    MeasurementsMock(const double MEASUREMENTS[], const int SIZE) : _MEASUREMENTS(MEASUREMENTS), _SIZE(SIZE), _index(0) {}
    ~MeasurementsMock();
    bool next(double & out);
    void reset();
private:
    const double * _MEASUREMENTS;
    const int _SIZE;
    int _index;
};

#endif // FILE_MEASUREMENTS_H
