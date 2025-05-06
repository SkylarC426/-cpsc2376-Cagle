#include <iostream>
#include "Fraction.h"
#include "MixedFraction.h"
#include "Fraction.cpp"
#include "MixedFraction.cpp"

void menu(const Fraction& current) {
    std::cout << "\nCurrent Fraction: " << current << "\n";
    std::cout << "Options:\n"
              << "1. Enter a fraction manually\n"
              << "2. Add a fraction\n"
              << "3. Subtract a fraction\n"
              << "4. Multiply by a fraction\n"
              << "5. Divide by a fraction\n"
              << "6. Display as Mixed Fraction\n"
              << "7. Clear Fraction\n"
              << "8. Exit\n";
}

Fraction inputFraction() {
    int n, d;
    std::cout << "Enter numerator and denominator: ";
    std::cin >> n >> d;
    if (d == 0) throw std::invalid_argument("Denominator cannot be zero");
    return Fraction(n, d);
}

int main() {
    Fraction current;
    int choice;

    do {
        menu(current);
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        try {
            switch (choice) {
                case 1:
                    current = inputFraction();
                    break;
                case 2:
                    current = current + inputFraction();
                    break;
                case 3:
                    current = current - inputFraction();
                    break;
                case 4:
                    current = current * inputFraction();
                    break;
                case 5:
                    current = current / inputFraction();
                    break;
                case 6: {
                    MixedFraction mf(current);
                    std::cout << "As Mixed Fraction: " << mf << "\n";
                    break;
                }
                case 7:
                    current = Fraction(); // reset to 0/1
                    break;
                case 8:
                    std::cout << "Exiting...\n";
                    break;
                default:
                    std::cout << "Invalid option. Try again.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }

    } while (choice != 8);

    return 0;
}
