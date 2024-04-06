/*
 * Pinky.h
 *
 *  Created on: May 14, 2017
 *      Author: ahsanabbas
 */

#ifndef PINKY_H_
#define PINKY_H_

#include "Ghost.h"

class Pinky: public Ghost {

public :

	Pinky(int x = 0 , int y = 0) ;

	void draw() ;

	~Pinky() ;
};

#endif /* PINKY_H_ */
