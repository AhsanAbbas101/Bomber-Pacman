/*
 * Inky.cpp
 *
 *  Created on: May 14, 2017
 *      Author: ahsanabbas
 */

#include "creature/Inky.h"

Inky::Inky(int x,int y)
:	Ghost(x,y,"INKY",CHASE,1,true)
{

}

void Inky::draw()
{
	DrawEnemy(getX_Coordinate(), getY_Coordinate(),DARK_GRAY,ghostWidht,ghostHeight) ;
}

Inky::~Inky()
{

}
