#include "GameObject.h"

std::vector <GameObject*> GameObject::gameobjs;
UVec3 GameObject::cameraRot;
UVec3 GameObject::cameraHeading;
UVec3 GameObject::cameraHeadingLeft;

int GameObject::playerindex;
int GameObject::endindex;

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	rigidbody->~URigidBody();
}

GameObject::GameObject(bool isrigid, std::string n, float m, UVec3 p, UVec3 r, std::string mp, std::string tp, std::string ct, float rad, UVec3 colls)
{
	name = n;
	mass = m;
	pos = p;
	rot = r;
	meshpath = mp;
	texpath = tp;
	coltype = ct;
	sphereRadius = rad;
	colliderSize = colls;
	rigidbody = nullptr;
	isRigidbody = isrigid;
	if (isRigidbody)
	{
		AddRigidBody(pos, colliderSize, coltype, sphereRadius, mass);
	}
	if (mp.size() > 0)
	{
		AttachMesh(mp, tp);
	}
	index = gameobjs.size();

	// These 2 if statements are being used in the physics in order to see when they collide
	if (name == "player")
	{
		playerindex = gameobjs.size();
	}
	if (name == "endbox")
	{
		endindex = gameobjs.size();
	}

	// This if statement simply sets the rotation of the sphere mesh for the simple animation into my scene
	if (name == "sphereanim")
	{
		this->rot.x = -150.0f;
		this->rot.z = 180.0f;
		this->rot.y = 90.0f;
	}
	gameobjs.push_back(this);
}

// This is how we create a new Rigidbody
void GameObject::AddRigidBody(UVec3 pos, UVec3 colliderS, std::string coltype, float rad, float mass)
{
	rigidbody = new URigidBody(pos, colliderS, coltype, rad, mass);
}

// This is how we attach the mesh that we want to the node 
void GameObject::AttachMesh(std::string mpath, std::string tpath)
{
	unode = new UNode(mpath, tpath);
}

void GameObject::GameObjectUpdate()
{
	// These 2 if statements update the game objects and graphical node position based on the physics
	if (rigidbody != nullptr)
	{
		pos = UVec3::frombtVec3(rigidbody->bulletRigidBody->getWorldTransform().getOrigin());
	}
	if (unode != nullptr)
	{
		unode->node->setPosition(UVec3::toirrVec3(pos));
		unode->node->setRotation(UVec3::toirrVec3(rot));
	}

	// This method gets the camera from Irrlicht and passes it into our player's rotation
	PlayerCameraRotation();
	
	/* This method calls for the Audio subsystems update function, in which I pass in the player's position,
	   so the sound follows the player's position wherever he is
	*/
	PlayerSound();

	// This is where I check to see if the player has hit the endbox
	PhysicsSub::CheckCollision(playerindex, endindex);

	/* This is where I set the camera's position, to that of the players, as well as getting reference points of the camera,
	   that will be used inside my physics subsystem in order to let the player go forward towards the camera's target
	*/
	if (name == "player")
	{
		GraphicsSub::SetCameraPos(pos);
		cameraRot = UVec3(GraphicsSub::GetCameraRot().X, GraphicsSub::GetCameraRot().Y, GraphicsSub::GetCameraRot().Z);
		cameraHeading = UVec3(GraphicsSub::GetHeading().X, GraphicsSub::GetHeading().Y, GraphicsSub::GetHeading().Z);
		cameraHeadingLeft = UVec3(GraphicsSub::GetHeadingLeft().X, GraphicsSub::GetHeadingLeft().Y, GraphicsSub::GetHeadingLeft().Z);
	}

	// In this if statement I just set the position of the sphere animation, as well as its rotation
	if (name == "sphereanim")
	{
		this->pos.y += sphereAnimation;
		if (this->pos.y <= -65.0f)
		{
			sphereAnimation = sphereAnimation * -1.0f;
		}
		else if (this->pos.y >= -62.0f)
		{
			sphereAnimation = sphereAnimation * -1.0f;
		}

		this->rot.y += sphereRotation;
		if (this->rot.y > 359.0f)
		{
			this->rot.y = 0.0f;
		}
	}
}

void GameObject::PlayerMovement(char key)
{
	for (int i = 0; i < gameobjs.size(); i++)
	{
		if (gameobjs[i]->name == "player")
		{
			PhysicsSub::RigidbodyMovement(key, gameobjs[i]->rigidbody->bulletRigidBody, cameraHeading, cameraHeadingLeft);
		}
	}
}

void GameObject::PlayerCameraRotation()
{
	for (int i = 0; i < gameobjs.size(); i++)
	{
		if (gameobjs[i]->name == "player")
		{
			gameobjs[i]->rot = UVec3(GraphicsSub::GetCameraRot().X, GraphicsSub::GetCameraRot().Y, GraphicsSub::GetCameraRot().Z);
		}
	}
}

void GameObject::PlayerSound()
{
	for (int i = 0; i < gameobjs.size(); i++)
	{
		if (gameobjs[i]->name == "player")
		{
			AudioSub::AudioUpdate(gameobjs[i]->pos);
		}
	}
}
