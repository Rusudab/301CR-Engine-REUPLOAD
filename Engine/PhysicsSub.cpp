#include "PhysicsSub.h"

btDynamicsWorld* PhysicsSub::world;

bool PhysicsSub::isColliding;

PhysicsSub::PhysicsSub()
{
	 
}

PhysicsSub::~PhysicsSub()
{
	delete solver;
	delete broadPhase;
	delete collDispatch;
	delete collConfig;
}

void PhysicsSub::PhysicsSetup()
{
	world = new btDiscreteDynamicsWorld(collDispatch, broadPhase, solver, collConfig);
	btVector3 gravityValue(0, -9.8f, 0); //gravity value for the scene
	world->setGravity(gravityValue); //setting the gravity value for the world
	isColliding = false;
}

// The Delta Time is being calculated using the chrono library in the MainEngine.cpp file
void PhysicsSub::PhysicsUpdate(float deltaTime)
{
	world->stepSimulation(deltaTime, 1); //use the delta time - hard coded at the top
}

// This is the function that is being called in MainEngine.cpp file in order to attach rigid bodies id to game object ids
int PhysicsSub::AttachCollider(btRigidBody* rigid)
{
	world->addRigidBody(rigid);
	return world->getNumCollisionObjects()-1;
}

// This is where we move the player game object based on the camera's rotation, position, and target
void PhysicsSub::RigidbodyMovement(char key, btRigidBody* rig, UVec3 head, UVec3 headleft)
{
	switch (key)
	{
		case 'w':
		{
			btVector3 fwvec3 = btVector3(head.x, head.y, head.z)*3.1f;

			rig->activate(true);
			rig->applyForce(fwvec3, btVector3(0.0, 0.0, 0.0));
		}
		break;

		case 'a':
		{
			btVector3 leftvec3 = btVector3(headleft.x, headleft.y, headleft.z)*3.1f;

			rig->activate(true);
			rig->applyForce(leftvec3, btVector3(0.0, 0.0, 0.0));
		}

		break;

		case 'd':
		{
			btVector3 rightvec3 = btVector3(-headleft.x, -headleft.y, -headleft.z)*3.1f;

			rig->activate(true);
			rig->applyForce(rightvec3, btVector3(0.0, 0.0, 0.0));
		}

		break;

		case 's':
		{
			btVector3 backvec3 = btVector3(-head.x, -head.y, -head.z)*3.1f;

			rig->activate(true);
			rig->applyForce(backvec3, btVector3(0.0, 0.0, 0.0));
		}

		break;
	}
}

// This is where we check to see if the game object is colliding with the endbox
void PhysicsSub::CheckCollision(int obj1, int obj2)
{
	int manifolds = world->getDispatcher()->getNumManifolds();

	for (int i = 0; i < manifolds; i++)
	{
		btPersistentManifold* contact = world->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obj = contact->getBody0();
		
		if (obj->getWorldArrayIndex() == obj1 || obj->getWorldArrayIndex() == obj2)
		{
			isColliding = true;
		}
		else
		{
			isColliding = false;
		}
	}
}
