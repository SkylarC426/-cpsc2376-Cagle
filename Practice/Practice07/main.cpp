#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

class Employee {
    protected:
    std::string name;
    int id;
    
    public:
    
    Employee(std::string name, int id) : name(std::move(name)), id(id) {}
    virtual ~Employee() = default;
    
    virtual double calculateSalary() const = 0;
    
    virtual void displayInfo() const {
        std::cout << "ID: " << id << ", Name: " << name;
    }
};

class SalariedEmployee : public Employee {
    private:
    double monthlySalary;
    
    public:
    SalariedEmployee(std::string name, int id, double monthlySalary) : Employee(std::move(name), id), monthlySalary(monthlySalary) {}
    
    double calculateSalary() const override {
        return monthlySalary;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Salaried, Monthly Salary: $" << std::fixed << std::setprecision(2) << calculateSalary() << "\n"; 
    }
    
};

class CommissionEmployee : public Employee {
    private:
    double baseSalary;
    double salesAmount;
    double commissionRate;
    
    public:
    CommissionEmployee(std::string name, int id, double baseSalary, double salesAmount, double commissionRate) : Employee(std::move(name), id), baseSalary(baseSalary), salesAmount(salesAmount), commissionRate(commissionRate) {}
    
    double calculateSalary() const override {
        return baseSalary + (salesAmount * commissionRate);
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Commission, Base Salary: $" << std::fixed << std::setprecision(2) << baseSalary << ", Sales: " << salesAmount << ", Commission Rate: " << (commissionRate * 100) << "%, Salary: $" << calculateSalary() << "\n";
    }
};

class HourlyEmployee : public Employee {
    private:
    double hourlyRate;
    int hoursWorked;
    
    public:
    HourlyEmployee(std::string name, int id, double hourlyRate, int hoursWorked) : Employee(std::move(name), id), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}
    
    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Hourly, Hours Worked: " << hoursWorked << ", Hourly Rate: $" << std::fixed << std::setprecision(2) << hourlyRate << ", Salary: $" << calculateSalary() << "\n";
    }
    
};

int main() {
    std::ifstream file("employees.txt");
    if (!file) {
        std::cerr << "Error opening file. \n";
        return 1;
    }
    
    std::vector<Employee*> employees;
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        std::string name;
        int id;
        
        if (!(iss >> type >> id >> name)) {
            std::cerr << "Invalid line format: " << line << "\n";
            continue;
        }
        
        try {
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
            }
        } catch(...) {
            std::cerr << "Error processing line: " << line << "\n";
        }
    }
    
    file.close();
    
    for (const auto& emp : employees) {
        emp->displayInfo();
    }
    
    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}



















