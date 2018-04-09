#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

class Measurements
{
public:
    virtual ~Measurements() = default;
    virtual void reset() = 0;
    virtual bool next(double & out) = 0;
};

#endif // MEASUREMENTS_H
