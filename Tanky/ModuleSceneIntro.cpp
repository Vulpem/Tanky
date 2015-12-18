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
	p.color = Color{ 1, 1, 1 , 1};
	p.Render();
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
//	LOG("Hit!");
}

void ModuleSceneIntro::LoadTowers()
{
	int neutralMax = 58;
	//Towers Positions
	neutralPositions = new vec4[neutralMax];

	//HALL
	//Behind Wall
	neutralPositions[0] = { 1, 1, 1, 2};
	neutralPositions[1] = { 3, 1, 1, 2};
	neutralPositions[2] = { 5, 1, 1, 2};
	neutralPositions[3] = { 7, 1, 1, 2};
	neutralPositions[4] = { 9, 1, 1, 2};
	neutralPositions[5] = { 11, 1, 1, 2 };
	neutralPositions[6] = { -1, 1, 1, 2};
	neutralPositions[7] = { -3, 1, 1, 2};
	neutralPositions[8] = { -5, 1, 1, 2};
	neutralPositions[9] = { -7, 1, 1, 2};
	neutralPositions[10] = { -9, 1, 1, 2};
	neutralPositions[11] = { -11, 1, 1, 2 };

	//Left Wall
	neutralPositions[12] = { 11, 1, 3, 2 };
	neutralPositions[13] = { 11, 1, 5, 2 };
	neutralPositions[14] = { 11, 1, 7, 2 };
	neutralPositions[15] = { 11, 1, 9, 2 };
	neutralPositions[16] = { 11, 1, 11, 2 };
	neutralPositions[17] = { 11, 1, 13, 2 };
	neutralPositions[18] = { 11, 1, 15, 2 };
	neutralPositions[19] = { 11, 1, 17, 2 };
	neutralPositions[20] = { 11, 1, 19, 2 };
	neutralPositions[21] = { 11, 1, 21, 2 };
	neutralPositions[22] = { 11, 1, 23, 2 };

	//Right Wall
	neutralPositions[23] = { -11, 1, 3, 2 };
	neutralPositions[24] = { -11, 1, 5, 2 };
	neutralPositions[25] = { -11, 1, 7, 2 };
	neutralPositions[26] = { -11, 1, 9, 2 };
	neutralPositions[27] = { -11, 1, 11, 2 };
	neutralPositions[28] = { -11, 1, 13, 2 };
	neutralPositions[29] = { -11, 1, 15, 2 };
	neutralPositions[30] = { -11, 1, 17, 2 };
	neutralPositions[31] = { -11, 1, 19, 2 };
	neutralPositions[32] = { -11, 1, 21, 2 };
	neutralPositions[33] = { -11, 1, 23, 2 };

	//Pasage Start
	neutralPositions[34] = { 9, 1, 23, 2 };
	neutralPositions[35] = { 7, 1, 23, 2 };
	neutralPositions[36] = { -9, 1, 23, 2 };
	neutralPositions[37] = { -7, 1, 23, 2 };

	//Passage Left
	neutralPositions[38] = { 7, 1, 25, 2 };
	neutralPositions[39] = { 7, 1, 27, 2 };
	neutralPositions[40] = { 7, 1, 29, 2 };
	neutralPositions[41] = { 7, 1, 31, 2 };
	neutralPositions[42] = { 7, 1, 33, 2 };
	neutralPositions[43] = { 7, 1, 35, 2 };
	neutralPositions[44] = { 7, 1, 37, 2 };
	neutralPositions[45] = { 7, 1, 39, 2 };
	neutralPositions[46] = { 7, 1, 41, 2 };
	neutralPositions[47] = { 7, 1, 43, 2 };

	//Passage Right
	neutralPositions[48] = { -7, 1, 25, 2 };
	neutralPositions[49] = { -7, 1, 27, 2 };
	neutralPositions[50] = { -7, 1, 29, 2 };
	neutralPositions[51] = { -7, 1, 31, 2 };
	neutralPositions[52] = { -7, 1, 33, 2 };
	neutralPositions[53] = { -7, 1, 35, 2 };
	neutralPositions[54] = { -7, 1, 37, 2 };
	neutralPositions[55] = { -7, 1, 39, 2 };
	neutralPositions[56] = { -7, 1, 41, 2 };
	neutralPositions[57] = { -7, 1, 43, 2 };


	//Allies
	for (int i = 0; i < 0; i++)
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
	
	for (int i = 0; i < 0; i++)
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

	for (int i = 0; i < neutralMax; i++)
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

