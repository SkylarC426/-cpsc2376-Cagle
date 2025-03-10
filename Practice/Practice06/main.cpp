#include <iostream>
#include "Fraction.h"
#include "MixedFraction.h"

void menu() {
    std::cout << "Current Fraction: ";

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

int main() {
    Fraction currentFraction;
    int choice; 

    do {
        menu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1: {
            int numerator, denominator;
            std::cout << "Enter the numerator and denominator: ";
            std::cin >> numerator >> denominator;
            
            try
            {
                currentFraction = Fraction(numerator, denominator);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
            break;
        }

        case 2: {
            int numerator, denominator;
            std::cout << "Enter the numerator and denominator for addition: ";
            std::cin >> numerator >> denominator;

            try
            {
                Fraction temp(numerator, denominator);
                currentFraction = currentFraction + temp;
                std::cout << "The result is: " << currentFraction << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        }
            
        case 3: {
            int numerator, denominator;
            std::cout << "Enter the numerator and denominator for subtraction: ";
            std::cin >> numerator >> denominator;
            
            try
            {
                Fraction temp(numerator, denominator);
                currentFraction = currentFraction - temp;
                std::cout << "The result is: " << currentFraction << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }
        
        case 4: {
            int numerator, denominator;
            std::cout << "Enter the numerator and denominator for multiplication: ";
            std::cin >> numerator >> denominator;
            
            try
            {
                Fraction temp(numerator, denominator);
                currentFraction = currentFraction * temp;
                std::cout << "The result is: " << currentFraction << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }

        case 5: {
            int numerator, denominator;
            std::cout << "Enter the numerator and denominator for division: ";
            std::cin >> numerator >> denominator;
            
            try
            {
                Fraction temp(numerator, denominator);
                currentFraction = currentFraction / temp;
                std::cout << "The result is: " << currentFraction << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            break;
        }
        
        case 6: {
            MixedFraction mixed(currentFraction);
            std::cout << "Mixed Fraction: " << mixed << std::endl;
            break;
        }

        case 7: {
            currentFraction = Fraction();
            std::cout << "Fraction reset." << std::endl;
            break;
        }

        case 8: 
            std::cout << "Exiting program." << std::endl;
            break;
        
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while(choice != 8);
    return 0;
}
