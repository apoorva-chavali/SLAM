#include "Object.h"
#include "ObjectParser.h"
#include "Grid.h"
#include <iostream>
#include <iomanip>


// Helper function to display a vector
void printVector(const std::vector<float>& vec) {
    std::cout << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
}

int main() {
    // Create parser instance
    ObjectParser parser;

    // Parse objects from file
    std::string filename = "objects.txt";
    std::vector<Object> objects = parser.parseFile(filename);

    // Display results
    std::cout << "Successfully parsed " << objects.size() << " objects:\n" << std::endl;

    // Create and display the grid visualization
    std::cout << "\n==== Object Grid Visualization ====\n" << std::endl;
    Grid grid_v(20);
    grid_v.placeObjects(objects);
    grid_v.displayGrid();

    return 0;
}