#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = rightAcceleration = leftAcceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(4, 1.5f, 7);
	car.chassis_offset.Set(0, 1.5f, 0);
	car.mass = 6000.0f;
	car.suspensionStiffness = 10; 
	car.suspensionCompression = 0.9f;
	car.suspensionDamping = 2.0f; 
	car.maxSuspensionTravelCm = 50.0f;
	car.frictionSlip = 1;
	car.maxSuspensionForce = 75000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.4f;
	float motor_radius = 0.5f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 14;
	car.wheels = new Wheel[14];

	float leftSide = half_width - 0.3f * wheel_width;
	float rightSide = -half_width + 0.3f * wheel_width;
	float motor = connection_height + 0.45f;
	float normal = connection_height;
	float dist = (half_length / 3);

	// LEFT FRONT------------------------
	car.wheels[0].connection.Set(leftSide, motor, dist*-3);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = motor_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = true;
	car.wheels[0].steering = false;

	// LEFT ------------------------
	for (int n = -2; n <= 2; n++)
	{
		car.wheels[n+3].connection.Set(leftSide, normal, dist * n);
		car.wheels[n+3].direction = direction;
		car.wheels[n+3].axis = axis;
		car.wheels[n+3].suspensionRestLength = suspensionRestLength;
		car.wheels[n+3].radius = wheel_radius;
		car.wheels[n+3].width = wheel_width;
		car.wheels[n+3].front = false;
		car.wheels[n+3].drive = true;
		car.wheels[n+3].brake = true;
		car.wheels[n+3].steering = false;
	}

	// LEFT REAR ------------------------
	car.wheels[6].connection.Set(leftSide, motor, dist*3);
	car.wheels[6].direction = direction;
	car.wheels[6].axis = axis;
	car.wheels[6].suspensionRestLength = suspensionRestLength;
	car.wheels[6].radius = motor_radius;
	car.wheels[6].width = wheel_width;
	car.wheels[6].front = true;
	car.wheels[6].drive = true;
	car.wheels[6].brake = true;
	car.wheels[6].steering = false;

	// RIGHT FRONT------------------------
	car.wheels[7].connection.Set(rightSide, motor, dist*-3);
	car.wheels[7].direction = direction;
	car.wheels[7].axis = axis;
	car.wheels[7].suspensionRestLength = suspensionRestLength;
	car.wheels[7].radius = motor_radius;
	car.wheels[7].width = wheel_width;
	car.wheels[7].front = true;
	car.wheels[7].drive = true;
	car.wheels[7].brake = true;
	car.wheels[7].steering = false;

	// RIGHT ------------------------
	for (int n = -2; n <= 2; n++)
	{
		car.wheels[n + 10].connection.Set(rightSide, normal, dist * n);
		car.wheels[n + 10].direction = direction;
		car.wheels[n + 10].axis = axis;
		car.wheels[n + 10].suspensionRestLength = suspensionRestLength;
		car.wheels[n + 10].radius = wheel_radius;
		car.wheels[n + 10].width = wheel_width;
		car.wheels[n + 10].front = false;
		car.wheels[n + 10].drive = true;
		car.wheels[n + 10].brake = true;
		car.wheels[n + 10].steering = false;
	}

	// RIGHT REAR ------------------------
	car.wheels[13].connection.Set(rightSide, motor, dist * 3);
	car.wheels[13].direction = direction;
	car.wheels[13].axis = axis;
	car.wheels[13].suspensionRestLength = suspensionRestLength;
	car.wheels[13].radius = motor_radius;
	car.wheels[13].width = wheel_width;
	car.wheels[13].front = true;
	car.wheels[13].drive = true;
	car.wheels[13].brake = true;
	car.wheels[13].steering = false;

	car.turret.turretRadius = car.chassis_size.y;
	car.turret.turretOffset = -1.5f;

	car.turret.canonLength = 6.0f;
	car.turret.canonRadius = 0.3f;

	vehicle = App->physics->AddVehicle(car, 0, 4 ,10);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = rightAcceleration = leftAcceleration = brake = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT && vehicle->GetKmh() < MAX_SPEED)
	{
		if (vehicle->GetLeftWheelSpeed() < 0.0f)
		{
			vehicle->ApplyLeftEngineForce(0);
			vehicle->LeftBrake(BRAKE_POWER);
		}
		else
		{
			vehicle->ApplyLeftEngineForce(MAX_ACCELERATION);
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT && vehicle->GetKmh() > -MAX_SPEED)
	{
		if (vehicle->GetLeftWheelSpeed() > 0.0f)
		{
			vehicle->ApplyLeftEngineForce(0);
			vehicle->LeftBrake(BRAKE_POWER);
		}
		else
		{
			vehicle->ApplyLeftEngineForce(-MAX_ACCELERATION);
		}
	}
	else
	{
		vehicle->ApplyLeftEngineForce(0);
		vehicle->LeftBrake(BRAKE_POWER);
	}


	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT && vehicle->GetKmh() < MAX_SPEED)
	{
		if (vehicle->GetRightWheelSpeed() < 0.0f)
		{
			vehicle->ApplyRightEngineForce(0);
			vehicle->RightBrake(BRAKE_POWER);
		}
		else
		{
			vehicle->ApplyRightEngineForce(MAX_ACCELERATION);
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT && vehicle->GetKmh() > -MAX_SPEED)
	{
		if (vehicle->GetRightWheelSpeed() > 0.0f)
		{
			vehicle->ApplyRightEngineForce(0);
			vehicle->RightBrake(BRAKE_POWER);
		}
		else
		{
			vehicle->ApplyRightEngineForce(-MAX_ACCELERATION);
		}
	}
	else
	{
		vehicle->ApplyRightEngineForce(0);
		vehicle->RightBrake(BRAKE_POWER);
	}

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
	{
		vehicle->RotateTurret(-TURRET_SPEED * dt);
	}
	else if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)
	{
		vehicle->RotateTurret(TURRET_SPEED * dt);
	}
	else
	{
		vehicle->RotateTurret(0);
	}
	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_REPEAT)
	{
		vehicle->RotateCanon(CANON_SPEED * dt);
	}
	else if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT)
	{
		vehicle->RotateCanon(-CANON_SPEED * dt);
	}
	else
	{
		vehicle->RotateCanon(0);
	}


	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		float tX, tY, tZ;
		vehicle->info.turret.turret->GetPos(&tX, &tY, &tZ);
		float cX, cY, cZ;
		vehicle->info.turret.canon->GetPos(&cX, &cY, &cZ);

		float x, y, z;
		x = (tX - cX);
		y = (tY - cY);
		z = (tZ - cZ);

		App->physics->Shoot({ cX - x, cY - y, cZ - z }, { -x, -y, -z }, 60.0f, 0.5f);
		vehicle->Push(x * 8000, y *100 - 20000, z * 8000);
	}
	return UPDATE_CONTINUE;
}


