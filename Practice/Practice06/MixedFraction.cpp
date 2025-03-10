#include "MixedFraction.h"
#include <iostream>

MixedFraction::MixedFraction(int whole, int n, int d) : Fraction(n,d), whole(whole) {}

MixedFraction::MixedFraction(const Fraction& fraction) {
    whole = fraction.getNumerator() / fraction.getDenominator();
    int numerator = fraction.getNumerator() % fraction.getDenominator();
    int denominator = fraction.getDenominator();
    *this = Fraction(numerator, denominator);
}

std::ostream& operator<<(std::ostream& os, const MixedFraction& mixedFraction) {
    if (mixedFraction.whole != 0) {
        os << mixedFraction.whole;
        if (mixedFraction.getNumerator() != 0) {
            os << " " << mixedFraction.getNumerator() << "/" << mixedFraction.getDenominator();
        }
    } else {
        os << mixedFraction.getNumerator() << "/" << mixedFraction.getDenominator();
    }
    return os;
}