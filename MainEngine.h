#pragma once

#include "ReadWriteJSON.h"

// The chrono library is being used to calculate delta time in my main engine
#include <chrono>

#include "GraphicsSub.h"
#include "PhysicsSub.h"
#include "InputSub.h"
#include "EventQueue.h"
#include "GameObject.h"
#include "AudioSub.h"
#include "Networking.h"

#include "UVec3.h"
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;

/*
	Brief summary of the subsystems used:
	
	Physics - Bullet 3.17
	Graphics - Irrlicht 1.8.4 
	Audio - OpenAL soft; AudioFile (for importing .wav files)
	Input - SFML 2.5.1
*/

// This is my main engine class, this is where I include all of the subsystems, their initialization and their update methods

class MainEngine
{
public:

	MainEngine();
	~MainEngine();

	void update();

	//One variable for each subsystem needed here
	GraphicsSub graph;
	PhysicsSub phys;
	InputSub input;
	AudioSub audio;
	EventQueue eventQ;
	Event test;
	ReadWriteJSON js;
	Networking net;

	Clock::time_point OldTime; //time of previous frame

	Clock::time_point CurrentTime; //current time

	Clock::duration DeltaTime; //change in time between frames

	void Initialise(int sizeX, int sizeY);

	//This method is where I apply the different rigidbodies and meshes ids to their particular game object
	void LoadingGameObjsIds();

};