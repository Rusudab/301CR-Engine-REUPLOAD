#pragma once

#include "btBulletDynamicsCommon.h"

#include "Event.h"
#include "Uvec3.h"

#include <iostream>

/*
For the physics subsystem I have used Bullet, I have based my physics subsystem on the example Ian provided for 217CR module from our second year
Example which was heavily modified in order to suit my needs, but the very basic initialization of variables is still here
*/

class PhysicsSub
{
public:

	PhysicsSub();
	~PhysicsSub();

	// These are the basic variables that we need in order to use bullet
	static btDynamicsWorld* world; //the primary control of all the physics objects in the scene, defining how they move when simulated
	btBroadphaseInterface* broadPhase = new btDbvtBroadphase(); //Collision Detection part of the simulation - optimized detection using 2 dynamic AABB bounding volume trees (1 for static objects, 1 for dynamic objects)
	btCollisionConfiguration* collConfig = new btDefaultCollisionConfiguration(); //Default memory allocation, collision algorithms and data output on collisions (aka Bullet can handle it for us behind the scenes)
	btCollisionDispatcher* collDispatch = new btCollisionDispatcher(collConfig); //Algorithms that handle collision pairs, using configuration above
	btConstraintSolver* solver = new btSequentialImpulseConstraintSolver(); //Collision Resolution part of the simulation - Solver used to make objects respond to objects

	int rigidbodyid;

	static bool isColliding;

	// We need these variables in order to create rigid bodies
	btRigidBody* rigb;
	btTransform transform;
	btMotionState* motion;
	btCollisionShape* collshape;

	void PhysicsSetup();
	void PhysicsUpdate(float deltaTime);

	int AttachCollider(btRigidBody* rigid);

	static void RigidbodyMovement(char key, btRigidBody* rig, UVec3 head, UVec3 headright);

	static void CheckCollision(int obj1, int obj2);
};