/*
 * Auditor.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: keith
 */
#include <iostream>
#include <algorithm>
#include <numeric>
#include <math.h>
#include "../includes/constants.h"
#include "../includes/Auditor.h"
using namespace std;

//tracks how many points you will get out of 100
//yeah, yeah its a global
int total_points =0;

//this is a template class, its mostly here as a helper for me
//the T and U are generic params, I can substitute any type for them
//they must be comparable with ==, templates are extremely hard to get right BTW
template<typename T, typename U>
bool EXPECT_EQ(T expectedVal, U actualVal,string testnumb , int pts){
	bool bout = (expectedVal == actualVal);
	if (bout){
		total_points+=pts;
		cout<<"SUCCESS "+testnumb+ "\t total points="<<total_points;
		
	}
	else
		cout<<"FAIL "+ testnumb<< "\t Expected:"<<expectedVal<<"  got:"<<actualVal;
	cout<<endl;
	return bout;
}
template<typename T, typename U>
bool EXPECT_NEARLY_EQ(T expectedVal, U actualVal,string testnumb , int pts, int range=1){
	bool bout = ((std::abs(expectedVal - actualVal) <=range));
	if (bout){
		total_points+=pts;
		cout<<"SUCCESS "+testnumb+ "\t total points="<<total_points;
		
	}
	else
		cout<<"FAIL "+ testnumb<< "\t Expected:"<<expectedVal<<"  got:"<<actualVal;
	cout<<endl;
	return bout;
}

Auditor::Auditor() {}
/***
 * parameters the auditor needs to check results
 */
void Auditor::resetParams(int numbBowlsSoup, int numbDrinks, int numbPeople){
	this->numbBowlsSoup = numbBowlsSoup;
	this->numbDrinks = numbDrinks;
	this->numbPeople = numbPeople;
	my_customers.clear();
}

void Auditor::report(int personID,int numbBowlsSoupEaten,int numbDrinksDrunk){
	lock_guard<mutex> lck(m);
	customer mc;
	mc.personID=personID;
	mc.numbBowlsSoup = numbBowlsSoupEaten;
	mc.numbDrinks = numbDrinksDrunk;
	my_customers.push_back(mc);
}
void Auditor::do_audit(){
	lock_guard<mutex> lck(m);
	
	//did all customers get soup and drinks
	EXPECT_EQ (int(my_customers.size()), numbPeople,"checking correct number customers",5);
	
	int soups=ZERO;
	int drinks=ZERO;
	for (auto& t : my_customers){
		soups+=t.numbBowlsSoup;
		drinks+=t.numbDrinks;
	}
	
	//did the total number of soups match?
	EXPECT_EQ (soups, numbBowlsSoup,"checking total soups\t\t",3);
	
	//did total number drinks match?
	EXPECT_EQ (drinks, numbDrinks,"checking total drinks\t\t",2);
	
	//everyone should get either the same amount, or withen 1 unit of each other
	double mean = soups/numbPeople;
	
	if(my_customers.size()>0){
		int defaultsoup=numbBowlsSoup/my_customers.size();
		int defaultdrinks=numbDrinks/my_customers.size();
		for (auto& t : my_customers){
			EXPECT_NEARLY_EQ(t.numbBowlsSoup,defaultsoup,string("checking person "+std::to_string(t.personID)+"\t number soups="+std::to_string(t.numbBowlsSoup))+ ",correct soups="+std::to_string(defaultsoup), 1);
//			EXPECT_EQ((std::abs(t.numbBowlsSoup-defaultsoup)<=1), true, string("checking person "+std::to_string(t.personID)+"\t number soups="+std::to_string(t.numbBowlsSoup)), 1);	
		}
		for (auto& t : my_customers){
			EXPECT_NEARLY_EQ(t.numbDrinks,defaultdrinks,string("checking person "+std::to_string(t.personID)+"\t number drinks="+std::to_string(t.numbDrinks))+ ",correct drinks="+std::to_string(defaultdrinks), 1);
//			EXPECT_EQ((std::abs(t.numbDrinks-defaultdrinks)<=1), true, string("checking person "+std::to_string(t.personID)+"\t number drinks="+std::to_string(t.numbDrinks)), 1);	
		}
	}		
}

