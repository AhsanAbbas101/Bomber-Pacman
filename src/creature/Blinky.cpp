/*
 * Blinky.cpp
 *
 *  Created on: May 14, 2017
 *      Author: ahsanabbas
 */

#include "creature/Blinky.h"

Blinky::Blinky(int x , int y)
:	Ghost(x,y,"BLINKY",CHASE,1,true)
{

}

void Blinky::draw()
{
	DrawEnemy(getX_Coordinate(), getY_Coordinate(),BLUE,ghostWidht,ghostHeight) ;
}


Blinky::~Blinky()
{

}

