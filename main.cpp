#include "Object.h"
#include "ObjectParser.h"
#include <iostream>
#include <iomanip>

int main() {
    ObjectParser parser;

    // Define the reference GPS location (frame origin)
    double originLat = 37.7749;   // Example: San Francisco
    double originLon = -122.4194;
    double heading = 0.0;         // Heading of the frame in degrees (0 = true north)

    // Load objects from file
    std::string filename = "objects.txt";
    std::vector<Object> objects = parser.parseFile(filename);

    // Convert each object’s (x, y) into GPS coordinates
    for (auto& obj : objects) {
        obj.computeLatLonFromDisplacement(originLat, originLon, heading);
    }

    // Print the updated objects
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Converted " << objects.size() << " objects:\n" << std::endl;

    for (const auto& obj : objects) {
        std::cout << "Object ID: " << obj.getId()
                  << " | Lat: " << obj.getLatitude()
                  << " | Lon: " << obj.getLongitude()
                  << std::endl;
    }

    return 0;
}
