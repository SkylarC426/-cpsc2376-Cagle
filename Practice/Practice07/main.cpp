#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

//base class for employee 
class Employee {
    //employee's name and id
    protected:
    std::string name;
    int id;
    
    public:
    
    //constructor for name and ID
    Employee(std::string name, int id) : name(std::move(name)), id(id) {} virtual ~Employee() = default;


    virtual double calculateSalary() const = 0;
    
    //displays id and name
    virtual void displayInfo() const {
        std::cout << "ID: " << id << ", Name: " << name;
    }
};

//derived class from employee for salaried employees
class SalariedEmployee : public Employee {
    private:
    //fixed monthly salary
    double monthlySalary;
    
    public:
    //constructor forwards name and id and sets monethly salary
    SalariedEmployee(std::string name, int id, double monthlySalary) : Employee(std::move(name), id), monthlySalary(monthlySalary) {}
    
    //overrides fixed monthly salary
    double calculateSalary() const override {
        return monthlySalary;
    }
    
    //displays all info for salaried employees
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Salaried, Monthly Salary: $" << std::fixed << std::setprecision(2) << calculateSalary() << "\n"; 
    }
    
};

//derived class from employee for the comission employee
class CommissionEmployee : public Employee {
    private:

    //base salary, total sales, comission rate
    double baseSalary;
    double salesAmount;
    double commissionRate;
    
    public:
    //constructor initializes base, sales, and rate
    CommissionEmployee(std::string name, int id, double baseSalary, double salesAmount, double commissionRate) : Employee(std::move(name), id), baseSalary(baseSalary), salesAmount(salesAmount), commissionRate(commissionRate) {}
    
    //calcualtes the salary
    double calculateSalary() const override {
        return baseSalary + (salesAmount * commissionRate);
    }
    
    //displays all the info for the comission employee
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Commission, Base Salary: $" << std::fixed << std::setprecision(2) << baseSalary << ", Sales: " << salesAmount << ", Commission Rate: " << (commissionRate * 100) << "%, Salary: $" << calculateSalary() << "\n";
    }
};

class HourlyEmployee : public Employee {
    private:
    //hourly rate and hours worked
    double hourlyRate;
    int hoursWorked;
    
    public:
    //constructor for rate and hours
    HourlyEmployee(std::string name, int id, double hourlyRate, int hoursWorked) : Employee(std::move(name), id), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}
    
    //calcs salary
    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
    
    //displays all info for the hourly employee
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Hourly, Hours Worked: " << hoursWorked << ", Hourly Rate: $" << std::fixed << std::setprecision(2) << hourlyRate << ", Salary: $" << calculateSalary() << "\n";
    }
    
};

int main() {
    //tries to open file
    std::ifstream file("employees.txt");

    //exits if file can't open
    if (!file) {
        std::cerr << "Error opening file. \n";
        return 1;
    }
    
    //vector for all employees
    std::vector<Employee*> employees;
    std::string line;
    
    //reads each line from the file
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        std::string name;
        int id;
        
        //if the input format is wrong skips bad lines
        if (!(iss >> type >> id >> name)) {
            std::cerr << "Invalid line format: " << line << "\n";
            continue;
        }
        
        try {

            //depending on type, formats and reads the data
            if (type == "Salaried") {
                double salary;
                if (iss >> salary)
                    employees.push_back(new SalariedEmployee(name, id, salary));
            } else if (type == "Hourly") {
                double rate;
                int hours;
                if (iss >> rate >> hours)
                employees.push_back(new HourlyEmployee(name, id, rate, hours));
            } else if (type == "Commission") {
                double base;
                double rate;
                double sales;
                if (iss >> base >> sales >> rate)
                employees.push_back(new CommissionEmployee(name, id, base, sales, rate));
            } else {
                std::cerr << "Unknown employee type: " << type << "\n";
            } //if un readable format, states there has been an error
        } catch(...) {
            std::cerr << "Error processing line: " << line << "\n";
        }
    }
    
    file.close(); //closes file
    
    //for all employees, displays the info
    for (const auto& emp : employees) {
        emp->displayInfo();
    }
    
    //cleans up memory
    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}



















