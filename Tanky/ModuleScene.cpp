#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Primitive.h"
#include "PhysBody3D.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	LoadTowers();
	LOG("%i", allyTowers);
	LOG("%i", enemyTowers);
	return ret;
}

// Load assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading Intro scene");
	if (neutralPositions)
	{
		delete[] neutralPositions;
		neutralPositions = NULL;
	}

	if (enemyPositions)
	{
		delete[] enemyPositions;
		enemyPositions = NULL;
	}

	if (allyPositions)
	{
		delete[] allyPositions;
		allyPositions = NULL;
	}LOG("Unloading Intro scene");
	for (int i = 0; i < towers.Count(); i++)
	{
		for (int j = 0; j < towers[i]->cubes.Count(); j++)
		{
			delete towers[i]->cubes[j];
			App->physics->DeleteBody(towers[i]->pbs[j]);
		}
		towers[i]->cubes.Clear();
	}
	towers.Clear();
	return true;
}

// Update
update_status ModuleScene::Update(float dt)
{
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

	Plane p(0, 0, 0, 1);
	p.axis = true;
	p.color = Color{ 1, 1, 1, 1 };
	p.Render();


	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}

void ModuleScene::LoadPositions()
{}
void ModuleScene::LoadTowers()
{
	LoadPositions();
	//Allies
	for (int i = 0; i < allyNum; i++)
	{
		Tower* tower = new Tower((int)allyPositions[i].x, (int)allyPositions[i].y, (int)allyPositions[i].z, TOWER_ALLY, allyPositions[i].w);
		for (int i = 0; i < tower->cubes.Count(); i++)
		{
			tower->pbs.PushBack(App->physics->AddBody(*tower->cubes[i]));
			tower->pbs[i]->SetInactive();
		}
		towers.PushBack(tower);
		allyTowers++;
	}
	if (allyPositions)
	{
		delete[] allyPositions;
		allyPositions = NULL;
	}
	//Enemies

	for (int i = 0; i < enemyNum; i++)
	{
		Tower* tower = new Tower((int)enemyPositions[i].x, (int)enemyPositions[i].y, (int)enemyPositions[i].z, TOWER_ENEMY, enemyPositions[i].w);
		for (int i = 0; i < tower->cubes.Count(); i++)
		{
			tower->pbs.PushBack(App->physics->AddBody(*tower->cubes[i]));
			tower->pbs[i]->SetInactive();
		}
		towers.PushBack(tower);
		enemyTowers++;
	}

	delete[]enemyPositions;
	enemyPositions = NULL;
	//Neutrals

	for (int i = 0; i < neutralNum; i++)
	{
		Tower* tower = new Tower((int)neutralPositions[i].x, (int)neutralPositions[i].y, (int)neutralPositions[i].z, TOWER_NEUTRAL, neutralPositions[i].w);
		for (int i = 0; i < tower->cubes.Count(); i++)
		{
			tower->pbs.PushBack(App->physics->AddBody(*tower->cubes[i], 0.0f));
			tower->pbs[i]->SetInactive();
		}
		towers.PushBack(tower);
	}

	delete[]neutralPositions;
	neutralPositions = NULL;
}

void ModuleScene::CheckTowersNumbers()
{
	LOG("Enemy towers: %i", enemyTowers);

	LOG("Ally towers: %i", allyTowers);

	if (allyNum > 0)
	{
		if (allyTowers == 0)
		{
			ResetScene();
		}
	}

	else if (enemyTowers == 0)
	{
		LoadNextScene();
	}
}


void ModuleScene::ResetScene()
{
	App->camera->Disable();
	App->player->Disable();
	this->Disable();
	this->Enable();
	App->player->Enable();
	App->camera->Enable();
}
void ModuleScene::LoadNextScene()
{
	App->camera->Disable();
	App->player->Disable();
	this->Disable();
	nextScene->Enable();
	App->player->Enable();
	App->camera->Enable();
}

void ModuleScene::SetNextScene(ModuleScene* scene)
{
	nextScene = scene;
}

