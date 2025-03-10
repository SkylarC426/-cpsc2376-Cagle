#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>

double getValidDouble(const std::string& prompt) { //makes sure the input value is an int
    double value;
    while(true) {
        std::cout << prompt;
        if(std::cin >> value) return value;
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter a valid number.\n";
    }
}



int main() {
    std::vector<double> maxMin;

    std::cout << "Input 5 numbers" << std::endl;
    double input;
    for (int i = 0; i < 5; i++) {
        input = getValidDouble("");
        maxMin.push_back(input);
    }

    auto max = std::max_element(maxMin.begin(), maxMin.end());
    if(max != maxMin.end()) {
        std::cout << "The largest element is: " << *max << std::endl;
    }

    auto min = std::min_element(maxMin.begin(), maxMin.end());
    if(min != maxMin.end()) {
        std::cout << "The smallest element is: " << *min << std::endl;
    }


}