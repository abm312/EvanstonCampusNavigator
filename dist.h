/*dist.h*/

//
// Computes the distance between 2 positions, given in
// (latitude, longitude) coordinates.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#pragma once


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
double distBetween2Points(double lat1, double lon1, double lat2, double lon2);

