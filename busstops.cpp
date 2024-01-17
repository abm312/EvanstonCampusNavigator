/* BusStops.cpp

   This source file defines the implementation of the BusStops class, which represents a collection of bus stops
   in the context of public transportation information. The class includes functions for reading bus stop data from
   a CSV file, printing bus stop details, finding the closest bus stop based on coordinates and direction, and
   retrieving bus stop predictions.

   Created by: Abdullah bin masood
   Date: November 30, 2023

   The BusStops class provides essential functionality for managing and accessing information about bus stops. It
   utilizes the BusStop class to represent individual bus stops and relies on external libraries such as libcurl
   and nlohmann::json for web requests and JSON parsing.

   Functions included in this implementation:
   - readFromCSV(const std::string& filename): Reads bus stop data from a CSV file and populates the stops vector.
   - print() const: Prints details of all bus stops, sorted by stop ID.
   - findClosestStop(double lat, double lon, const std::string& direction) const: Finds the closest bus stop based
     on given coordinates and travel direction.
   - getNumBusStops() const: Retrieves the total number of bus stops in the collection.
   - getPredictionsForStop(const BusStop& stop, CURL *curl) const: Retrieves and formats bus arrival predictions for
     a specific bus stop using web requests and JSON parsing.

*/

#include "busstops.h"
#include "busstop.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include "dist.h"
#include "curl_util.h" 
#include <curl/curl.h>
#include "json.hpp"



using json = nlohmann::json;


void BusStops::readFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> fields;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Assuming the fields are: ID, Route, Name, Direction, Corner, Latitude, Longitude
        if (fields.size() == 7) {
            int stopID = std::stoi(fields[0]);
            int route = std::stoi(fields[1]);
            std::string name = fields[2];
            std::string direction = fields[3];
            std::string corner = fields[4];
            double latitude = std::stod(fields[5]);
            double longitude = std::stod(fields[6]);

            BusStop stop(stopID, route, name, direction, corner, latitude, longitude);
            stops.push_back(stop);
        } else {
            std::cerr << "Error: Incorrect number of fields in line: " << line << std::endl;
        }
    }

    file.close();
}



// void BusStops::readFromCSV(const std::string& filename) {
//     std::ifstream file(filename);
    
//     if (!file.is_open()) {
//         std::cerr << "Error opening file: " << filename << std::endl;
//         return;
//     }
    
//     std::string line;
//     while (getline(file, line)) {
//         std::stringstream ss(line);
//         std::string field;
//         std::vector<std::string> fields;

//         while (getline(ss, field, ',')) {
//             fields.push_back(field);
//         }

//         if (fields.size() == 7) {
//             // Assuming the fields are: ID, Route, Name, Direction, Corner, Latitude, Longitude
//             int stopID = std::stoi(fields[0]);
//             int route = std::stoi(fields[1]);
//             std::string& name = fields[2];
//             std::string& direction = fields[3];
//             std::string& corner = fields[4];
//             double latitude = std::stod(fields[5]);
//             double longitude = std::stod(fields[6]);

//             BusStop stop(stopID, route, name, direction, corner, latitude, longitude);
//             stops.push_back(stop);
//         } else {
//             std::cerr << "Error: Incorrect number of fields in line: " << line << std::endl;
//         }
//     }

//     file.close();
// }


// void BusStops::print() const {
//     for (const auto& stop : stops) {
//         std::cout << stop.getID() << ": bus " << stop.getRoute() 
//                   << ", " << stop.getName() << ", " << stop.getDirection()
//                   << ", " << stop.getCorner() << ", location (" 
//                   << stop.getLatitude() << ", " << stop.getLongitude() << ")"
//                   << std::endl;
//     }
// }

void BusStops::print() const {
    // Create a copy of the stops vector to avoid modifying the original data
    std::vector<BusStop> sortedStops = stops;

    // Sort the vector based on stop ID
    std::sort(sortedStops.begin(), sortedStops.end(),
        [](const BusStop& a, const BusStop& b) {
            return a.getID() < b.getID();
        });

    // Print the sorted bus stops
    for (const auto& stop : sortedStops) {
        std::cout << stop.getID() << ": bus " << stop.getRoute() 
                  << ", " << stop.getName() << ", " << stop.getDirection()
                  << ", " << stop.getCorner() << ", location (" 
                  << stop.getLatitude() << ", " << stop.getLongitude() << ")"
                  << std::endl;
    }
}

std::pair<BusStop, double> BusStops::findClosestStop(double lat, double lon, const std::string& direction) const {
    double minDistance = std::numeric_limits<double>::max();
    BusStop closestStop; // Will hold the closest bus stop

    for (const auto& stop : stops) {
        if (stop.getDirection() == direction) { // Assuming BusStop has a getDirection() method
            double distance = distBetween2Points(lat, lon, stop.getLatitude(), stop.getLongitude());
            if (distance < minDistance) {
                minDistance = distance;
                closestStop = stop;
            }
        }
    }

    return {closestStop, minDistance};
}


int BusStops::getNumBusStops() const {
    return stops.size(); // Use this->stops if needed, but typically not required
}


std::string BusStops::getPredictionsForStop(const BusStop& stop, CURL *curl) const {
    if (curl == nullptr) {
        return "  <<bus predictions unavailable, CURL not initialized>>";
    }

    std::string response;

    std::string apiKey = "32ZEDddQBfkQW87Kkamfbm8tS"; 
    std::string route = std::to_string(stop.getRoute());
    std::string stopId = std::to_string(stop.getID());
    std::string url = "http://www.ctabustracker.com/bustime/api/v2/getpredictions?key=" + apiKey +
                      "&rt=" + route + "&stpid=" + stopId + "&format=json";

    bool success = callWebServer(curl, url, response);

    if (!success) {
        return "  <<bus predictions unavailable, call failed>>";
    }

    try {
        auto jsondata = json::parse(response); // Parse the response into a JSON object
        auto predictions = jsondata["bustime-response"]["prd"]; // Access the predictions list

        std::string formattedPredictions;
        for (auto& pred : predictions) {
            std::string vid = pred.value("vid", "");
            std::string rt = pred.value("rt", "");
            std::string rtdir = pred.value("rtdir", "");
            std::string prdctdn = pred.value("prdctdn", "");

            if (!prdctdn.empty()) {
                formattedPredictions += "  vehicle #" + vid + " on route " + rt + " travelling " + rtdir + " to arrive in " + prdctdn + " mins\n";
            }
        }

        if (formattedPredictions.empty()) {
            return "  <<no predictions available>>";
        }

        return formattedPredictions;
    } catch (json::parse_error& e) {
        return "  <<error parsing predictions>>";
    }
}