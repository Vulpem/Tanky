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
	Tower(float x, float z, int width, float height)
	{
		startPosition.x = x;
		startPosition.y = height / 2;
		startPosition.z = z;
		column.size.x = width;
		column.size.y = height;
		column.size.z = width;
		column.SetPos(x, (height/2), z);
		
	}
	void Update()
	{
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
		
	}

public:
	Cube column;
	PhysBody3D* pb;

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
