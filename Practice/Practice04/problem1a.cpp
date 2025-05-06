#include <iostream>
#include <limits>

// Function to safely get an integer input
int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            // Not an int
            std::cin.clear(); // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter a valid integer.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard extra input
            return value;
        }
    }
}

// Temperature conversion function
double convertTemperature(double temp, char scale = 'F') {
    if (scale == 'F') {
        return ((temp * 9.0 / 5.0) + 32);
    } else if (scale == 'C') {
        return ((temp - 32) * 5.0 / 9.0);
    } else {
        return temp;
    }
}

int main() {
    int choice;
    double tempInput;
    double result;

    do {
        std::cout << "1. Convert Celsius to Fahrenheit" << std::endl;
        std::cout << "2. Convert Fahrenheit to Celsius" << std::endl;
        std::cout << "3. Exit" << std::endl;

        choice = getIntInput("Enter your choice as an int: ");

        switch (choice) {
            case 1:
                std::cout << "Enter the temperature in Celsius: ";
                std::cin >> tempInput;
                result = convertTemperature(tempInput, 'F');
                std::cout << "Converted: " << result << " degrees Fahrenheit\n";
                break;

            case 2:
                std::cout << "Enter the temperature in Fahrenheit: ";
                std::cin >> tempInput;
                result = convertTemperature(tempInput, 'C');
                std::cout << "Converted: " << result << " degrees Celsius\n";
                break;

            case 3:
                std::cout << "Exiting the program.\n";
                break;

            default:
                std::cout << "Invalid choice, please try again.\n";
        }

    } while (choice != 3);

    return 0;
}
