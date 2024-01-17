/*building.h*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#pragma once
#include "curl_util.h"
#include <curl/curl.h>

#include <string>
#include <vector>
#include "busstop.h"
#include "busstops.h"
#include "node.h"
#include "nodes.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // containsThisNode
  //
  // Returns true if the building's nodes contains the given node id,
  // false if not.
  //
  bool containsThisNode(long long nodeid);

  //
  // print
  // 
  // prints information about a building --- id, name, etc. -- to
  // the console. The function is passed the Nodes for searching 
  // purposes.
  //
  void print(Nodes& nodes, const BusStops& busStops, CURL *curl);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);


  //
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
  pair<double, double> getLocation(const Nodes& nodes);

};
