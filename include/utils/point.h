/*
 * point.h
 *
 *  Created on: Apr 25, 2017
 *      Author: ahsanabbas
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>

class Point {

private :

	int xCoordinate, yCoordinate;

public :

	Point() ;
	Point ( int x , int y ) ;

	void displayPoint() ;

	float distance(const Point& obj ) ;

	int getX() const;
	void setX(int coordinate);
	int getY() const;
	void setY(int coordinate);
};


std::ostream& operator<< ( std::ostream& c , Point& obj ) ;

#endif /* POINT_H_ */
