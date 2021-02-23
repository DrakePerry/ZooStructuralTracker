/*
 * Animal.h
 *
 *  Created on: Feb 18, 2021
 *      Author: 1911931_snhu
 */
#include <iostream>
#ifndef ANIMAL_H_
#define ANIMAL_H_

using namespace std;

class Animal {
public:
	Animal();
	string Name;
	int TrackNum;

	virtual ~Animal();
};

#endif /* ANIMAL_H_ */
