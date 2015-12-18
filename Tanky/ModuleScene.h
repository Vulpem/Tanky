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

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	virtual void LoadPositions();
	void LoadTowers();
	void CheckTowersNumbers();

	void ResetScene();
	void LoadNextScene();

	void SetNextScene(ModuleScene* scene);

public:
	int allyTowers = 0;
	int enemyTowers = 0;

	int allyNum;
	int enemyNum;
	int neutralNum;

	vec4* allyPositions = NULL;
	vec4* enemyPositions = NULL;
	vec4* neutralPositions = NULL;

	p2DynArray<Tower*> towers;

	ModuleScene* nextScene;
};