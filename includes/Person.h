/*
 * Person.h
 *
 *  Created on: Oct 19, 2021
 *      Author: keith
 */

#ifndef PERSON_H_
#define PERSON_H_

class Person {
private :
	int personID;
	int numbBowlsSoupEaten;
	int numbDrinksDrunk;
public:
	/***
	 * Constructor
	 * @param personID identity of this person, save it
	 */
	Person(int personID);
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
	void eatlunch();
	
	/***
	 * the following functions are for auditing, they are already implemented
	 */
	int getnumbBowlsSoupEaten(){return numbBowlsSoupEaten;};
	int getnumbDrinksDrunk(){return numbDrinksDrunk;};	
	int getPersonID(){return personID;};
};

#endif /* PERSON_H_ */
