#include <iostream>
#include <string> 
#include <iomanip>
#include <limits>

int main() {
	float redPotion{0.0f};    // Amount of red potion in mL
	float bluePotion{0.0f};   // Amount of blue potion in mL
	float* flask{nullptr};    // Pointer to the selected potion
	
	std::string choice;
	
	while(true) { //loop that continues until done
	    std::cout << "Which potion do you want to add to, Red or Blue? Type Done to be finished. ";
	    std::cin >> choice;
	    
		//if done, finish code
	    if (choice == "Done" || choice == "done") {
	        break;
	    } 
		//point to red potion
		else if (choice == "Red" || choice == "red") {
	        flask = &redPotion;
	    } 
		//point to blue potion
		else if (choice == "Blue" || choice == "blue") {
	        flask = &bluePotion;
	    }
		//invalid option
		else {
	        std::cout << "Invalid choice. Please enter Red, Blue, or Done. \n";
	        continue;
	    }
	    
	    float amount; //amount of mL to add
	    while (true) {
            std::cout << "Enter amount to add (in mL): ";
            std::cin >> amount;

			//if entering not a number
            if (std::cin.fail()) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter number. \n";
            }
			//if adding a negative amount
			else if (amount < 0.0f) {
                std::cout << "Cannot add a negative amount. Try again.\n";
            } 
			// if valid
			else {
                break; 
            }
        }
	    
		//adds amount if clear
	    *flask += amount;
	    
		//displays updated volumes
	    std::cout << std::fixed << std::setprecision(2);
	    std::cout << "Red Potion: " << redPotion << "ml\n";
	    std::cout << "Blue Potion: " << bluePotion << "ml\n";
	    
	}
	
	//final values
	std::cout << "\nPotion brewing complete!\n";
	std::cout << "Final Red Potion: " << redPotion << "ml\n";
	std::cout << "Final Blue Potion: " << bluePotion << "ml\n";
	
	return 0;
}
