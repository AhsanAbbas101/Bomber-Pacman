/*
 * Clyde.h
 *
 *  Created on: May 14, 2017
 *      Author: ahsanabbas
 */

#ifndef CLYDE_H_
#define CLYDE_H_

#include "Ghost.h"

class Clyde: public Ghost {

public :

	Clyde(int x= 0 , int y = 0);

	void draw();

	~Clyde() ;
};

#endif /* CLYDE_H_ */
