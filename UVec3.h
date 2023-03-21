#pragma once

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h";

/*
	This is my own vector 3 class, that is being used in many places, but mainly in the Game Object class
	I have decided to create my own Vector 3 class soon after I started creating the Game Engine,
	because about every other subsystem used a different kind of vector, this acted as a great intermediary between those
*/

class UVec3
{
public:

	~UVec3();

	float x;
	float y;
	float z;

	int xi;
	int yi;
	int zi;

	UVec3(float x = 0.0, float y = 0.0, float z = 0.0);

	void UVec3i(int xi = 0, int yi = 0, int zi = 0);

	static UVec3 frombtVec3(btVector3 vectorbt);

	static btVector3 tobtVec3(UVec3 uvec);

	static UVec3 fromirrVec3(irr::core::vector3df irrvec);

	static irr::core::vector3df toirrVec3(UVec3 uvec);
};
