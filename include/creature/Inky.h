/*
 * Inky.h
 *
 *  Created on: May 14, 2017
 *      Author: ahsanabbas
 */

#ifndef INKY_H_
#define INKY_H_

#include "Ghost.h"

class Inky: public Ghost {

public :

	Inky(int x = 0 , int y = 0) ;

	void draw() ;

	~Inky() ;
};

#endif /* INKY_H_ */
