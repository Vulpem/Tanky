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
	timer.Start();
	timer.Stop();
	loadNext = false;
	LoadTowers();
	//LOG("%i", allyTowers);
	//LOG("%i", enemyTowers);
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
	}
	
	for (int i = 0; i < towers.Count(); i++)
	{
		for (int j = 0; j < towers[i]->cubes.Count(); j++)
		{
			delete towers[i]->cubes[j];
			App->physics->DeleteBody(towers[i]->pbs[j]);
		}
		towers[i]->cubes.Clear();
		delete towers[i];
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

	if (ended && timer.Read() > 4 * 1000)
	{
		if (allyNum > 0 && allyTowers < allyNum)
		{
			reset = true; 
		}
		else if (enemyTowers <= 0)
		{
			loadNext = true;
		}
	}
	
	Plane p(0, 0, 0, 1);
	p.axis = true;
	p.Render();


	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt)
{
	if (reset)
	{
		ResetScene();
		reset = false;
	}
	if (loadNext)
	{
		LoadNextScene();
		loadNext = false;
	}
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
	char title[80];
	sprintf_s(title, "Tanky, the game!!   Enemies left: %i   Allies: %i", enemyTowers, allyTowers);
	App->window->SetTitle(title);
}

void ModuleScene::CheckTowersNumbers()
{
	char title[164];
	sprintf_s(title, "Tanky, the game!!   Enemies left: %i   Allies: %i", enemyTowers, allyTowers);

	if (enemyTowers == 0)
	{
		if (!ended)
		{
			timer.Start();
			ended = true;
			strcat_s(title, "     ----------  Level complete! :)  ----------");
		}

	}
	else if (allyNum > 0 && ended == false)
	{
		if (allyTowers < allyNum)
		{
			if (!ended)
			{
				timer.Start();
				ended = true;
				strcat_s(title, "     ----------  Ally killed, you lost!  ----------");
				App->audio->PlayFx(App->player->looseMusic);
			}

		}
	}

	App->window->SetTitle(title);

}


void ModuleScene::ResetScene()
{
	App->camera->Disable();
	this->Disable();
	this->Enable();
	App->camera->Enable();

	App->player->Reset();
}
void ModuleScene::LoadNextScene()
{
	App->camera->Disable();
	this->Disable();
	nextScene->Enable();
	App->camera->Enable();

	App->player->Reset();
}

void ModuleScene::SetNextScene(ModuleScene* scene)
{
	nextScene = scene;
}

