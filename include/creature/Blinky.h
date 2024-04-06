/*
 * Blinky.h
 *
 *  Created on: May 14, 2017
 *      Author: ahsanabbas
 */

#ifndef BLINKY_H_
#define BLINKY_H_

#include "Ghost.h"

class Blinky: public Ghost {

public :

	Blinky ( int x = 0 , int y = 0 );

	void draw();

	~Blinky() ;

};

#endif /* BLINKY_H_ */
