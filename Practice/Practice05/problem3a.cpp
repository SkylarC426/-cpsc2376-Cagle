#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>
#include <numeric>

//comment and layout better
int getValidInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;

        // Try to read an integer
        if (std::cin >> value) {
            // Check if there is any leftover input (e.g., a double or extra characters)
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
    std::vector<int> lambdaList;

    std::cout << "Input 5 ints" << std::endl;
    int input;
    for (int i = 0; i < 5; i++) {
        input = getValidInt("");
        lambdaList.push_back(input);
    }

    std::cout << "All values squared: ";
    std::for_each(lambdaList.begin(), lambdaList.end(), [](int num) {
        std::cout << num * num << " ";
    });
    std::cout << std::endl;

    int sum = std::accumulate(lambdaList.begin(), lambdaList.end(), 0, [](int sum, int num){
        return sum + (num*num);
    });
    std::cout << "Sum of the squared ints: " << sum << std::endl;

    return 0;

}