/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#pragma once
#include "busstop.h"
#include "busstops.h"
#include "curl_util.h"
#include <curl/curl.h>

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "nodes.h"
#include "building.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// Keeps track of all the buildings in the map.
//
class Buildings
{
public:
  vector<Building> MapBuildings;

  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and 
  // stores all the buildings into the given vector.
  //
  void readMapBuildings(XMLDocument& xmldoc);

  //
  // print
  //
  // prints each building (id, name, address) to the console.
  //
  void print();

  //
  // findAndPrint
  //
  // Prints each building that contains the given name.
  //
  void findAndPrint(string name, Nodes& nodes, const BusStops& busStops, CURL *curl);

  //
  // accessors / getters
  //
  int getNumMapBuildings();

};


