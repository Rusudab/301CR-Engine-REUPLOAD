#include "ReadWriteJSON.h"

using json = nlohmann::json;

/*
	This is method that saves all of my game objects into the file called "objects.JSON"
*/
void ReadWriteJSON::JSONsaving()
{
	if (GameObject::gameobjs.size() > 0)
	{
		std::string savePath = "objects.JSON";

		json saveFiles;

		saveFiles["GameObjNo"] = GameObject::gameobjs.size();

		for (int i = 0; i < GameObject::gameobjs.size(); i++)
		{
			vector <float> temparr = { GameObject::gameobjs[i]->pos.x, GameObject::gameobjs[i]->pos.y, GameObject::gameobjs[i]->pos.z };
			vector <float> tempvec = { GameObject::gameobjs[i]->colliderSize.x, GameObject::gameobjs[i]->colliderSize.y, GameObject::gameobjs[i]->colliderSize.z };
			vector <float> temprot = { GameObject::gameobjs[i]->rot.x, GameObject::gameobjs[i]->rot.y, GameObject::gameobjs[i]->rot.z };

			saveFiles["GameObjects"][i]["isRigidbody"] = { GameObject::gameobjs[i]->isRigidbody };
			saveFiles["GameObjects"][i]["name"] = { GameObject::gameobjs[i]->name };
			saveFiles["GameObjects"][i]["mass"] = { GameObject::gameobjs[i]->mass };
			saveFiles["GameObjects"][i]["position"] = { temparr };
			saveFiles["GameObjects"][i]["rotation"] = { temprot };
			saveFiles["GameObjects"][i]["mesh path"] = { GameObject::gameobjs[i]->meshpath };
			saveFiles["GameObjects"][i]["texture path"] = { GameObject::gameobjs[i]->texpath };
			saveFiles["GameObjects"][i]["collider type"] = { GameObject::gameobjs[i]->coltype };
			saveFiles["GameObjects"][i]["sphere radius"] = { GameObject::gameobjs[i]->sphereRadius };
			saveFiles["GameObjects"][i]["collider size"] = { tempvec };
		}

		std::ofstream out(savePath);

		out << std::setw(4) << saveFiles << endl;
	}

}

/*
	This is the method that loads all of the game objects from "objects.JSON" file
*/
void ReadWriteJSON::JSONreading()
{
	std::string loadPath = "objects.JSON";

	std::ifstream in(loadPath);

	json loadFiles = json::parse(in);

	int size = loadFiles["GameObjNo"].get<int>();

	for (int i = 0; i < size; i++)
	{
		GameObject* newgo = new GameObject(
			loadFiles["GameObjects"][i]["isRigidbody"][0],
			loadFiles["GameObjects"][i]["name"][0],
			loadFiles["GameObjects"][i]["mass"][0],
			UVec3(loadFiles["GameObjects"][i]["position"][0][0], loadFiles["GameObjects"][i]["position"][0][1], loadFiles["GameObjects"][i]["position"][0][2]),
			UVec3(loadFiles["GameObjects"][i]["rotation"][0][0], loadFiles["GameObjects"][i]["rotation"][0][1], loadFiles["GameObjects"][i]["rotation"][0][2]),
			loadFiles["GameObjects"][i]["mesh path"][0],
			loadFiles["GameObjects"][i]["texture path"][0],
			loadFiles["GameObjects"][i]["collider type"][0],
			loadFiles["GameObjects"][i]["sphere radius"][0],
			UVec3(loadFiles["GameObjects"][i]["collider size"][0][0], loadFiles["GameObjects"][i]["collider size"][0][1], loadFiles["GameObjects"][i]["collider size"][0][2])
		);
	}
}
