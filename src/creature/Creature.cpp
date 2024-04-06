/*
 * Creature.cpp
 *
 *  Created on: May 4, 2017
 *      Author: ahsanabbas
 */

#include "creature/Creature.h"

/* Constructors */
Creature::Creature( Point p , std::string name )
	:	position(p)
{
	 this->name = name ;
	 alive = false ;
}

Creature::Creature( int x , int y , std::string name )
	:	position (x,y)
{
	this->name = name ;
	alive = false ;
}


/* Accessors And Mutators */
const std::string& Creature::getName() const {
	return name;
}

void Creature::setAliveSatus(bool status )
{
	alive = status ;
}
bool Creature::isAlive()
{
	if ( alive )
		return true ;

	return false ;
}

void Creature::setX_Coordinate ( int x  )
{
	position.setX(x) ;
}

void Creature::setY_Coordinate ( int y  )
{
	position.setY(y) ;
}
int Creature::getX_Coordinate()
{
	return position.getX() ;
}
int Creature::getY_Coordinate()
{
	return position.getY() ;
}

/* Destructor */
Creature::~Creature()
{

}
