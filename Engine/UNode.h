#pragma once

#include "UVec3.h";
#include "irrlicht.h";

#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
	This is my intermediary node class that is being used between the game objects and the graphics subsystem
	How it works is that each new game object has it's own UNode, which already has one irrlicht scene node,
	to which we add the new path of the mesh and the new path of the textures
*/

class UNode
{
public:

	UNode();
	~UNode();

	UNode(std::string mpath, std::string tpath = 0);

	void AttachNode(IAnimatedMeshSceneNode* nd);

	std::string mpath;
	std::string tpath;

	int nodeid;

	IAnimatedMeshSceneNode* node;
};