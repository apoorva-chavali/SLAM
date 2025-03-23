#ifndef GRID_H
#define GRID_H

#include "Object.h"
#include <vector>
#include <string>

class Grid {
public:
    // Constructor with grid size parameter (default 20x20)
    Grid(int size = 20);
    ~Grid();

    // Place objects on the grid
    void placeObjects(const std::vector<Object>& objects);

    // Display the grid with objects
    void displayGrid() const;

    // Save grid to file
    bool saveToFile(const std::string& filename) const;

private:
    int gridSize;
    char** grid;

    // Convert object coordinates to grid coordinates
    std::pair<int, int> objectToGridCoords(const Object& obj) const;

    // Initialize grid with empty cells
    void initializeGrid();

    // Clear the grid and free memory
    void clearGrid();

    // Get character representation based on object class
    char getObjectSymbol(OBJECT_CLASS objClass) const;
};

#endif // GRID_H
