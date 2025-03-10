#ifndef MIXEDFRACTION_H
#define MIXEDFRACTION_H

#include "Fraction.h"

class MixedFraction : public Fraction {
private:
    int whole;

public:
    // Constructors
    MixedFraction(int whole, int n, int d);  // Mixed fraction constructor
    MixedFraction(const Fraction& fraction);  // Convert a fraction to mixed form

    // Overloaded stream operator to print mixed fraction
    friend std::ostream& operator<<(std::ostream& os, const MixedFraction& mixedFraction);
};

#endif