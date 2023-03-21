#pragma once

#include <nlohmann/json.hpp>

#include "GameObject.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using json = nlohmann::json;

namespace parsing {

	void JSONsaving()
	{
		std::string savePath = ".JSON";

		json saveFiles;

		saveFiles["GameObjNo"] = GameObject::gameobjs.size();

		for (int i = 0; i < GameObject::gameobjs.size(); i++)
		{
			saveFiles["GameObjects"][i]["isRigidbody"] = { GameObject::gameobjs[i]->isRigidbody };
			saveFiles["GameObjects"][i]["name"] = { GameObject::gameobjs[i]->name };
			saveFiles["GameObjects"][i]["mass"] = { GameObject::gameobjs[i]->mass };
			saveFiles["GameObjects"][i]["position x"] = { GameObject::gameobjs[i]->pos.x };
			saveFiles["GameObjects"][i]["position y"] = { GameObject::gameobjs[i]->pos.y };
			saveFiles["GameObjects"][i]["position z"] = { GameObject::gameobjs[i]->pos.z };
			saveFiles["GameObjects"][i]["mesh path"] = { GameObject::gameobjs[i]->unode->mpath };
			saveFiles["GameObjects"][i]["texture path"] = { GameObject::gameobjs[i]->unode->tpath };
			saveFiles["GameObjects"][i]["collider type"] = { GameObject::gameobjs[i]->coltype };
			saveFiles["GameObjects"][i]["sphere radius"] = { GameObject::gameobjs[i]->sphereRadius };
			saveFiles["GameObjects"][i]["collider size x"] = { GameObject::gameobjs[i]->colliderSize.x };
			saveFiles["GameObjects"][i]["collider size y"] = { GameObject::gameobjs[i]->colliderSize.y };
			saveFiles["GameObjects"][i]["collider size z"] = { GameObject::gameobjs[i]->colliderSize.z };
		}

		std::ofstream out(savePath);

		out << std::setw(6) << savePath << endl;

	}

	void JSONreading()
	{
		std::string loadPath = ".JSON";

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
				loadFiles["GameObjects"][i]["mesh path"][0],
				loadFiles["GameObjects"][i]["texture path"][0],
				loadFiles["GameObjects"][i]["collider type"][0],
				loadFiles["GameObjects"][i]["sphere radius"][0],
				UVec3(loadFiles["GameObjects"][i]["collider size"][0][0], loadFiles["GameObjects"][i]["collider size"][0][1], loadFiles["GameObjects"][i]["collider size"][0][2])
			);
		}
	}

}