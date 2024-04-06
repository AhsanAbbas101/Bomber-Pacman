/*
 * Clyde.cpp
 *
 *  Created on: May 14, 2017
 *      Author: ahsanabbas
 */

#include "creature/Clyde.h"

Clyde::Clyde(int x , int y )
:	Ghost( x , y , "CLYDE" , CHASE , 1 , true )
{

}


void Clyde::draw()
{
	DrawEnemy(getX_Coordinate(), getY_Coordinate(),DARK_RED,ghostWidht,ghostHeight) ;
}

Clyde::~Clyde()
{

}
