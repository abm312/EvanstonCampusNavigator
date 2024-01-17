/*dist.cpp*/

//
// Computes the distance between 2 positions, given in
// (latitude, longitude) coordinates.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include <iostream>
#include <cmath>

#include "dist.h"

using namespace std;


//
// DistBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2). Latitudes are positive above the equator and 
// negative below; longitudes are positive heading east of Greenwich 
// and negative heading west. Example: Chicago is (41.88, -87.63).
//
// Reference: chatGPT using haversine formula
//
// static constexpr double M_PI = 3.141592653589;

static double toRadians(double degrees)
{
  return (degrees * 3.141592653589 / 180.0);
}

double distBetween2Points(double lat1, double lon1, double lat2, double lon2)
{
  const double R = 6371; // Earth's radius in kilometers

  double dLat = toRadians(lat2 - lat1);
  double dLon = toRadians(lon2 - lon1);

  double a = sin(dLat / 2) * sin(dLat / 2) +
    cos(toRadians(lat1)) * cos(toRadians(lat2)) *
    sin(dLon / 2) * sin(dLon / 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  double dist_in_km = R * c;

  double dist_in_miles = dist_in_km * 0.6213711922;

  return dist_in_miles;
}
