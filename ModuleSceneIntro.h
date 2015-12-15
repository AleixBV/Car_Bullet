#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	Cube sensor_cube;
	p2List<Cube*>* s;
	p2List<PhysBody3D*>* sensor;
	unsigned int checkpoint;
	Cube p;
	PhysBody3D* plane;

	Cube cc1, cc2, cc3, cc4;
};