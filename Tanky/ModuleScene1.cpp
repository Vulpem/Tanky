#include "Globals.h"
#include "Application.h"
#include "ModuleScene1.h"
#include "Primitive.h"
#include "PhysBody3D.h"


ModuleScene1::ModuleScene1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene1::~ModuleScene1()
{}

// Load assets
bool ModuleScene1::Start()
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
bool ModuleScene1::CleanUp()
{
	LOG("Unloading Intro scene");
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
update_status ModuleScene1::Update(float dt)
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

void ModuleScene1::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}

void ModuleScene1::LoadTowers()
{
	int neutralMax = 111;
	neutralPositions = new vec4[neutralMax];
#pragma region NeutralPositions
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

	//PASAGE
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
	neutralPositions[48] = { 7, 1, 45, 2 };
	neutralPositions[49] = { 7, 1, 47, 2 };
	neutralPositions[50] = { 7, 1, 49, 2 };
	neutralPositions[51] = { 7, 1, 51, 2 };
	neutralPositions[52] = { 7, 1, 53, 2 };
	neutralPositions[53] = { 7, 1, 55, 2 };
	neutralPositions[54] = { 7, 1, 57, 2 };
	neutralPositions[55] = { 7, 1, 59, 2 };
	neutralPositions[56] = { 7, 1, 61, 2 };
	neutralPositions[57] = { 7, 1, 63, 2 };

	//Passage Right
	neutralPositions[58] = { -7, 1, 25, 2 };
	neutralPositions[59] = { -7, 1, 27, 2 };
	neutralPositions[60] = { -7, 1, 29, 2 };
	neutralPositions[61] = { -7, 1, 31, 2 };
	neutralPositions[62] = { -7, 1, 33, 2 };
	neutralPositions[63] = { -7, 1, 35, 2 };
	neutralPositions[64] = { -7, 1, 37, 2 };
	neutralPositions[65] = { -7, 1, 39, 2 };
	neutralPositions[66] = { -7, 1, 41, 2 };
	neutralPositions[67] = { -7, 1, 43, 2 };
	neutralPositions[68] = { -7, 1, 45, 2 };
	neutralPositions[69] = { -7, 1, 47, 2 };
	neutralPositions[70] = { -7, 1, 49, 2 };
	neutralPositions[71] = { -7, 1, 51, 2 };
	neutralPositions[72] = { -7, 1, 53, 2 };
	neutralPositions[73] = { -7, 1, 55, 2 };
	neutralPositions[74] = { -7, 1, 57, 2 };
	neutralPositions[75] = { -7, 1, 59, 2 };
	neutralPositions[76] = { -7, 1, 61, 2 };
	neutralPositions[77] = { -7, 1, 63, 2 };

	//End Start
	neutralPositions[78] = { -7, 1, 63, 2 };
	neutralPositions[79] = { -9, 1, 63, 2 };
	neutralPositions[80] = { -11, 1, 63, 2 };
	neutralPositions[81] = { -13, 1, 63, 2 };
	neutralPositions[82] = { -15, 1, 63, 2 };

	neutralPositions[83] = { 7, 1, 63, 2 };
	neutralPositions[84] = { 9, 1, 63, 2 };
	neutralPositions[85] = { 11, 1, 63, 2 };
	neutralPositions[86] = { 13, 1, 63, 2 };
	neutralPositions[87] = { 15, 1, 63, 2 };

	//End Left
	neutralPositions[88] = { 15, 1, 65, 2 };
	neutralPositions[89] = { 15, 1, 67, 2 };
	neutralPositions[90] = { 15, 1, 69, 2 };
	neutralPositions[91] = { 15, 1, 71, 2 };

	//End Right
	neutralPositions[92] = { -15, 1, 65, 2 };
	neutralPositions[93] = { -15, 1, 67, 2 };
	neutralPositions[94] = { -15, 1, 69, 2 };
	neutralPositions[95] = { -15, 1, 71, 2 };

	//End End
	neutralPositions[96] = { -13, 1, 71, 2 };
	neutralPositions[97] = { -11, 1, 71, 2 };
	neutralPositions[98] = { -9, 1, 71, 2 };
	neutralPositions[99] = { -7, 1, 71, 2 };
	neutralPositions[100] = { -5, 1, 71, 2 };
	neutralPositions[101] = { -3, 1, 71, 2 };
	neutralPositions[102] = { -1, 1, 71, 2 };
	neutralPositions[103] = { 1, 1, 71, 2 };
	neutralPositions[104] = { 3, 1, 71, 2 };
	neutralPositions[105] = { 5, 1, 71, 2 };
	neutralPositions[106] = { 7, 1, 71, 2 };
	neutralPositions[107] = { 9, 1, 71, 2 };
	neutralPositions[108] = { 11, 1, 71, 2 };
	neutralPositions[109] = { 13, 1, 71, 2 };

#pragma endregion NeutralPositions

	int enemyMax = 4;
	enemyPositions = new vec4[enemyMax];
#pragma region EnemyPositions

	enemyPositions[0] = { 9, 0, 67, 5 };
	enemyPositions[1] = { 3, 0, 67, 5 };
	enemyPositions[2] = { -3, 0, 67, 5 };
	enemyPositions[3] = { -9, 0, 67, 5 };



#pragma endregion EnemyPositions
	/*
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
	*/
	//Enemies
	
	for (int i = 0; i < enemyMax; i++)
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

	delete[]neutralPositions;
}

void ModuleScene1::CheckTowersNumbers()
{
	/*
	if (allyTowers == 0)
	{
		LOG("YOU LOOSE");
	}
	else */if (enemyTowers == 0)
	{
		App->camera->Disable();
		App->player->Disable();
		App->scene_1->Disable();
		App->scene_2->Enable();
		App->player->Enable();
		App->camera->Enable();
	}
}

