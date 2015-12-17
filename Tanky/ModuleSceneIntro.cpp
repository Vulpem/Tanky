#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

//	floor = Cube(50, 0.2f, 50);
//	App->physics->AddBody(floor);
	LoadTowers();
	LOG("%i", allyTowers);
	LOG("%i", enemyTowers);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	floor.Render();

	for (int i = 0; i < towers.Count(); i++)
	{
		if (towers[i]->Update() == false)
		{
			if (towers[i]->type == TOWER_ALLY)
			{
				allyTowers--;
				CheckTowersNumbers();
			}

			else if (towers[i]->type == TOWER_ENEMY)
			{
				enemyTowers--;
				CheckTowersNumbers();
			}

		}
	}

	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
//	LOG("Hit!");
}

void ModuleSceneIntro::LoadTowers()
{
	//Towers Positions
	neutralPositions = new vec4[10];
	neutralPositions[0] = { 1, 0, 1, 3};
	neutralPositions[1] = { 3, 0, 1, 3};
	neutralPositions[2] = { 5, 0, 1, 3};
	neutralPositions[3] = { 7, 0, 1, 3};
	neutralPositions[4] = { 9, 0, 1, 3};
	neutralPositions[5] = { -1, 0, 1, 3};
	neutralPositions[6] = { -3, 0, 1, 3};
	neutralPositions[7] = { -5, 0, 1, 3};
	neutralPositions[8] = { -7, 0, 1, 3};
	neutralPositions[9] = { -9, 0, 1, 3};
	//Allies
	for (int i = 0; i < 10; i++)
	{
		Tower* tower = new Tower(5 * i - 20, 0, 5 * i + 0, TOWER_ALLY, 5, 2);
		for (int i = 0; i < tower->cubes.Count(); i++)
		{
			tower->pbs.PushBack(App->physics->AddBody(*tower->cubes[i]));
			tower->pbs[i]->SetInactive();
		}
		towers.PushBack(tower);
		allyTowers++;
	}

	//Enemies
	
	for (int i = 0; i < 10; i++)
	{
		Tower* tower = new Tower(5 * i - 20, 0, 5 * i + 10, TOWER_ENEMY, 5);
		for (int i = 0; i < tower->cubes.Count(); i++)
		{
			tower->pbs.PushBack(App->physics->AddBody(*tower->cubes[i]));
			tower->pbs[i]->SetInactive();
		}
		towers.PushBack(tower);
		enemyTowers++;
	}
	
	//Neutrals

	for (int i = 0; i < 10; i++)
	{
		Tower* tower = new Tower((int)neutralPositions[i].x, (int)neutralPositions[i].y, (int)neutralPositions[i].z, TOWER_NEUTRAL, neutralPositions[i].w);
		for (int i = 0; i < tower->cubes.Count(); i++)
		{
			tower->pbs.PushBack(App->physics->AddBody(*tower->cubes[i], 0.0f));
			tower->pbs[i]->SetInactive();
		}
		towers.PushBack(tower);
	}
}

void ModuleSceneIntro::CheckTowersNumbers()
{
	LOG("Ally towers: %i", allyTowers);
	LOG("Enemy towers: %i", enemyTowers);
	if (allyTowers == 0)
	{
		LOG("YOU LOOSE");
	}
	else if (enemyTowers == 0)
	{
		LOG("YOU WIN!");
	}
}

