#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet\src\btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	//Wheels render
	Cylinder wheel;
	Cube wheelRadius;
	Cube joints;

	wheelRadius.color = Green;
	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{	
		wheel.radius = info.wheels[i].radius;
		wheel.height = info.wheels[i].width;

		wheelRadius.size = { info.wheels[i].width+0.1f, info.wheels[i].radius * 2, 0.1f };

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);
		wheelRadius.transform = wheel.transform;

		wheelRadius.Render();
		wheel.Render();

	}

	//Chassis render
	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	chassis.Render();

	//turret render
	Sphere turret;
	turret.radius = info.turret.turretRadius;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&turret.transform);
	vec3 turretCenter;
	turretCenter.x = turret.transform.translation().x + info.chassis_offset.x;
	turretCenter.y = turret.transform.translation().y + info.chassis_size.y * 0.5 + 1 + info.chassis_offset.y;
	turretCenter.z = turret.transform.translation().z + info.turret.turretOffset + info.chassis_offset.z;

	turret.transform.translate(turretCenter.x, turretCenter.y, turretCenter.z);

	turret.Render();

	//Turret base render
	Cylinder turretBase;
	//info.turret.turret->
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&turret.transform);
	turret.transform.translate(turretCenter.x, turretCenter.y - 1, turretCenter.z);
	turretBase.height = 1.0f;
	turretBase.radius = turret.radius;
	turretBase.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyLeftEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels() / 2; ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

void PhysVehicle3D::ApplyRightEngineForce(float force)
{
	for (int i = vehicle->getNumWheels() / 2; i < vehicle->getNumWheels(); ++i)
	{
		if (info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}


// ----------------------------------------------------------------------------
void PhysVehicle3D::LeftBrake(float force)
{
	for (int i = 0; i < vehicle->getNumWheels() / 2; ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

void PhysVehicle3D::RightBrake(float force)
{
	for (int i = vehicle->getNumWheels() / 2; i < vehicle->getNumWheels(); ++i)
	{
		if (info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

float PhysVehicle3D::GetLeftWheelSpeed()
{
	float rotation = 0.0f;
	int nWheels = 0;
	for (int i = 1; i < vehicle->getNumWheels() / 2 - 1; ++i)
	{
			rotation += vehicle->getWheelInfo(i).m_deltaRotation;
			nWheels++;
	}
	return rotation / nWheels;
}

float PhysVehicle3D::GetRightWheelSpeed()
{
	float rotation = 0.0f;
	int nWheels = 0;
	for (int i = vehicle->getNumWheels() / 2+1; i < vehicle->getNumWheels()-1; ++i)
	{
		rotation += vehicle->getWheelInfo(i).m_deltaRotation;
		nWheels++;
	}
	return rotation / nWheels;
}

void PhysVehicle3D::RotateTurret(float amount)
{

}
void PhysVehicle3D::RotateCanon(float amount)
{

}

void PhysVehicle3D::Fire()
{

}

// ----------------------------------------------------------------------------
/*void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}*/

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}