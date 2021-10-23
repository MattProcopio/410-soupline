/*
 * Auditor.h
 *
 *  Created on: Oct 19, 2021
 *      Author: keith
 */

#ifndef AUDITOR_H_
#define AUDITOR_H_
#include <vector>
#include <mutex>
#include "constants.h"
#include "Soupline.h"

class Auditor {
private:
	std::mutex m;
	std::vector<customer> my_customers;
	int numbBowlsSoup;
	int numbDrinks;
	int numbPeople;

public:
	Auditor();
	/***
	 * parameters the auditor needs to check results
	 * clears my_customers
	 */
	void resetParams(int numbBowlsSoup, int numbDrinks, int numbPeople);
	/***
	 * Person reports what they ate and drank
	 * @param personID
	 * @param numbBowlsSoupEaten
	 * @param numbDrinksDrunk
	 */
	void report(int personID,int numbBowlsSoupEaten,int numbDrinksDrunk);
	/***
	 * Compares the amount of food the people say they ate with what the soupline had to begin with
	 */
	void do_audit();
};

#endif /* AUDITOR_H_ */
