/* building.cpp

   This file contains the implementation of the Building class, which represents a building in the Open Street Map.

   Prof. Joe Hummel
   Northwestern University
   CS 211

   The Building class is responsible for defining the behavior and attributes of a building object. It includes
   functions to check if a building contains a specific node, print building information, add nodes to a building,
   and calculate the location of the building based on its nodes. Additionally, it makes use of external data
   sources such as Nodes and BusStops to enhance its functionality.

*/

#include <utility>
#include <numeric>
#include <iostream>
#include <curl/curl.h>

#include "building.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// containsThisNode
//
// Returns true if the building's nodes contains the given node id,
// false if not.
//
bool Building::containsThisNode(long long nodeid)
{
  for (long long id : this->NodeIDs)
  {
    if (nodeid == id)
      return true;
  }

  // 
  // if get here, not found:
  //
  return false;
}

//
// print
// 
// prints information about a building --- id, name, etc. -- to
// the console. The function is passed the Nodes for searching 
// purposes.
//
void Building::print(Nodes& nodes, const BusStops& busStops, CURL *curl)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  std::cout << "# perimeter nodes: " << this->NodeIDs.size() << std::endl; // Number of perimeter nodes project 07
  auto location = this->getLocation(nodes);
  std::cout << "Location: (" << location.first << ", " << location.second << ")" << std::endl;


///////remove if wrong project 7
// Find the closest southbound bus stop
    auto closestSouthbound = busStops.findClosestStop(location.first, location.second, "Southbound");

    // Find the closest northbound bus stop
    auto closestNorthbound = busStops.findClosestStop(location.first, location.second, "Northbound");

    std::cout << "Closest southbound bus stop:" << endl; 
        std::cout << "  " << closestSouthbound.first.getID() << ": " 
          << closestSouthbound.first.getName() << ", bus #" 
          << closestSouthbound.first.getRoute() 
          // << closestSouthbound.first.getDirection()
           << ", " 
          << closestSouthbound.first.getCorner() <<  ", " 
          << closestSouthbound.second << " miles" << std::endl;


          ///predictions
          // Get and print predictions for the southbound stop
    std::string southboundPredictions = busStops.getPredictionsForStop(closestSouthbound.first, curl);
    std::cout << southboundPredictions<<endl;



   std::cout << "Closest northbound bus stop:" << endl; 
     std::cout <<"  " 
          << closestNorthbound.first.getID() << ": " 
          << closestNorthbound.first.getName() << ", bus #" 
          << closestNorthbound.first.getRoute()  
          // << closestNorthbound.first.getDirection()
           << ", " 
          << closestNorthbound.first.getCorner() << ", " 
          << closestNorthbound.second << " miles" << std::endl;

          // Get and print predictions for the northbound stop
    std::string northboundPredictions = busStops.getPredictionsForStop(closestNorthbound.first, curl);
    std::cout << northboundPredictions<< endl;




//commented out

  // cout << "Nodes:" << endl;
  // for (long long nodeid : this->NodeIDs)
  // {
  //   cout << "  " << nodeid << ": ";

  //   double lat = 0.0;
  //   double lon = 0.0;
  //   bool entrance = false;

  //   bool found = nodes.find(nodeid, lat, lon, entrance);

  //   if (found) {
  //     cout << "(" << lat << ", " << lon << ")";

  //     if (entrance)
  //       cout << ", is entrance";

  //     cout << endl;
  //   }
  //   else {
  //     cout << "**NOT FOUND**" << endl;
  //   }
  // }//for
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}


//
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
pair<double, double> Building::getLocation(const Nodes& nodes)
{
double sumLat = 0.0;
  double sumLon = 0.0;

  for (auto id : this->NodeIDs) {
    double lat, lon;
    bool isEntrance; // This value is not used here
    if (nodes.find(id, lat, lon, isEntrance)) {
      sumLat += lat;
      sumLon += lon;
    }
  }

  double avgLat = sumLat / this->NodeIDs.size();
  double avgLon = sumLon / this->NodeIDs.size();

  return std::make_pair(avgLat, avgLon);
}
