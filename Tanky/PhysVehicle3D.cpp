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

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();


	chassis.Render();
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