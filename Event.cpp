#include "Event.h"

#include <iostream>

using namespace std;

Event::Event()
{

}

Event::~Event()
{

}

Event::Event(char key, int subsystemType, int evType)
{
	keyPress = key;
	subType = subsystemType;
	eventType = evType;
}