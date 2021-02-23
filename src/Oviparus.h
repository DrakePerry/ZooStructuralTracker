/*
 * Oviparus.h
 *
 *  Created on: Feb 18, 2021
 *      Author: 1911931_snhu
 */
#ifndef OVIPARUS_H_
#define OVIPARUS_H_
#include "Animal.h"

class Oviparus : public Animal{
public:
	int NumberOfEggs;
	Oviparus();
	virtual ~Oviparus();
};

#endif /* OVIPARUS_H_ */
