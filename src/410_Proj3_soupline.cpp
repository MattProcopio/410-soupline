#include <iostream>
#include <thread>
#include <vector>
#include <time.h>
#include <chrono>
#include <mutex>
#include "../includes/Soupline.h"
#include "../includes/Person.h"
#include "../includes/constants.h"
#include "../includes/Auditor.h"

using namespace std;
//global
Soupline msl(ZERO,ZERO);	//created with no soup or drinks
Auditor auditor;

//use BOTH of these mutexes.  One to synchronize access to soup and one to drinks
//what are the advantages of 2 mutexes?
//What are the risks?
std::mutex soup_mutex;
std::mutex drink_mutex;

void thrdfunc(int id){
	Person p(id);
	p.eatlunch();	
	//record what the person ate and drank so we can reconcile Soupline records with user records
	auditor.report(p.getPersonID(), p.getnumbBowlsSoupEaten(), p.getnumbDrinksDrunk());
}

void doRound(int numbBowlsSoup, int numbDrinks, int numbPeople ) {
	//do I need to use a mutex to protect the following 2 globals?
	//No.  There is only 1 thread running when I modify them
	msl.restock(numbBowlsSoup, numbDrinks);
	auditor.resetParams(numbBowlsSoup, numbDrinks, numbPeople);
	
	std::vector<std::thread> vecPeople;
	//start threads
	for (int i = 0; i < numbPeople; i++) {
		vecPeople.push_back(std::thread(thrdfunc, i));
	}
	//wait for em to finish
	for (auto &t : vecPeople) {
		t.join();
	}
	auditor.do_audit();
}

//show starting a bunch of threads
int main()
{
	//handle no soup or drinks
	doRound(ZERO,ZERO,NUMBER_PEOPLE);
	
	//handle restocking
	doRound(INITIAL_BOWLS_SOUP,INITIAL_DRINKS, NUMBER_PEOPLE);
	return 0;
}
