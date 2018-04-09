#ifndef FILE_MEASUREMENTS_H
#define FILE_MEASUREMENTS_H

#include <measurements.h>
#include <fstream> //ifstream
#include <exception>

using std::ifstream;

class FileMeasurements : public Measurements
{
public:
    FileMeasurements();
    ~FileMeasurements();
    bool next(double & out);
    void reset();
    struct FileOpenFailed : public std::exception {
       const char * what () const throw () {
          return "Failed to open measurements file";
       }
    };
private:
    ifstream _fileStream;
};

#endif // FILE_MEASUREMENTS_H
