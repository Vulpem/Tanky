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

class ModuleScene1 : public ModuleScene
{
public:
	ModuleScene1(Application* app, bool start_enabled = true);

	void LoadPositions();
};
