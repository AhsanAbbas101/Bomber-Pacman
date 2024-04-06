/*
 * Bomb.h
 *
 *  Created on: May 7, 2017
 *      Author: ahsanabbas
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "utils/point.h"
class Bomb {


private :
	Point position ;		// Bomb Position on the Board
	int radius ;			// Bomb Radius , By Default 1
	bool bombStatus ;		// Bomb Placed Status
	int bombTime ;			// Bomb On Screen Time Or Bomb To Explode Time
public :

	Bomb(int x = 0 , int y = 0 , int radius = 1);

	/* Accessors And Mutators */
	bool getBombStatus() const;
	void setBombStatus(bool bombStatus);
	int getRadius() const;
	void setRadius(int radius);

	void setX_Coordinate(int x_C);
	void setY_Coordinate(int y_C);
	int getX_Coordinate() ;
	int getY_Coordinate() ;


	int getTime() const;
	void setTime(int time) ;

	~Bomb() ;
};

#endif /* BOMB_H_ */
