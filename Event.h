#pragma once

using namespace std;

#include <vector>

/*
	This is my own Event class, which is mostly used in my Event Queue.
	Any event must store a key, the subsystem that the event should correspond to,
	and the event type that this event is
*/

class Event
{
public:

	int subType;
	int eventType;
	char keyPress;

	// These subsystems are going to be used together with each specific event
	enum Subsystems
	{
		INPUT, 
		GRAPHICS, 
		PHYSICS, 
		AUDIO,
		NETWORK
	};
	
	enum EventType
	{
		KEYPRESS, //For the Input subsystem

		SHOWFPS, //For the Graphics subsystem
		DONTSHOWFPS,
		SHOWSCORE, 

		MOVEMENT, //For the Physics subsystem
		COLLIDE,

		PLAYSOUND, //For the Audio subsystem
		DONTPLAYSOUND,

		CHANGESCORE //For Networking
	};

	Event();
	~Event();

	//This is my Event constructor, besides the basic one
	Event(char key, int subsystemType, int evType);
};

