#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Tower.h"

struct PhysBody3D;
struct PhysMotor3D;
class Tower;

class ModuleScene9 : public ModuleScene
{
public:
	ModuleScene9(Application* app, bool start_enabled = true);

	void LoadPositions();
};
