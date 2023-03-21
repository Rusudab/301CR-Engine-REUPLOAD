#include "URigidBody.h"



URigidBody::URigidBody()
{
}
//This constructor creates new bullet rigid bodies based on the collider type stored by the game object
URigidBody::URigidBody(UVec3 trans, UVec3 coll, std::string colltype, float rad, float mass)
{
	//trans == position
	transform.setIdentity();
	transform.setOrigin(btVector3(trans.x, trans.y, trans.z));

	motion = new btDefaultMotionState(transform); // - A btMotionState = tracks motion (taking the btTransform)

	// This is where we check what collider type the game object has
	if (colltype == "sphere")
	{
		collshape = new btSphereShape(rad); // - A btCollisionShape = The volume of the physics object and how it responds to collisions and other shapes (Box, Sphere etc.)
	}
	if (colltype == "box")
	{
		collshape = new btBoxShape(btVector3(coll.x, coll.y, coll.z));
	}

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motion, collshape); 	// - A btRigidBodyConstructionInfo = Mass information(taking btMotionState and btCollisionShape)

	bulletRigidBody = new btRigidBody(rbInfo); // - A btRigidBody = A physics object holding all the information above

	// I have applied some dampening to every rigid body in the scene
	bulletRigidBody->setDamping(btScalar(0.3f), btScalar(0.3f));
}

URigidBody::~URigidBody()
{
}
