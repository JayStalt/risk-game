// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the implementation file Continent.cpp of the class Continent.
//The interface of this class is in the header file Continent.h.

#include<string>
#include<list>
#include <iostream>
using namespace std;

#include"Continent.h"

int Continent::continentCount = 0;

Continent::Continent() {
	cout << "Default continent constructor\n";
	id = ++continentCount;
	owner = NULL;
	isOwned = false;
	countries = new vector<Country*>;
	numCountries = 0;
	controlValue = (rand() % 10) + 1;
}

Continent::Continent(string aname, int numC, int aid, int acontrolValue):name(aname) {
	cout << "Non-Default continent constructor\n";
	id = aid;
	owner = NULL;
	isOwned = false;
	countries = new vector<Country*>;
	numCountries = numC;
	controlValue = acontrolValue;
}

Continent::~Continent() {
	delete countries;
}

//accessors used to be inline, but it caused a problem with the linker.
string Continent::getName() const {
	return name;
}

int Continent::getId() const {
	return id;
}
Player* Continent::getOwner() const {
	return owner;
}

bool Continent::getIsOwned() const {
	return isOwned;
}

int Continent::getCount(){
	return continentCount;
}

int Continent::getNumCountries() const{
	return numCountries;
}

//returns a string with the names of the countries of the continent, seperated by a space
string Continent::getCountryNames() const {
	//making sure that there are countries in the list
	if (numCountries > 0) {
		string names = "";
		for (int i = 0; i < numCountries;i++)
			names += ((*countries)[i])->getName() + " ";
		return names;
	}
	else
		return "No countries";
}

vector<Country*>* Continent::getCountries() const {
	return countries;
}


void Continent::setName(string n) {
	name = n;
}

void Continent::setOwner(Player* o) {
	owner = o;
	setIsOwned(true);
}

void Continent::setIsOwned(bool o) {
	isOwned = o;
}

//Note that the concept of countries being members of only one continent takes place is shown in the Map class.
void Continent::addCountry(Country* c) {
	countries->push_back(c);
}

int Continent::getControlValue() {
	return controlValue;
}

//this method only exists for demo purposes (to reset the continentCount to 0 when a new menu option is selected)
void Continent::resetCount() {
	continentCount = 0;
}
