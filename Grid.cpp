#include "Grid.h"
#include <iostream>
#include <fstream>
#include <cmath>

Grid::Grid(int size) : gridSize(size) {
    initializeGrid();
}

Grid::~Grid() {
    clearGrid();
}

void Grid::initializeGrid() {
    // Allocate memory for the grid
    grid = new char* [gridSize];
    for (int i = 0; i < gridSize; ++i) {
        grid[i] = new char[gridSize];
        // Fill with empty cells
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = '.';
        }
    }
}

void Grid::clearGrid() {
    if (grid) {
        for (int i = 0; i < gridSize; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
        grid = nullptr;
    }
}

void Grid::placeObjects(const std::vector<Object>& objects) {
    // Clear the grid first
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = '.';
        }
    }

    // Place objects on the grid
    for (const auto& obj : objects) {
        std::pair<int, int> coords = objectToGridCoords(obj);
        int x = coords.first;
        int y = coords.second;

        // Check if coordinates are within grid bounds
        if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
            grid[y][x] = getObjectSymbol(obj.getLabel());
        }
    }
}

std::pair<int, int> Grid::objectToGridCoords(const Object& obj) const {
    // Get position from object
    std::vector<float> pos = obj.getPosition();

    // Scale the x,y coordinates to fit the grid
    // Assuming positions range from 0 to 20 in the real world
    int x = static_cast<int>(pos[0]);
    int y = static_cast<int>(pos[1]);

    // Flip y-coordinate since grid is displayed with (0,0) at top-left
    y = gridSize - 1 - y;

    return { x, y };
}

char Grid::getObjectSymbol(OBJECT_CLASS objClass) const {
    switch (objClass) {
    case PERSON:         return 'P';
    case VEHICLE:        return 'V';
    case BAG:            return 'B';
    case ANIMAL:         return 'A';
    case ELECTRONICS:    return 'E';
    case FRUIT_VEGETABLE: return 'F';
    case SPORT:          return 'S';
    default:             return 'X';
    }
}

void Grid::displayGrid() const {
    // Print column numbers
    std::cout << "   ";
    for (int i = 0; i < gridSize; ++i) {
        if (i < 10) std::cout << " ";
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Print top border
    std::cout << "   ";
    for (int i = 0; i < gridSize; ++i) {
        std::cout << "---";
    }
    std::cout << std::endl;

    // Print grid with row numbers
    for (int i = 0; i < gridSize; ++i) {
        if (i < 10) std::cout << " ";
        std::cout << i << "| ";

        for (int j = 0; j < gridSize; ++j) {
            std::cout << grid[i][j] << " |";
        }
        std::cout << std::endl;

        // Print row separator
        std::cout << "   ";
        for (int j = 0; j < gridSize; ++j) {
            std::cout << "---";
        }
        std::cout << std::endl;
    }

    // Print legend
    std::cout << "\nLegend:" << std::endl;
    std::cout << "P - Person" << std::endl;
    std::cout << "V - Vehicle" << std::endl;
    std::cout << "B - Bag" << std::endl;
    std::cout << "A - Animal" << std::endl;
    std::cout << "E - Electronics" << std::endl;
    std::cout << "F - Fruit/Vegetable" << std::endl;
    std::cout << "S - Sport" << std::endl;
    std::cout << ". - Empty" << std::endl;
}

bool Grid::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return false;
    }

    // Write column numbers
    file << "   ";
    for (int i = 0; i < gridSize; ++i) {
        if (i < 10) file << " ";
        file << i << " ";
    }
    file << std::endl;

    // Write top border
    file << "   ";
    for (int i = 0; i < gridSize; ++i) {
        file << "---";
    }
    file << std::endl;

    // Write grid with row numbers
    for (int i = 0; i < gridSize; ++i) {
        if (i < 10) file << " ";
        file << i << "| ";

        for (int j = 0; j < gridSize; ++j) {
            file << grid[i][j] << " |";
        }
        file << std::endl;

        // Write row separator
        file << "   ";
        for (int j = 0; j < gridSize; ++j) {
            file << "---";
        }
        file << std::endl;
    }

    // Write legend
    file << "\nLegend:" << std::endl;
    file << "P - Person" << std::endl;
    file << "V - Vehicle" << std::endl;
    file << "B - Bag" << std::endl;
    file << "A - Animal" << std::endl;
    file << "E - Electronics" << std::endl;
    file << "F - Fruit/Vegetable" << std::endl;
    file << "S - Sport" << std::endl;
    file << ". - Empty" << std::endl;

    file.close();
    return true;
}