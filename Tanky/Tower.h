#pragma once

#include "Primitive.h"
#include "p2DynArray.h"
#include "PhysBody3D.h"
#include "Application.h"

class Tower
{
public:
	Tower();
	Tower(float x, float z, float height = 10, float cubeSize = 1);
	void Update();


public:
	p2DynArray<Cube*> cubes;
	p2DynArray<PhysBody3D*> pbs;

	vec3 startPosition;
	bool fallen = false;
};
