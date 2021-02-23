/*
 * Mammal.h
 *
 *  Created on: Feb 18, 2021
 *      Author: 1911931_snhu
 */

#ifndef MAMMAL_H_
#define MAMMAL_H_
#include "Animal.h"

class Mammal : public Animal {
public:
	int Nurse;
	Mammal();
	virtual ~Mammal();
};

#endif /* MAMMAL_H_ */
