#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>


int getValidInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        //Had to change this because if I would input a double it would count it as an int
        // Try to read an integer
        if (std::cin >> value) {
            // Check if there is any leftover input 
            if (std::cin.peek() == '.') {
                std::cout << "Invalid input. A double is not allowed.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            }
            else {
                return value;  // Successfully read an integer
            }
        }
        else {
            // Handle invalid input (non-integer)
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input.\n";
        }
    }
}

int main() {
    std::vector<int> reverse;

    std::cout << "Input 5 ints" << std::endl;
    int input;
    for (int i = 0; i < 5; i++) { //push back the vector
        input = getValidInt("");
        reverse.push_back(input);
    }

    for (auto i = reverse.rbegin(); i != reverse.rend(); i++) { //iterators to reverse the output
        std::cout << *i << " ";
    }
}