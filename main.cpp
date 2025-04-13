#include "Object.h"
#include "ObjectParser.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <matplot/matplot.h>

int main() {

    ObjectParser parser;

    // Define the reference GPS location (frame origin)
    //Frame = vtti, 37.189823, -80.394825

    double originLat = 37.189823; 
    double originLon = -80.394825;
    double heading = 0.0;         // Heading of the frame in degrees (0 = true north)

    // Load objects from file
    std::string filename = "objects.txt";
    std::vector<Object> objects = parser.parseFile(filename);

    // Vectors for storing latitudes, longitudes, and labels
    std::vector<double> latitudes;
    std::vector<double> longitudes;
    std::vector<std::string> labels;

    latitudes.push_back(originLat);
    longitudes.push_back(originLon);
    labels.push_back("Frame");

    // Convert each object’s (x, y) into GPS coordinates
    for (auto& obj : objects) {
        obj.computeLatLonFromDisplacement(originLat, originLon, heading);
        
        // Store latitudes, longitudes, and labels
        latitudes.push_back(obj.getLatitude());
        longitudes.push_back(obj.getLongitude());
        labels.push_back(obj.getId());
    }

    // Print the updated objects to debug
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Converted " << objects.size() << " objects:\n" << std::endl;

    for (const auto& obj : objects) {
        std::cout << "Object ID: " << obj.getId()
                  << " | Lat: " << obj.getLatitude()
                  << " | Lon: " << obj.getLongitude()
                  << std::endl;
    }

    // Debugging: Check if latitudes and longitudes are being stored correctly
    std::cout << "\nPlotting data:\n";
    std::cout << "Latitudes: ";
    for (const auto& lat : latitudes) {
        std::cout << lat << " ";
    }
    std::cout << "\nLongitudes: ";
    for (const auto& lon : longitudes) {
        std::cout << lon << " ";
    }
    std::cout << std::endl;

    // Plot object points (latitudes vs longitudes)
    matplot::geoplot(latitudes, longitudes, "*");

    // Annotate object IDs
    for (size_t i = 0; i < latitudes.size(); ++i) {
        matplot::text(longitudes[i], latitudes[i], labels[i]);
    }

    // Set geographic limits to ensure the map is centered around the data
    double minLat = *std::min_element(latitudes.begin(), latitudes.end()) - 0.1;
    double maxLat = *std::max_element(latitudes.begin(), latitudes.end()) + 0.1;
    double minLon = *std::min_element(longitudes.begin(), longitudes.end()) - 0.1;
    double maxLon = *std::max_element(longitudes.begin(), longitudes.end()) + 0.1;

    // Set geolimits for the plot
    matplot::geolimits({minLat, maxLat}, {minLon, maxLon});


    // Show the plot
    matplot::show();

    return 0;
}
