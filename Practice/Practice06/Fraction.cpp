#include "Fraction.h"
#include <algorithm>

Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int n, int d) : numerator(n), denominator(d) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator can not be 0");
    } 
    simplify();
}

int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}

void Fraction::setNumerator(int n) {
    numerator = n;
    simplify();
}

void Fraction::setDenominator(int d) {
    if (d == 0) {
        throw std::invalid_argument("Denominator can not be 0");
    }
    denominator = d;
    simplify();
}

void Fraction::simplify() {
    if (den == 0) throw std::invalid_argument("Denominator cannot be zero");
 
    // Compute GCD using Euclidean algorithm
    int a = num, b = den;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a; // GCD is stored in 'a' after loop exits
 
    // Simplify the fraction
    num /= gcd;
    den /= gcd;

    if(den < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    int numerator = lhs.num * rhs.den + rhs.num * lhs.den;
    int denominator = lhs.den * rhs.den;
    return Fraction(numerator, denominator);
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    int numerator = lhs.num * rhs.den - rhs.num * lhs.den;
    int denominator = lhs.den * rhs.den;
    return Fraction(numerator, denominator);
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    int numerator = lhs.num * rhs.num;
    int denominator = lhs.den * rhs.den;
    return Fraction(numerator, denominator);
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    if (rhs.num == 0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    int numerator = lhs.num * rhs.den;
    int denominator = lhs.den * rhs.num;
    return Fraction(numerator, denominator);
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    os << fraction.num << "/" << fraction.den;
    return os;
}