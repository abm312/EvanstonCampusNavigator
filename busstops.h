/* BusStops.h

   This header file defines the BusStops class, which represents a collection of bus stops in the context of public
   transportation information. The class declaration includes member functions for reading bus stop data from a CSV
   file, finding the closest bus stop based on coordinates and direction, printing bus stop details, retrieving the
   total number of bus stops, and obtaining bus arrival predictions.

   Created by: Abdullah bin masood
   Date: November 30, 2023

   The BusStops class encapsulates essential functionality for managing and accessing information about bus stops.
   It uses the BusStop class to represent individual bus stops and relies on external libraries such as libcurl for
   web requests.

   Member functions defined in this class:
   - readFromCSV(const std::string& filename): Reads bus stop data from a CSV file and populates the stops vector.
   - findClosestStop(double lat, double lon, const std::string& direction) const: Finds the closest bus stop based
     on given coordinates and travel direction.
   - print() const: Prints details of all bus stops in a sorted order by stop ID.
   - getNumBusStops() const: Returns the total number of bus stops in the collection.
   - getPredictionsForStop(const BusStop& stop, CURL *curl) const: Retrieves and formats bus arrival predictions for
     a specific bus stop using web requests.

   The BusStops class serves as a central component for managing and accessing public transportation information,
   making it a crucial part of applications related to bus route planning and tracking.

*/
#pragma once
#include <vector>
#include "busstop.h"
#include "dist.h"
#include <limits>
#include <algorithm>
#include <curl/curl.h>


class BusStops {
private:
    std::vector<BusStop> stops;

public:
    void readFromCSV(const std::string& filename);
    std::pair<BusStop, double> findClosestStop(double lat, double lon, const std::string& direction) const;

    void print() const;

    int getNumBusStops() const; // Returns the number of bus stops

std::string getPredictionsForStop(const BusStop& stop, CURL *curl) const; 
    
};
