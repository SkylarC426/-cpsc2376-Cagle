#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

//base shape class
class Shape {
    public:
    virtual double getArea() const = 0;
};

//rectange from shape class
class Rectangle : public Shape {
    private:
    double width;
    double height;
    
    public:
	//constructor with width and height
    Rectangle(double w, double h) : width(w), height(h) {}

	//override getArea to calc rectangle area
    double getArea() const override {
        return width * height;
    }
};

//circle from shape class
class Circle : public Shape {
    private:
    double radius;
    
    public:
	//constructor with radius
    Circle(double r) : radius(r) {}

	//overrides getArea to calc circle area
    double getArea() const override {
        return M_PI * radius * radius;
    }
};

//prints all areas of every shape in the vector
void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes) {

	//prints with a set amount (4) decimal places
    std::cout << std::fixed << std::setprecision(4);

	//goes through all shapes and prints area
    for (const auto& shape: shapes) {
        std::cout << "Area: " << shape -> getArea() << std::endl;
    }
}

int main() { 

	//open the file
	std::ifstream file("shapes.txt");

	//if no file it stated cant open
	if (!file) {
	    std::cerr << "Filed failed to open.\n";
	    return 1;
	}
	
	//container for the shapes
	std::vector<std::unique_ptr<Shape>> shapes;
	std::string line;
	
	//reads each line of file
	while (std::getline(file, line)) {
	    std::istringstream iss(line);
	    std::string type;
	    iss >> type;
	    
		//if rectangle, reads width and height
	    if (type == "rectangle") {
	        double w;
	        double h;
	        if (iss >> w >> h) {
	            shapes.push_back(std::make_unique<Rectangle>(w, h));
	        }
	    } 
		//if circle, reads radius
		else if (type == "circle") {
	        double r;
	        if (iss >> r) {
	            shapes.push_back(std::make_unique<Circle>(r));
	        }
	    }
	}
	
	//prints all areas of all shapes
	printAllAreas(shapes);
	
	return 0;
}
