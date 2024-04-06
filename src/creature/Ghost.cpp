/*
 * Ghost.cpp
 *
 *  Created on: May 9, 2017
 *      Author: ahsanabbas
 */

#include "creature/Ghost.h"



Ghost::Ghost(int x , int y , std::string name ,int behaviour, int startingRow , bool BFS )
	:	Creature(x,y,name)
{
	this->behaviour = behaviour ;
	followBFS = BFS ;
	this->startingRow = startingRow ;
	ghostHeight = 48;
	ghostWidht = 48;

}
void Ghost::setBehaviour(int behaviour)
{
	this->behaviour = behaviour ;
}
int Ghost::getBehaviour()
{
	return behaviour ;
}

void Ghost::switchBehaviour()
{
	if ( followBFS )
	{
		if ( behaviour == CHASE )
			behaviour = SCATTER ;
		else
			behaviour = CHASE ;
	}
}

bool Ghost::FollowBFS()
{
	return followBFS ;
}
void Ghost::setBFS(bool state)
{
	followBFS = state ;
}


int Ghost::getStartingRow() const {
	return startingRow;
}

void Ghost::draw()
{
	DrawEnemy(getX_Coordinate(), getY_Coordinate(),WHITE,ghostWidht,ghostHeight) ;
}


Ghost::~Ghost()
{

}

