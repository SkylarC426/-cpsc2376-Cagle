#include <iostream>
#include <list>
#include <string>

//displays menu
void showMenu() {
    std::cout << "\n1. Add Task\n";
    std::cout << "2. Remove Task\n";
    std::cout << "3. Show Tasks\n";
    std::cout << "4. Exit\n";
    std::cout << "Choice: ";
}

//adds a task to list
void addTask(std::list<std::string>& tasks) {
    std::string task;
    std::cout << "Enter task: ";
    std::cin.ignore();
    std::getline(std::cin, task);
    tasks.push_back(task);
    std::cout << "Task added\n";
}

//removes task from list
void removeTask(std::list<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to remove.\n";
        return;
    }

    int number;
    std::cout << "Enter task number to remove: ";
    std::cin >> number;

    //validates if number is within list size
    if (number <= 0 || number > tasks.size()) {
        std::cout << "Invalid task number.\n";
        return;
    }

    //iterator advances through to the n-1th element and removes it
    auto it = tasks.begin();
    std::advance(it, number - 1);
    tasks.erase(it);
    std::cout << "Task removed.\n";
}

//displays all tasks
void showTasks(const std::list<std::string>& tasks) {
    //if no tasks, say no tasks
    if (tasks.empty()) {
        std::cout << "No tasks.\n";
        return;
    }

    //prints tasks out and has them numbered
    std::cout << "Tasks:\n";
    int i = 1;
    for (const auto& task : tasks) {
        std::cout << i++ << ". " << task << "\n";
    }
}

int main() {
    //vector to hold the tasks
    std::list<std::string> tasks;
    int choice;

    do {
        //shows the menu and gives the user a way to input
        showMenu();
        std::cin >> choice;

        //cases for each option
        switch (choice) {
            case 1: //adds task
                addTask(tasks);
                break;
            case 2: //removes tasks
                removeTask(tasks);
                break;
            case 3: //shows tasks
                showTasks(tasks);
                break;
            case 4: //leaves program
                std::cout << "exiting program\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 4); //keeps going until 4 is chosen

    return 0;
}