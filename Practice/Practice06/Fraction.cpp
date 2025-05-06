#include "Fraction.h"

// Default constructor: 0/1
Fraction::Fraction() : num(0), den(1) {}

// Parameterized constructor
Fraction::Fraction(int n, int d) : num(n), den(d) {
    if (d == 0)
        throw std::invalid_argument("Denominator cannot be zero");
    simplify();
}

// Getters
int Fraction::getNumerator() const {
    return num;
}

int Fraction::getDenominator() const {
    return den;
}

// Setters
void Fraction::setNumerator(int n) {
    num = n;
    simplify();
}

void Fraction::setDenominator(int d) {
    if (d == 0)
        throw std::invalid_argument("Denominator cannot be zero");
    den = d;
    simplify();
}

// Simplify using Euclidean algorithm
void Fraction::simplify() {
    if (den == 0)
        throw std::invalid_argument("Denominator cannot be zero");

    int a = abs(num);
    int b = abs(den);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    int gcd = a;
    num /= gcd;
    den /= gcd;

    // Ensure denominator is positive
    if (den < 0) {
        num = -num;
        den = -den;
    }
}

// Arithmetic operators
Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    int n = lhs.num * rhs.den + rhs.num * lhs.den;
    int d = lhs.den * rhs.den;
    return Fraction(n, d);
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    int n = lhs.num * rhs.den - rhs.num * lhs.den;
    int d = lhs.den * rhs.den;
    return Fraction(n, d);
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    int n = lhs.num * rhs.num;
    int d = lhs.den * rhs.den;
    return Fraction(n, d);
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    if (rhs.num == 0)
        throw std::invalid_argument("Division by zero");
    int n = lhs.num * rhs.den;
    int d = lhs.den * rhs.num;
    return Fraction(n, d);
}

// Output operator
std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.num << "/" << f.den;
    return os;
}
