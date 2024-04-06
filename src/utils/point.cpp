/*
 * point.cpp
 *
 *  Created on: Apr 25, 2017
 *      Author: ahsanabbas
 */

#include "utils/point.h"
#include <iostream>
using namespace std;
#include <cmath>

Point::Point()
{
	xCoordinate = 0 ;
	yCoordinate = 0 ;
}

Point::Point( int x , int y )
{
	xCoordinate = x ;
	yCoordinate = y ;
}


void Point::displayPoint()
{
	cout << "(" << xCoordinate << "," << yCoordinate << ")" ;
}

float Point::distance(const Point& obj )
{
	return pow( ( pow(xCoordinate - obj.xCoordinate , 2) + pow(yCoordinate - obj.yCoordinate , 2) ) , 0.5 ) ;
}


std::ostream& operator<< ( std::ostream& c , Point& obj )
{
	obj.displayPoint() ;
	return c ;
}

int Point::getX() const {
	return xCoordinate;
}

void Point::setX(int coordinate) {
	xCoordinate = coordinate;
}

int Point::getY() const {
	return yCoordinate;
}

void Point::setY(int coordinate) {
	yCoordinate = coordinate;
}
