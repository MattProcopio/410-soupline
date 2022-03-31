/*
 * Person.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: keith
 */
#include <iostream>
#include <thread>
#include <vector>
#include <time.h>
#include <chrono> // this_thread::sleep_for(chrono::milliseconds(MILLI_SECONDS_TO_WAIT));

//TODO your includes here 

#include "../includes/Person.h"
#include "../includes/externs.h"
#include "../includes/constants.h"
#include "../includes/Soupline.h"

using namespace std;

//TODO your implementation here

/***
 * Constructor
 * @param personID identity of this person, save it
 */
Person::Person(int personID) {
	this->personID = personID;
	this->numbBowlsSoupEaten = 0;
	this->numbDrinksDrunk = 0;
}

/***
 * gets soup and drinks until SoupLine runs out of both then exits
 *
 * runs a loop repeatedly asking for soup and drinks from msl, the soupline global
 * calls msl.getSoup(personID)
 * If call returns NOT_YOUR_TURN then gives other threads a chance by waiting MILLI_SECONDS_TO_WAIT
 * If call returns BOWL_OF_SOUP then increment numbBowlsSoupEaten
 * If call returns OUT_OF_SOUP then stop asking for soup
 *
 * calls msl.getDrink(personID)
 * If call returns NOT_YOUR_TURN then gives other threads a chance by waiting MILLI_SECONDS_TO_WAIT
 * If call returns DRINK then increment numbDrinksDrunk
 * If call returns OUT_OF_DRINKS then stop asking for drinks
 *
 * If soupline is out of both soup and drinks this function exits
 * @return void
 */
void Person::eatlunch() {
	bool hasSoup;
	bool hasDrink;
	if (msl.getnumbBowlsLeft() > 0) {
		hasSoup = true;
	}
	else {
		hasSoup = false;
	}
	if (msl.getnumbDrinksLeft() > 0) {
		hasDrink = true;
	}
	else {
		hasDrink = false;
	}

	//While there is soup and drinks left//
	while (hasSoup == true || hasDrink == true) {

		//If there is soup left, get soup//
		if (hasSoup == true) {
			int soup = msl.getSoup(personID);
			if (soup == NOT_YOUR_TURN) {
				this_thread::sleep_for(chrono::milliseconds(MILLI_SECONDS_TO_WAIT));
			}
			if (soup == BOWL_OF_SOUP) {
				numbBowlsSoupEaten++;
			}
			if (soup == OUT_OF_SOUP) {
				hasSoup = false;
			}
		}

		//If there are drinks left, get drink//
		if (hasDrink == true) {
			int drink = msl.getDrink(personID);
			if (drink == NOT_YOUR_TURN) {
				this_thread::sleep_for(chrono::milliseconds(MILLI_SECONDS_TO_WAIT));
			}
			if (drink == DRINK) {
				numbDrinksDrunk++;
			}
			if (drink == OUT_OF_DRINKS) {
				hasDrink = false;
			}
		}

	}
}
