#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
class Tower
{
public:
	Tower();
	Tower(float x, float z, int width, int height)
	{
		column.size.x = width;
		column.size.y = height;
		column.size.z = width;
		column.SetPos(x, height/2, z);
	}
	void Update()
	{
		column.Render();
	}

public:
	Cube column;
	PhysBody3D* pb;
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
