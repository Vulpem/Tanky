#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Tower.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
class Tower;

class ModuleScene1 : public Module
{
public:
	ModuleScene1(Application* app, bool start_enabled = true);
	~ModuleScene1();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void LoadTowers();
	void CheckTowersNumbers();

public:
	int allyTowers = 0;
	int enemyTowers = 0;

	vec4* allyPositions;
	vec4* enemyPositions;
	vec4* neutralPositions;

	p2DynArray<Tower*> towers;
};
