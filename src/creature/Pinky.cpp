/*
 * Pinky.cpp
 *
 *  Created on: May 14, 2017
 *      Author: ahsanabbas
 */

#include "creature/Pinky.h"

Pinky::Pinky(int x , int y )
:	Ghost(x,y,"PINKY",FRIGHTENED,3,false)
{

}

void Pinky::draw()
{
	DrawEnemy(getX_Coordinate(), getY_Coordinate(),PINK,ghostWidht,ghostHeight) ;
}

Pinky::~Pinky()
{

}
