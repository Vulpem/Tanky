#pragma once

#include "Primitive.h"
#include "PhysBody3D.h"
#include "Application.h"
#include "ModulePhysics3D.h"

class Tower
{
public:
	Tower();
	Tower(float x, float z, float height = 10, float cubeSize = 1);
	void Update();

	bool isDestroyed();
	void ChangeColor(Color);


public:
	p2DynArray<Cube*> cubes;
	p2DynArray<PhysBody3D*> pbs;
	p2DynArray<vec3> positions;

	bool fallen = false;
};
