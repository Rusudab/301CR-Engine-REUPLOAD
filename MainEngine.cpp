#include "MainEngine.h"

MainEngine::MainEngine()
{
}

// With the main engine deconstructor, I deconstrut all of the game objects and their rigid bodies
MainEngine::~MainEngine()
{
	for (int i = 0; i < GameObject::gameobjs.size(); i++)
	{
		if (GameObject::gameobjs[i]->rigidbody != 0)
		{
			btRigidBody* body = GameObject::gameobjs[i]->rigidbody->bulletRigidBody;
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
				delete body;
			}
		}
		delete GameObject::gameobjs[i];
	}
}

/*	The shutdown of the engine starts from here, and it is based on a boolean variable called shutdown, which is based in the Event Queue class.
If we press ESC (You can see all the controls from the controls GUI on the bottom right of the game engine's window) then this variable shuts off
and the loop will stop, after this loop stops, we go to the last line in our src.cpp file which then prompts the deconstructor of each class.
*/
void MainEngine::update()
{
	while (!eventQ.shutdown)
	{
		//This is how the delta time is calculated, then it is passed into the physics update
		OldTime = CurrentTime;
		CurrentTime = Clock::now();
		DeltaTime = CurrentTime - OldTime;

		graph.GraphicsUpdate();
		phys.PhysicsUpdate((DeltaTime).count() * 0.0000001f);
		input.InputUpdate();
		eventQ.EventUpdate();

		//This checks to see if we want the audio to be played or not
		audio.PlayPlayerSound();

		//This checks to see if we pressed a button in order to demonstrate the uploading of data to a website
		net.NetworkingChange();

		//This checks to see if the player has pressed the showFPS button
		if (eventQ.showfps)
		{
			graph.ShowFPS(int(1 / (DeltaTime.count()* 0.000000001f)));
		}
		else
		{
			graph.ResetFPS();
		}

		for (int i = 0; i < GameObject::gameobjs.size(); i++)
		{
			GameObject::gameobjs[i]->GameObjectUpdate();
		}
	}
}

//This is the method that calls all of the other subsystems initialization methods
void MainEngine::Initialise(int sizeX, int sizeY)
{
	net.NetworkingInitialise();
	graph.GraphicsSetup(sizeX, sizeY);

	js.JSONreading();

	//This is how I used to create my game objects
	/*GameObject* obj = new GameObject(true, "plain", 0.0f, UVec3(0.0f, -100.0f, 0.0f), UVec3(0.0f, 0.0f, 0.0f), meshp, texp, ctpplain, 3.0f, UVec3(32.0f, 32.0f, 32.0f));
	GameObject* obj1 = new GameObject(true, "player", 1.0f, UVec3(0.0f, 0.0f, 15.0f), UVec3(0.0f, 0.0f, 0.0f), "", "", ctpplayer, 1.0f, UVec3(1.0f, 1.0f, 1.0f));
	GameObject* obj2 = new GameObject(true, "endbox", 0.3f, UVec3(20.0f, 0.0f, 0.0f), UVec3(0.0f, 0.0f, 0.0f), meshsphere, texsphere, ctpsphere, 0.0f, UVec3(3.2f, 3.2f, 3.2f));
	GameObject* obj3 = new GameObject(false, "sphereanim", 0.0f, UVec3(20.0f, -65.0f, 15.0f), UVec3(0.0f, 0.0f, 0.0f), "models/sphere.obj", "textures/spheretex.jpg", "", 0.0f, UVec3(0.0f, 0.0f, 0.0f));*/

	phys.PhysicsSetup();
	LoadingGameObjsIds();
	audio.AudioInitialise();

	js.JSONsaving();

	CurrentTime = Clock::now();
	update();
}

void MainEngine::LoadingGameObjsIds()
{
	for (int i = 0; i < GameObject::gameobjs.size(); i++)
	{
		if (GameObject::gameobjs[i]->isRigidbody == true)
		{
			GameObject::gameobjs[i]->rigidbody->rigidbodyid = phys.AttachCollider(GameObject::gameobjs[i]->rigidbody->bulletRigidBody);
		}
		if (GameObject::gameobjs[i]->unode != nullptr)
		{
			GameObject::gameobjs[i]->unode->nodeid = graph.AddMesh(GameObject::gameobjs[i]->unode, GameObject::gameobjs[i]->unode->mpath, GameObject::gameobjs[i]->unode->tpath);
		}
	}
}