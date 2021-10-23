/*
 * constants.h
 *
 *  Created on: Oct 19, 2021
 *      Author: keith
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
const int MILLI_SECONDS_TO_WAIT = 1;
const int NUMBER_PEOPLE		=20;

const int INITIAL_BOWLS_SOUP = 519;
const int INITIAL_DRINKS = 188;

const int BOWL_OF_SOUP = 1;
const int DRINK =1;
const int NOT_YOUR_TURN = -1;
const int OUT_OF_SOUP = -2;
const int OUT_OF_DRINKS = -3;

const int UNINITIALIZED = -1;
const int ZERO=0;
struct customer{
	int personID=UNINITIALIZED;
	int numbBowlsSoup = ZERO;
	int numbDrinks = ZERO;
};

#endif /* CONSTANTS_H_ */
