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

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

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

	Cylinder handlebar(info.chassis_size.x*0.25f, info.chassis_size.y*1.5f);
	//handlebar.SetRotation(90, vec3(0, 0, 1));
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&handlebar.transform);
	//handlebar.transform.rotate(90, vec3(handlebar.transform.M[8], handlebar.transform.M[9], handlebar.transform.M[10]));
	float t = handlebar.transform.M[0];
	handlebar.transform.M[0] = -handlebar.transform.M[4];
	handlebar.transform.M[4] = t;
	t = handlebar.transform.M[1];
	handlebar.transform.M[1] = -handlebar.transform.M[5];
	handlebar.transform.M[5] = t;
	t = handlebar.transform.M[2];
	handlebar.transform.M[2] = -handlebar.transform.M[6];
	handlebar.transform.M[6] = t;

	btVector3 offset2(info.chassis_offset.x, info.chassis_offset.y*0.75f, info.chassis_offset.z + (info.chassis_size.z*0.5) + info.chassis_size.z*0.1f);
	offset2 = offset2.rotate(q.getAxis(), q.getAngle());

	handlebar.transform.M[12] += offset2.getX();
	handlebar.transform.M[13] += offset2.getY();
	handlebar.transform.M[14] += offset2.getZ();

	handlebar.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}