#include <iostream>
#include <list>
#include <string>

void showMenu() {
    std::cout << "\n1. Add Task\n";
    std::cout << "2. Remove Task\n";
    std::cout << "3. Show Tasks\n";
    std::cout << "4. Exit\n";
    std::cout << "Choice: ";
}

void addTask(std::list<std::string>& tasks) {
    std::string task;
    std::cout << "Enter task: ";
    std::cin.ignore(); // Clear leftover newline
    std::getline(std::cin, task);
    tasks.push_back(task);
    std::cout << "Task added!\n";
}

void removeTask(std::list<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to remove.\n";
        return;
    }

    int number;
    std::cout << "Enter task number to remove: ";
    std::cin >> number;

    if (number <= 0 || number > tasks.size()) {
        std::cout << "Invalid task number.\n";
        return;
    }

    auto it = tasks.begin();
    std::advance(it, number - 1);
    tasks.erase(it);
    std::cout << "Task removed!\n";
}

void showTasks(const std::list<std::string>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks.\n";
        return;
    }

    std::cout << "Tasks:\n";
    int i = 1;
    for (const auto& task : tasks) {
        std::cout << i++ << ". " << task << "\n";
    }
}

int main() {
    std::list<std::string> tasks;
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                removeTask(tasks);
                break;
            case 3:
                showTasks(tasks);
                break;
            case 4:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}