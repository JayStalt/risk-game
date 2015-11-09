// Assignment #2 - COMP345 - Section DI - Fall 2015
// Author: Jennifer Sunahara (27590628)
//
//This is the implementation file Map.cpp of the class Map
//which is an abstract class.
//The interface of this class is in the header file Map.h.

#include<string>
#include<iostream>
#include<vector>

using namespace std;

#include "Country.h"
#include "Continent.h"
#include "Map.h"


Map::Map(string n, int ctry, int ctnt) {
	name = n;
	numCountries = ctry;
	numContinents = ctnt;
	continents = new vector<Continent*>;
	countries = new vector<Country*>;
}

Map::~Map() {
	delete continents;
	delete countries;
}

int Map::getNumCountries() const{
	return numCountries;
}

int Map::getNumContinents() const {
	return numContinents;
}

//returns a string with the name of the map
string Map::getName() const {
	return name;
}

//returns a pointer to the vector with the continents of the map
vector<Continent*>* Map::getContinents() const {
	return continents;
}

//returns a pointer to the vector with the countries of the map
vector<Country*>* Map::getCountries() const {
	return countries;
}

//returns a string with the names of the continents of the map, seperated by a space
string Map::getContinentNames() const {
	if (numContinents > 0) {
		string names = "";
		for (int i = 0; i < numContinents; i++)
			names += ((*continents)[i])->getName() + " ";
		return names;
	}
	else
		return "No continents";
}

//returns a string with the names of the countries of the map, seperated by a space
string Map::getCountryNames() const {
	if (numCountries > 0) {
		string names = "";
		for (int i = 0; i < numCountries; i++)
			names += ((*countries)[i])->getName() + " ";
		return names;
	}
	else
		return "No countries";
}

bool Map::getIsConnected(){
	//before returning isConnected, perform a check
	setIsConnected(checkIsConnected());
	return isConnected;
}

bool Map::getContinentsValid() {
	setContinentsValid(checkContinentsValid());
	return continentsValid;
}

string Map::getType() {
	return type;
}

void Map::setType(string s) {
	type = s;
}

void Map::setContinentsValid(bool b) {
	continentsValid = b;
}

//this set should only be called by getIsConnected
void Map::setIsConnected(bool b) {
	isConnected = b;
}

//setting the names of the countries of the map
void Map::setCountryNames() {
	string n = "";
	if (numCountries > 0) {
		for (int i = 0; i < numCountries; i++) {
			cout << "Country" << (i+1) << " : ";
			cin >> n;
			((*countries)[i])->setName(n);
		}
	}
	else
		cout << "No continents" << endl;
}

//setting the names of the continents of the map
void Map::setContinentNames() {
	string n = "";
	if (numContinents > 0) {
		for (int i = 0; i < numContinents; i++) {
			cout << "Continent" << (i+1) << " : ";
			cin >> n;
			((*continents)[i])->setName(n);
		}
	}
	else
		cout << "No continents" << endl;
}


//adding a continent to the map (should only be called at the initialization of the map)
void Map::addContinent(Continent* c) {
	continents->push_back(c);
}

//adding a conutry to the map (should only be called at the initialization of the map)
void Map::addCountry(Country* c) {
	countries->push_back(c);
}

//Preconditon: valid id numbers only
//This is a helper method mainly for the purpose of the demo
void Map::printContinentsCountries(int n) {
	cout << "The following countries belong to " << (*continents)[n - 1]->getName() << ": ";
	cout << (*continents)[n - 1]->getCountryNames() << " "<< endl;
}
