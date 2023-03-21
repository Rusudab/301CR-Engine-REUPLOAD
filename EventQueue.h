#pragma once

#include <iostream>

#include <vector>

#include "GraphicsSub.h"
#include "PhysicsSub.h"
#include "InputSub.h"
#include "Event.h"
#include "AudioSub.h"
#include "GameObject.h"
#include "Networking.h"

#include "UVec3.h"
#include "URigidBody.h"
#include "UNode.h"

using namespace std;

/*
	This is my Event Queue class, I have it designed so this is the brains of the Events, most events go through here first.
*/

class EventQueue
{
public:

	EventQueue();
	~EventQueue();

/*
	This is my actual physical queue, where I created a vector of Events,
	while this queue is populated, the events inside it will always be executed
*/
	static vector <Event> queue;

	//These 2 variables were used for the shutdown and to show the fps respectively
	bool shutdown = false;
	bool showfps = false;

	void EventUpdate();

	void AddEvent(Event event);

	void CheckCollider();

};

