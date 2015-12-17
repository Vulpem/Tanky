#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
class Tower
{
public:
	Tower();
	Tower(float x, float z, float height = 10, float cubeSize = 1)
	{
		startPosition.x = x;
		startPosition.y = 0;
		startPosition.z = z;
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < 4; w++)
			{
				Cube* cube = new Cube(cubeSize, cubeSize, cubeSize);
				float offsetX = 0;
				float offsetZ = 0;
				if (w == 1 || w == 3)
					offsetX = cubeSize;
				if (w > 1)
					offsetZ = cubeSize;

				float x = startPosition.x + offsetX;
				float y = startPosition.y + h * cubeSize;
				float z = startPosition.z + offsetZ;
				cube->SetPos(x, y, z);
				cubes.PushBack(cube);
			}
		}
		/*
		column.size.x = cubeSize;
		column.size.y = cubeSize;
		column.size.z = cubeSize;
		column.SetPos(x, (height/2), z);
		*/
		
	}
	void Update()
	{
		for (int i = 0; i < cubes.Count(); i++)
		{
			cubes[i]->Render();
		}
		/*
		float x, y, z;
		
		pb->GetPos(&x, &y, &z);
		float difX = startPosition.x - x;
		float difY = startPosition.y - y;
		float difZ = startPosition.z - z;
		if (difX < -0.2f || 0.2f < difX || difY < -0.2f || 0.2f < difY || difZ < -0.2f || 0.2f < difZ)
		{
			if (pb->isResting())
			{
				fallen = true;
				column.color = { 0.5f, 0, 0 };
			}
		}
		column.Render();
		*/
		
	}

public:
	p2DynArray<Cube*> cubes;
	p2DynArray<PhysBody3D*> pbs;

	vec3 startPosition;
	bool fallen = false;
};
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	Cube s;
	Tower* tower = NULL;
	PhysBody3D* sensor;
};
