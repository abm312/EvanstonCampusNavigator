/* BusStop.h

   This header file defines the BusStop class, which represents a bus stop in the context of public transportation
   information. A bus stop is characterized by its unique identifier, bus route, name, direction of travel, corner
   details, latitude, and longitude. This class provides the structure for storing and accessing bus stop data.

   Created by: Abdullah bin masood
   Date: November 30, 2023

   The BusStop class includes constructors to initialize bus stop objects and getter methods to access specific
   attributes of a bus stop. Additionally, it defines a function for printing bus stop details.

*/
#pragma once
#include <string>
#include <curl/curl.h>


class BusStop {
public:
BusStop() = default; // Default constructor
    int StopID;
    int BusRoute;
    std::string StopName;
    std::string DirectionOfTravel;
    std::string Corner;
    double Latitude;
    double Longitude;

    BusStop(int stopID, int busRoute, const std::string& stopName, 
            const std::string& directionOfTravel, const std::string& corner,
            double latitude, double longitude);


    //getters
    int getID() const { return StopID; }
    int getRoute() const { return BusRoute; }
    std::string getName() const { return StopName; }
    std::string getDirection() const { return DirectionOfTravel; }
    std::string getCorner() const { return Corner; }
    double getLatitude() const { return Latitude; }
    double getLongitude() const { return Longitude; }

    bool print();
};
