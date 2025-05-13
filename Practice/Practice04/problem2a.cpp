#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> // for std::setprecision
#include <limits>  // for std::numeric_limits

//template for all the cases
template <typename T>
T calculate(T a, T b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
        default: return 0;
    }
}

//detects decimal
bool isDouble(const std::string& s) {
    return s.find('.') != std::string::npos;
}

//makes sure there are no stray characters
bool isValidNumber(const std::string& s) {
    std::istringstream iss(s);
    double temp;
    char extra;
    return (iss >> temp) && !(iss >> extra); // valid number and no trailing characters
}

int main() {
    std::string input1;
    std::string input2;
    char op;

    //inputs and validates first number
    while (true) {
        std::cout << "Enter first number: ";
        std::cin >> input1;
        if (isValidNumber(input1)) break;
        std::cout << "Invalid input. Please enter a valid number.\n";
    }

    //inputs and validates second number
    while (true) {
        std::cout << "Enter second number: ";
        std::cin >> input2;
        if (isValidNumber(input2)) break;
        std::cout << "Invalid input. Please enter a valid number.\n";
    }

    //inputs and validates operator
    while (true) {
        std::cout << "Enter operation (+, -, *, /): ";
        std::cin >> op;
        if (op == '+' || op == '-' || op == '*' || op == '/') break;
        std::cout << "Invalid operation. Please enter one of +, -, *, /.\n";
    }

    //determines if its an int or double
    if (isDouble(input1) || isDouble(input2)) {
        double a;
        double b;
        std::stringstream(input1) >> a;
        std::stringstream(input2) >> b;

        //checks for zeros 
        if (op == '/' && b == 0.0) {
            std::cout << "Error: Cannot divide by zero.\n";
            return 1;
        }

        //perform calcs with set decimal place for tidyness
        double result = calculate<double>(a, b, op);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Result: " << result << std::endl;
    } else {
        //convers inputs to int
        int a;
        int b;
        std::stringstream(input1) >> a;
        std::stringstream(input2) >> b;

        //checks for dividing zeros
        if (op == '/' && b == 0) {
            std::cout << "Error: Cannot divide by zero.\n";
            return 1;
        }

        //preforms calcs
        int result = calculate<int>(a, b, op);
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}
