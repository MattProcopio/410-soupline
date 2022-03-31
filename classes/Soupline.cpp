/*
 * Soupline.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: keith
 */
#include <algorithm>
#include <mutex>
//TODO your includes here 

#include "../includes/Soupline.h"
#include "../includes/externs.h"
#include "../includes/Person.h"
#include "../includes/constants.h"

using namespace std;

//TODO your implementation here

    /***
	 * Simulate a fair soupline, which makes sure everyone gets the same amount of soup and drinks
	 * @param numbBowlsSoup  start with this many bowls soup
	 * @param numbDrinks     start with this many drinks
	 */
	Soupline::Soupline(int numbBowlsSoup, int numbDrinks) {
		this->numbBowlsSoupLeft = numbBowlsSoup;
		this->numbDrinksLeft = numbDrinks;
	}

	/***
	 * Sets numbBowlsSoupLeft and numbDrinksLeft values to numbBowlsSoup and numbDrinks
	 * @param numbBowlsSoup
	 * @param numbDrinks
	 */
	void Soupline::restock(int numbBowlsSoup, int numbDrinks) {
		this->numbBowlsSoupLeft += numbBowlsSoup;
		this->numbDrinksLeft += numbDrinks;
	}

	/***
	 * If no soup left returns OUT_OF_SOUP
	 * If personID not found in my_customers AND numbBowlsSoupLeft>0 then give this person a bowl of soup (return BOWL_OF_SOUP)
	 * and record it by creating new customer struct using personID, numbBowlsSoup=1 and adding this struct to my_customers, be sure to decrement numbBowlsSoupLeft.
	 * If personID has had more bowls of soup than others in my_customers then return NOT_YOUR_TURN
	 * If it's persons turn to have soup returns 1 bowl by decrementing numbBowlsSoupLeft and returning BOWL_OF_SOUP
	 * @return NOT_YOUR_TURN if others have not had as much as this person
	 *         BOWL_OF_SOUP  1 bowl of soup
	 *         OUT_OF_SOUP if numbBowlsSoupLeft==0 return this
	 */
	int Soupline::getSoup(int personID) {
		lock_guard<mutex> lock(soup_mutex);
		if (numbBowlsSoupLeft <= 0) {
			return OUT_OF_SOUP;
		}
		bool inVector = false;
		int count = 0;
		int index = 0;
		for (customer c : my_customers) {
			if (c.personID == personID) {
				index = count;
				inVector = true;
			}
			count++;
		}
		if (!inVector) {
			customer c;
			c.personID = personID;
			c.numbBowlsSoup = 1;
			numbBowlsSoupLeft--;
			my_customers.push_back(c);
			return BOWL_OF_SOUP;
		}

		//int test1 = getFewestBowlsOfSoupServedToACustomer();
		//int test2 = my_customers[index].numbBowlsSoup;

		if (getFewestBowlsOfSoupServedToACustomer() < my_customers[index].numbBowlsSoup) {
			return NOT_YOUR_TURN;
		}
		my_customers[index].numbBowlsSoup++;
		numbBowlsSoupLeft--;
		return BOWL_OF_SOUP;
	}

	/***
	 * Find customer who has had the fewest bowls of soup and return numbBowlsSoup they have had
	 * If my_customers is empty, return ZERO
	 * @return ZERO or int
	 */
	int Soupline::getFewestBowlsOfSoupServedToACustomer() {
		if (my_customers.empty()) {
			return ZERO;
		}
		int fewest = my_customers[0].numbBowlsSoup;
		for (customer c : my_customers) {
			if (c.numbBowlsSoup < fewest) {
				fewest = c.numbBowlsSoup;
			}
		}
		return fewest;
	}

	/***
	 * If no drinks left returns OUT_OF_DRINKS
	 * If personID not found in my_customers AND numbDrinksLeft>0 then give this person a drink (return DRINK)
	 * and record it by creating new customer struct using personID, numbDrinks=1 and adding this struct to my_customers, be sure to decrement numbDrinksLeft.
	 * If personID has had more drinks than others in my_customers then return NOT_YOUR_TURN
	 * If it's persons turn to have drink, then returns 1 drink by decrementing numbDrinksLeft, updating this persons info in my_customers and returning DRINK
	 * @return NOT_YOUR_TURN if others have not had as much as this person
	 *         DRINK  1 drink
	 *         OUT_OF_DRINKS if numbDrinksLeft==0 return this
	 */
	int Soupline::getDrink(int personID) {
		lock_guard<mutex> lock(drink_mutex);
		if (numbDrinksLeft <= 0) {
			return OUT_OF_DRINKS;
		}
		bool inVector = false;
		int count = 0;
		int index = 0;
		for (customer c : my_customers) {
			if (c.personID == personID) {
				index = count;
				inVector = true;
			}
			count++;
		}
		if (!inVector) {
			customer c;
			c.personID = personID;
			c.numbDrinks = 1;
			numbDrinksLeft--;
			my_customers.push_back(c);
			return DRINK;
		}

		if (getFewestDrinksServedToACustomer() < my_customers[index].numbDrinks) {
			return NOT_YOUR_TURN;
		}
		my_customers[index].numbDrinks++;
		numbDrinksLeft--;
		return DRINK;
	}

	/***
	 * Find customer who has had the fewest drinks and return numbDrinks they have had
	 * If my_customers is empty, return ZERO
	 * @return ZERO or int
	 */
	int Soupline::getFewestDrinksServedToACustomer() {
		if (my_customers.empty()) {
			return ZERO;
		}
		int fewest = my_customers[0].numbDrinks;
		for (customer c : my_customers) {
			if (c.numbDrinks < fewest) {
				fewest = c.numbDrinks;
			}
		}
		return fewest;
	}
