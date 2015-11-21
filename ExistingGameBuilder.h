#ifndef EXISTINGGAMEBUILDER_H
#define EXISTINGGAMEBUILDER_H

#include "Game.h"
#include "GameBuilder.h"
#include "SaveLoader.h"



class ExistingGameBuilder : public GameBuilder {

private:
	SaverLoader* saveload;
	Game* builtGame; 

public:
	ExistingGameBuilder(SaverLoader* gameFile);
	void buildMap();
	void buildPlayers();
	void buildState();
	

};


#endif