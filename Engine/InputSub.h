#pragma once
#include "SFML\Graphics.hpp"

#include <iostream>

#include "EventQueue.h"

/*
	For the Input subsystem, I used the SFML library, even though the SFML library can do many other things, I only used it for this sole reason
	I went with SFML since I have seen that using it is extremely easy and accessible
*/

class InputSub
{
public:

	InputSub();
	~InputSub();

	void InputUpdate();

};