#pragma once

#include <nlohmann/json.hpp>

#include "GameObject.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

/*
	For the data-driven element of this engine, I have decided to use nlohmann's JSON
	The sole reason why I decided against using LUA is because I wanted to create my game objects in code first
	I didn't want to write in a .lua file any new Game Objects, with JSON, I have created 2 methods (look into ReadWriteJSON.cpp to see more)
	With JSON I have managed to load and save all of my game objects.

	NOTE: The objects inside the "objects.JSON" file can still be edited.
*/

class ReadWriteJSON
{
public:

	void JSONsaving();

	void JSONreading();
};

