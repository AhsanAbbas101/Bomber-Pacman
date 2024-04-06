/*
 * Creature.h
 *
 *  Created on: May 4, 2017
 *      Author: ahsanabbas
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include "utils/point.h"
#include <string>

class Creature {

protected :

	Point position ;		// Position of The Creature
	std::string name ;		// Name of the Creature
	bool alive ;			// ALive Status of Creature

public :

	Creature( Point p , std::string name = " ") ;
	Creature ( int x , int y , std::string name = " ") ;


	/* Accessors And Mutators */
	const std::string& getName() const;
	void setAliveSatus(bool status ) ;
	bool isAlive() ;

	void setX_Coordinate ( int x  ) ;
	void setY_Coordinate ( int y  ) ;
	int getX_Coordinate() ;
	int getY_Coordinate() ;

	/* Function To Draw Creature On the Board */
	virtual void draw() = 0 ;

	virtual ~Creature() ;
};

#endif /* CREATURE_H_ */
