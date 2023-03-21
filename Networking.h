#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>

#include <string>
#include <vector>

/*
	This class was created in order to deal with the networking side of the game engine,
	for it to work, I have created a simple .html file, from which I gather data,
	show it on the screen, as well as upload data to the website.

	NOTE: My design for the website is that it will show you the top 5 high scores at all times
*/

class Networking
{
public:

	// How it works is that I get all of the lines from the website and store them all separately in case the .html file is on multiple lines
	std::vector <std::string> fileLines;

	// The temp variable is being used to go through all of the characters on each line
	std::string temp;

	/* The numbers variable is being used to store only the exact sequence of characters that denote the actual high score value
	   It is being used in order to change the website, when the player uploads a new highscore,
	   as well as being able to show the high scores on screen */
	static std::vector <std::string> numbers;

	/*
		This newNumber variable stores the new highscore of the player, right now, in order to change the high score,
		you need to physically change the number in the code (look into the global space of Networking.cpp),
		but I believe that this is enough in order to get the idea of how this works across*/
	static std::string newNumber;

	// These 2 variables are what allow changes to the highscore table happen
	static int change;
	static bool changedNumbers;

	Networking();
	~Networking();

	void NetworkingInitialise();

	void NetworkingChange();

	void NetworkingUpload();

};