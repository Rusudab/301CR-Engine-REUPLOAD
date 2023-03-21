#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "UNode.h"
#include "UVec3.h"

#include "irrlicht.h"

#include "Event.h"
#include "Networking.h"

using namespace irr;
using namespace std;

// Irrlicht's namespaces
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
	This is my Graphics subsystem, where I create a window, add meshes and textures into my scene and add any kind of GUI
	I have chosen Irrlicht for my graphics since it is very easy to implement and the documentation is incredibly well put together
*/

class GraphicsSub
{
public:

	GraphicsSub();
	~GraphicsSub();

	// My Graphics Setup function initializes everything, it takes 2 int values that allow for the window to change sizes (default 1200x800)
	void GraphicsSetup(int sizeX, int sizeY);
	void GraphicsUpdate();

	int AddMesh(UNode* nod, std::string meshpath, std::string texpath = NULL);

	//These 2 methods are for the FPS GUI in the top left corner
	void ShowFPS(int fps);
	void ResetFPS();

	//This method is for showing the scoreboard GUI whenever you touch the cube
	void ShowScoreboard();

	//This is where the player gets the camera's values
	static void SetCameraPos(UVec3 pos);
	static irr::core::vector3df GetCameraRot();
	static irr::core::vector3df GetHeading();
	static irr::core::vector3df GetHeadingLeft();

	static std::vector <std::string> meshes;
	static std::vector <std::string> textures;

	static bool scoreboardOn;

private:

	int graphindex = 0;

	//These are all basic variables for the graphics setup
	IrrlichtDevice* device = NULL;
	IVideoDriver* driver = NULL;
	static ISceneManager* smgr;
	IGUIEnvironment* guienv = NULL;

	//These are all different GUI elements
	IGUIStaticText* fpstext;
	IGUIStaticText* scoretable;
	IGUIStaticText* controls;

	irr::core::stringw GUIFPS = L"FPS: ";
	irr::core::stringw displayText;

	static irr::core::vector3df cameraLook;

	//This variable is used to show the fps roughly each second without it changing rapidly
	int frames;

	std::string meshpath;
	std::string texpath;

	/*
		These next stringw variables are being used for the scoretable that appears when the player colliders with the endbox
		The reason why I needed these stringw variables is because the setText method from irrlicht does not allow concatenation of strings
		in its function call, therefor, I needed to create different variables for each line, as well as different variables for
		each highscore that I needed to display.
	*/
	irr::core::stringw firstLine = "\n \n The Game Highscores are:";
	irr::core::stringw secondLine = "\n \n 1. ";
	irr::core::stringw thirdLine = "\n 2. ";
	irr::core::stringw fourthLine = "\n 3. ";
	irr::core::stringw fifthLine = "\n 4. ";
	irr::core::stringw sixthLine = "\n 5. ";

	irr::core::stringw firstNumber;
	irr::core::stringw secondNumber;
	irr::core::stringw thirdNumber;
	irr::core::stringw fourthNumber;
	irr::core::stringw fifthNumber;
	
	irr::core::stringw scoreboardText;

	// This is the text that appears in the controls section
	irr::core::stringw controlsText = "\n Controls: \n \n WASD - movement\n Mouse - Camera \n Comma - Start Music \n Fullstop - Stop Music \n M - Uploads new highscore \n F3 - Show FPS \n F4 - Don't show FPS \n \n Collide with the box to see highscores \n \nEsc - Shutdown";

	u32 then;
};