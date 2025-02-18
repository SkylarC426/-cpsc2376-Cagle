#include <iostream>
#include <vector>
#include <algorithm> // For std::find

// Adds an item to the vector
void addItem(std::vector<int>& vec) {
    int num;
    std::cout << "Input an integer to add: ";
    std::cin >> num;
    vec.push_back(num); // Add the input number to the vector
}

// Removes an item from the vector
void minusItem(std::vector<int>& vec) {
    int num;
    std::cout << "Enter a number to remove: ";
    std::cin >> num;

    // Find the element in the vector
    auto it = std::find(vec.begin(), vec.end(), num);
    if (it != vec.end()) {
        vec.erase(it); // Remove the element if found
        std::cout << "Number removed." << std::endl;
    } else {
        std::cout << "The number entered could not be found in the vector." << std::endl;
    }
}

// Doubles the value of all elements in the vector
void doubleVector(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        vec.at(i) *= 2; // Multiply each element by 2
    }
    std::cout << "Elements have been doubled! *smile*" << std::endl;
}

// Halves the value of all elements in the vector
void halfVector(std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        vec.at(i) /= 2; // Divide each element by 2
    }
    std::cout << "Elements have been halved!" << std::endl;
}

// Prints all elements in the vector
void printVector(const std::vector<int>& vec) {
    if (vec.empty()) {
        std::cout << "There are no elements in this vector." << std::endl;
        return;
    }
    
    std::cout << "All elements: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec.at(i) << " "; // Display each element
    }
    std::cout << std::endl;
}

// Computes and prints the sum of all elements in the vector
void findSum(const std::vector<int>& vec) {
    int sum = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        sum += vec.at(i); // Accumulate the sum
    }
    std::cout << "Sum of all the elements: " << sum << std::endl;
}

// Prints all elements that are multiples of the given number
void printMultiples(const std::vector<int>& vec) {
    int factor;
    std::cout << "Enter a number to find multiples: ";
    std::cin >> factor;

    std::cout << "Multiples of " << factor << ": ";
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec.at(i) % factor == 0) { // Check if the element is a multiple
            std::cout << vec.at(i) << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec; // Vector to store integer values
    int choice; // Variable to store user choice
    std::cout << "Please use an int for all inputs." <<std::endl;

    do { // Menu loop
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Print the vector" << std::endl;
        std::cout << "2. Add item to vector" << std::endl;
        std::cout << "3. Take an item out of the vector" << std::endl;
        std::cout << "4. Double the values in the vector" << std::endl;
        std::cout << "5. Halve the values in the vector" << std::endl;
        std::cout << "6. Find the sum of all the numbers in the vector" << std::endl;
        std::cout << "7. Print all elements of the vector that are multiples of a given number" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Switch statement to execute the corresponding function based on user choice
        switch (choice) {
            case 1: printVector(vec); break;
            case 2: addItem(vec); break;
            case 3: minusItem(vec); break;
            case 4: doubleVector(vec); break;
            case 5: halfVector(vec); break;
            case 6: findSum(vec); break;
            case 7: printMultiples(vec); break;
            case 8: std::cout << "Exiting program." << std::endl; break;
            default: std::cout << "Invalid input. Please try again." << std::endl;
        }
    } while (choice != 8); // Loop continues until user chooses to exit

    return 0;
}