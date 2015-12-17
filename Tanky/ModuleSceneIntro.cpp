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

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	for (int i = 0; i < 10; i++)
	{
		Tower* tower = new Tower(5 * i, 5 * i, TOWER_ALLY, 5, 2);
		for (int i = 0; i < tower->cubes.Count(); i++)
		{
			tower->pbs.PushBack(App->physics->AddBody(*tower->cubes[i]));
			tower->pbs[i]->SetInactive();
		}
		towers.PushBack(tower);
	}

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
		towers[i]->Update();
	}

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	sensor->GetTransform(&s.transform);
	s.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

