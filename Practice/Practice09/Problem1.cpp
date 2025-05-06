#include <iostream>
#include <string> 
#include <iomanip>
#include <limits>

int main() {
	float redPotion{0.0f};
	float bluePotion{0.0f};
	float* flask{nullptr};
	
	std::string choice;
	
	while(true) {
	    std::cout << "Which potion do you want to add to? (Red or Blue. Type Done to be finished.) ";
	    std::cin >> choice;
	    
	    if (choice == "Done" || choice == "done") {
	        break;
	    } else if (choice == "Red" || choice == "red") {
	        flask = &redPotion;
	    } else if (choice == "Blue" || choice == "blue") {
	        flask = &bluePotion;
	    } else {
	        std::cout << "Invalid choice. Please enter 'Red', 'Blue', or 'Done'. \n";
	        continue;
	    }
	    
	    float amount;
	    while (true) {
            std::cout << "Enter amount to add (in mL): ";
            std::cin >> amount;

            if (std::cin.fail()) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a numeric value.\n";
            } else if (amount < 0.0f) {
                std::cout << "Cannot add a negative amount. Try again.\n";
            } else {
                break; 
            }
        }
	    
	    *flask += amount;
	    
	    std::cout << std::fixed << std::setprecision(2);
	    std::cout << "Red Potion: " << redPotion << "ml\n";
	    std::cout << "Blue Potion: " << bluePotion << "ml\n";
	    
	}
	
	std::cout << "\nPotion brewing complete!\n";
	std::cout << "Final Red Potion: " << redPotion << "ml\n";
	std::cout << "Final Blue Potion: " << bluePotion << "ml\n";
	
	return 0;
}
