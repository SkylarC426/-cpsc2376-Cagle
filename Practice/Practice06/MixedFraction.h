#ifndef MIXEDFRACTION_H
#define MIXEDFRACTION_H

#include "Fraction.h"

class MixedFraction : public Fraction {
public:
    // Constructors
    MixedFraction(int whole, int n, int d);      // From mixed numbers
    MixedFraction(const Fraction& fraction);     // From existing fraction

    // Output override
    friend std::ostream& operator<<(std::ostream& os, const MixedFraction& mf);
};

#endif
