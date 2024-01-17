/* BusStop.cpp

   This file contains the implementation of the BusStop class, which represents a bus stop in the context of
   public transportation information. The BusStop class defines the attributes and behavior of a bus stop,
   including its unique identifier, bus route, name, direction of travel, location, and corner details.

   Created by: abdullah bin masood
   Date: nov 30 2023

   The BusStop class is responsible for initializing bus stop objects with the provided information and
   implementing a function for printing bus stop details. It is part of a broader system that manages bus
   stops and their associated data.

*/

#include "busstop.h"
#include "busstops.h"
#include <curl/curl.h>


BusStop::BusStop(int stopID, int busRoute, const std::string& stopName, const std::string& directionOfTravel, const std::string& corner,
                 double latitude, double longitude)
    : StopID(stopID), BusRoute(busRoute), StopName(stopName), 
      DirectionOfTravel(directionOfTravel), Corner(corner), 
      Latitude(latitude), Longitude(longitude) {}


bool BusStop::print()
{return true;}
