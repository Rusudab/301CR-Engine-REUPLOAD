#pragma once

#include "btBulletDynamicsCommon.h"
#include "UVec3.h"

#include <iostream>

/*
	This is my own rigidbody class that is being used to communicate between the game objects and the physics subsystem
*/

class URigidBody
{
public:

	URigidBody();
	URigidBody(UVec3 transform, UVec3 coll, std::string coltype, float rad, float mass);
	~URigidBody();

	int rigidbodyid;

	btRigidBody* bulletRigidBody;
	btTransform transform;
	btMotionState* motion;
	btCollisionShape* collshape;

};