#ifndef MISERABLE_H
#define MISERABLE_H

#include <measurements.h>
#include <string> // string

using std::string;

class Miserable {
public:
    Miserable(Measurements * measurements) : _measurements(measurements) {}
    ~Miserable() {
        delete _measurements;
    }
    int run();
    void displayIntroduction() const;
    int getMenuSelection() const;
    string getMeasurements(const int MEASUREMENTS_PER_ROW, const int NUMBER_OF_MEASUREMENTS);
    string getMaxMin();
    string getAverage();
private:
    Measurements * _measurements;
};

#endif // MISERABLE_H
