/*
 * Ghosts.h
 *
 *  Created on: May 9, 2017
 *      Author: ahsanabbas
 */

#ifndef GHOST_H_
#define GHOST_H_

#include "creature/Creature.h"
#include "utils/util.h"

/* enum to declare behaviour of Ghosts */
enum Behaviour {
	CHASE, SCATTER  , FRIGHTENED
};


class Ghost: public Creature {

protected :
	int behaviour ;			// Behaviour Variable
	bool followBFS ;		// Check if ghosts follow BFS or Not
	int startingRow ;		// starting row position of Ghost

	/* Ghost Height And Width For Drawing Ghost */
	int ghostHeight;
	int ghostWidht;
public :

	Ghost(int x = 0, int y = 0, std::string name = "Ghost" ,int behaviour = CHASE ,int startingRow = 1, bool BFS = false ) ;

	void setBehaviour(int behaviour) ;
	int getBehaviour() ;
	void switchBehaviour() ;
	bool FollowBFS() ;
	void setBFS(bool state) ;
	int getStartingRow() const;

	void draw() ;

	~Ghost() ;

};

#endif /* GHOST_H_ */
