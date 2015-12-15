#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 20.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	bool debug;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	float nitro;
	int deaths;
	bool reset;
	unsigned int reset_timer;
	mat4x4 last_checkpoint_matrix;
	unsigned int checkpoint;

private:
	mat4x4 initial_matrix;
};