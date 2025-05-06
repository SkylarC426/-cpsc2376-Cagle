#include "MixedFraction.h"
#include <cmath>

// Constructor from whole, numerator, and denominator
MixedFraction::MixedFraction(int whole, int n, int d) 
    : Fraction(whole * d + (whole >= 0 ? n : -n), d) {
    // If whole < 0, make sure numerator is negative
    if (d == 0)
        throw std::invalid_argument("Denominator cannot be zero");
}

// Constructor from Fraction
MixedFraction::MixedFraction(const Fraction& fraction)
    : Fraction(fraction) {
    // Uses base class constructor
}

// Output override for MixedFraction
std::ostream& operator<<(std::ostream& os, const MixedFraction& mf) {
    int n = mf.getNumerator();
    int d = mf.getDenominator();

    if (std::abs(n) < d) {
        // Proper fraction
        os << n << "/" << d;
    } else {
        // Mixed fraction
        int whole = n / d;
        int remainder = std::abs(n % d);
        if (remainder == 0)
            os << whole;
        else
            os << whole << " " << remainder << "/" << d;
    }

    return os;
}
