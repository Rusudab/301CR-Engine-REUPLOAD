#pragma once
#include <iostream>
#include <string>

#include "UVec3.h"
#include "UNode.h"
#include "URigidBody.h"

#include "GraphicsSub.h"
#include "PhysicsSub.h"
#include "AudioSub.h"

/*
	This is my Game Object class, with which I can create new game objects.
	I have made this class so that if a user wanted to, he could create a game object with or without a mesh and with or without physics properties.
	
	If the user decides to use a mesh for his game object, then he will automatically use my own node class,
	which is an intermediary between the game object and the irrlicht node system. (see UNode.h for more info)

	If the user decides that the game object needs to have a rigidbody and collision properties, then he will automatically use my class,
	which created a rigidbody for the game object, which acts as an intermediary between the
	game object and the bullet physics system. (see URigidBody.h for more info)

	Everything in my Game Object class is based on my own vector 3 class that I created,
	with this class I can easily convert any bullet vector or irrlicht vector into my own. (see UVec3.h for more info)
*/

class GameObject
{
public:

	GameObject();
	~GameObject();

	bool isRigidbody = false;

	UVec3 pos;
	UVec3 rot;
	UVec3 colliderSize;
	static UVec3 cameraRot;
	static UVec3 cameraHeading;
	static UVec3 cameraHeadingLeft;
	
	int index;
	static int playerindex;
	static int endindex;

	float mass;
	float sphereRadius;
	float sphereAnimation = 0.005f;
	float sphereRotation = 0.2f;

	std::string name;
	std::string meshpath;
	std::string texpath;
	std::string coltype;

	URigidBody* rigidbody;
	UNode* unode;

	static std::vector <GameObject*> gameobjs;

	/*
	* This is my Game Object constructor, any game object is populated in the following order:
	* 
	* 1. Is it a rigidbody? (bool)
	* 2. What is its name? (std::string)
	* 3. What is its mass? (float)
	* 4. What is its position? (UVec3)
	* 5. What is its rotation? (UVec3)
	* 6. What is the mesh's path (if it has one)? (std::string)
	* 7. What is the texture's path (if it has one)? (std::string)
	* 8. What is its collider type (if it has one)? (std::string)
	* 9. What is the radius of the sphere collider (if it has one/ if it even is a sphere)? (float)
	* 10. What is the size of the box collider (if it has one/ if it even is a box)? (UVec3)
	*/

	GameObject(bool isRigidbody, 
			std::string name, 
			float mass = 0, 
			UVec3 pos = 0,
			UVec3 rot = 0,
			std::string mpath = 0, 
			std::string tpath = 0, 
			std::string colpath = 0, 
			float radius = 0, 
			UVec3 colliderSize = 0);

	// These 2 methods are only going to be called if the game object either has a mesh or if it is a rigid body
	void AddRigidBody(UVec3 pos, UVec3 colliderSize, std::string collidertype, float rad, float mass);
	void AttachMesh(std::string mp, std::string tp);

	// This is the method that updates all of the game objects
	void GameObjectUpdate();

	// These 3 methods are regarding the player game object, which can be initialized by naming a game object "player"
	static void PlayerMovement(char key);
	void PlayerCameraRotation();
	void PlayerSound();
};