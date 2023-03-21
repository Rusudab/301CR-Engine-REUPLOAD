#include "GraphicsSub.h"

using namespace irr;
using namespace std;

// Irrlicht's namespaces
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

std::vector <std::string> GraphicsSub::meshes;
std::vector <std::string> GraphicsSub::textures;

ISceneManager* GraphicsSub::smgr;
irr::core::vector3df GraphicsSub::cameraLook;

bool GraphicsSub::scoreboardOn;

GraphicsSub::GraphicsSub()
{
}

GraphicsSub::~GraphicsSub()
{
	device->drop();
}

// This function is to setup the window of the game, I added those 2 parameters so the window size can be changed at will from main
void GraphicsSub::GraphicsSetup(int sizeX, int sizeY)
{
	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(sizeX, sizeY), 16, false, false, false, 0);

	if (!device)
		cout << "Window setup couldn't complete" << endl;

	// Here we set the caption of the newly opened window
	device->setWindowCaption(L"Game Engine Window");

	// Here we set pointers to our VideoDriver, SceneManager, and GUIEnvironment, so that we don't need to write them down each time
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	smgr->addCameraSceneNodeFPS();

	//These next 3 variables are all part of the GUI initialization, where I just create the background and later on I will activate them at will
	fpstext = guienv->addStaticText(L"", rect<s32>(irr::core::vector2di(1, 1), irr::core::vector2di(50, 10)), false, false, nullptr, 0, true);
	fpstext->setBackgroundColor(SColor(0.0f, 0.0f, 0.0f, 0.0f));

	scoretable = guienv->addStaticText(L"", rect <s32>(irr::core::vector2di(500, 300), irr::core::vector2di(700, 500)), false, false, nullptr, 1, true);
	scoretable->setBackgroundColor(SColor(0.0f, 0.0f, 0.0f, 0.0f));
	scoretable->setTextAlignment(EGUIA_CENTER, EGUIA_UPPERLEFT);

	controls = guienv->addStaticText(controlsText.c_str(), rect<s32>(irr::core::vector2di(1050, 650), irr::core::vector2di(1200, 800)), false, false, nullptr, 2, true);
	controls->setBackgroundColor(SColor(175.0f, 255.0f, 255.0f, 255.0f));
	controls->setTextAlignment(EGUIA_CENTER, EGUIA_UPPERLEFT);

	scoreboardOn = false;

	u32 then = device->getTimer()->getTime();
}

void GraphicsSub::GraphicsUpdate()
{
	if (device->run())
	{
		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		// We get the numbers that need to be displayed each frame so that if something changes, we will have the new values ready
		firstNumber = Networking::numbers[0].c_str();
		secondNumber = Networking::numbers[1].c_str();
		thirdNumber = Networking::numbers[2].c_str();
		fourthNumber = Networking::numbers[3].c_str();
		fifthNumber = Networking::numbers[4].c_str();

		// Here is where we concatenate the strings in order to be able to show the text on screen
		scoreboardText = firstLine + secondLine + firstNumber + thirdLine + secondNumber + fourthLine + thirdNumber + fifthLine + fourthNumber + sixthLine + fifthNumber;

		ShowScoreboard();

		driver->endScene();
	}
}

// This is where we add our game object's node into the graphics, so it can be rendered
int GraphicsSub::AddMesh(UNode* nod, std::string m, std::string t)
{
	meshes.push_back(m);
	textures.push_back(t);

	if (m.size() > 0)
	{
		nod->node = smgr->addAnimatedMeshSceneNode(smgr->getMesh(m.c_str()));
	}

	if (t.size() > 0)
	{
		nod->node->setMaterialTexture(0, driver->getTexture(t.c_str()));
		nod->node->setMaterialFlag(video::EMF_LIGHTING, false);
	}
	return graphindex;
}

// These next 2 methods is where we set on and off the fps GUI
void GraphicsSub::ShowFPS(int fps)
{
	frames++;
	if(frames < 300)
	{
		fpstext->setText(displayText.c_str());
	}
	else if (frames > 300)
	{
		fpstext->setBackgroundColor(SColor(175.0f, 255.0f, 255.0f, 255.0f));
		displayText = GUIFPS + std::to_string(fps).c_str();
		fpstext->setText(displayText.c_str());
		frames = 0;
	}
}
void GraphicsSub::ResetFPS()
{
	fpstext->setBackgroundColor(SColor(0.0f, 0.0f, 0.0f, 0.0f));
	fpstext->setText(L"");
	frames = 0;
}

// This is where we check to see if we have collided with the endbox
void GraphicsSub::ShowScoreboard()
{
	if (scoreboardOn)
	{
		scoretable->setBackgroundColor(SColor(175.0f, 255.0f, 255.0f, 255.0f));
		scoretable->setText(scoreboardText.c_str());
		scoreboardOn = false;
	}
	else if(scoreboardOn == false)
	{
		scoretable->setBackgroundColor(SColor(0.0f, 0.0f, 0.0f, 0.0f));
		scoretable->setText(L"");
	}
}

void GraphicsSub::SetCameraPos(UVec3 pos)
{
	smgr->getActiveCamera()->setPosition(vector3df(pos.x, pos.y, pos.z));
}
irr::core::vector3df GraphicsSub::GetCameraRot()
{
	return smgr->getActiveCamera()->getRotation();
}
irr::core::vector3df GraphicsSub::GetHeading()
{
	cameraLook = (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getPosition()).normalize();
	return (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getPosition()).normalize();
}
irr::core::vector3df GraphicsSub::GetHeadingLeft()
{
	return (cameraLook.crossProduct(smgr->getActiveCamera()->getUpVector())).normalize();
}
