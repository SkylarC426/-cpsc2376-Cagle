#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <limits>

const std::string BALANCE_FILE = "account_balance.txt"; //creates the file

int getValidInt(const std::string& prompt) { //makes sure that the input value is an int
    int value;
    while(true) {
        std::cout << prompt;
        if(std::cin >> value) return value;
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Please enter a valid number.\n";
    }
}

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


double readBalanceFromFile() { //reads the file and puts 100 bucks in it if the file is fresh
    std::ifstream file(BALANCE_FILE);
    double balance = 100.00;
    if (file) { //keeps money consistent across multiple opens
        file >> balance;
        std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << "\n";
    }
    else { //if file is new
        std::ofstream newFile(BALANCE_FILE);
        newFile << balance;
        std::cout << "Initializing account with $100.00...\n";
    }
    return balance;
}

void writeBalanceToFile(double balance) { //code to write and update the file
    std::ofstream file(BALANCE_FILE); //opens
    if (file) {
        file << balance; //updates balance
    }
    else { //if unable to open
        std::cerr << "Error: Unable to update balance file." << std::endl;
        exit(1);
    }
}

void checkBalance(double balance) { //checks current balance
    std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << balance << "\n";
}

double deposit(double& balance) { //function to depo money into account
    double amount = getValidDouble("Enter deposit amount: "); //calling the function
    if (amount <= 0) { //makes sure amount is positive
        std::cout << "Error: Deposit amount must be positive.\n";
        return balance;
    }
    balance += amount; //adds money to account
    writeBalanceToFile(balance);//and saves it
    std::cout << "Deposit successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << "\n";
    return balance;
}

double withdraw(double& balance) { //func to take money out of account
    double amount = getValidDouble("Enter withdraw amount: "); //calling the new function
    if (amount <= 0) { //makes sure amount is positive
        std::cout << "Error: Withdrawal amount must be positive.\n";
        return balance;
    }
    if (amount > balance) { //makes sure you can't take out more than you have
        std::cout << "Error: Insufficient funds. Your balance is $" << std::fixed << std::setprecision(2) << balance << "\n";
        return balance;
    }
    balance -= amount;//takes money out
    writeBalanceToFile(balance);//and saves it
    std::cout << "Withdrawal successful. Your new balance is: $" << std::fixed << std::setprecision(2) << balance << "\n";
    return balance;
}

double calculateInterest(double initialAmount, double rate, int time) { //formula for a later function
    return initialAmount * rate * time;
}

double interest(double balance) { //function to calculate potential interest
    int months; //setting up variables to call with the function
    double rate = 0.01; //not the best rates... consider swapping banks
    double intrestCalculator; 

    months = getValidInt("Enter how many months you would like to keep your money with us: "); //calling the new function

    intrestCalculator = calculateInterest(balance, rate, months); //calling the prior function
    std::cout << "You would earn $" << std::fixed << std::setprecision(2) << intrestCalculator << std::endl; //prints out potential interest
    return 0;
}


int main() {

    int choice;
    std::cout << "Welcome to Your Bank Account!\n";
    double balance = readBalanceFromFile();


    do { //menu do while loop
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Check Balance" << std::endl;
        std::cout << "2. Deposit Money" << std::endl;
        std::cout << "3. Withdraw Money" << std::endl;
        std::cout << "4. Check Interest" << std::endl;
        std::cout << "5. Exit" << std::endl;
        
         choice = getValidInt("Enter your choice: ");

        switch (choice) { //choice for the menu
        case 1: checkBalance(balance); break;
        case 2: deposit(balance); break;
        case 3: withdraw(balance); break;
        case 4: interest(balance); break;
        case 5: std::cout << "Exiting program." << std::endl; break;
        default: std::cout << "Invalid input. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}