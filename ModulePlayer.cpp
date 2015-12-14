#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	nitro = 100.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	debug = false;

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 250.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 17.0f;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 3;
	car.wheels = new Wheel[3];

	// FRONT ------------------------
	car.wheels[0].connection.Set(0, connection_height, half_length + wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = false;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// REAR-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width - 0.3f * wheel_width, connection_height + 0.5f, -half_length - wheel_radius / 2);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width + 0.5f;
	car.wheels[1].front = false;
	car.wheels[1].drive = true;
	car.wheels[1].brake = true;
	car.wheels[1].steering = false;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width + 0.3f * wheel_width, connection_height + 0.5f, -half_length - wheel_radius / 2);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width + 0.5f;
	car.wheels[2].front = false;
	car.wheels[2].drive = true;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 2, 10);
	
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
	turn = acceleration = brake = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT/* || (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) */||
		App->input->GetJButton(8) == KEY_DOWN)
	{
		brake = BRAKE_POWER;
	}

	else
	{
		if (App->input->GetJAxisValue() != 0)
			turn = TURN_DEGREES * -App->input->GetJAxisValue();

		if (App->input->GetJAccelValue() != 0 || App->input->GetJDeaccelValue() != 0)
		{
			if (App->input->GetJAccelValue() - App->input->GetJDeaccelValue() > 0)
			{
				if (vehicle->GetKmh() < 0.0f)
					acceleration = MAX_ACCELERATION * 2 * (App->input->GetJAccelValue() - App->input->GetJDeaccelValue());
				else
					acceleration = MAX_ACCELERATION * (App->input->GetJAccelValue() - App->input->GetJDeaccelValue());
			}
			else
			{
				if (vehicle->GetKmh() > 0.0f)
					acceleration = MAX_ACCELERATION * 2 * (App->input->GetJAccelValue() - App->input->GetJDeaccelValue());
				else
					acceleration = (MAX_ACCELERATION / 2) * (App->input->GetJAccelValue() - App->input->GetJDeaccelValue());
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) != KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) != KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			{
				if (vehicle->GetKmh() > 0.0f)
					acceleration = -MAX_ACCELERATION * 2;
				else
					acceleration = -MAX_ACCELERATION / 2;
			}

			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			{
				if (vehicle->GetKmh() < 0.0f)
					acceleration = MAX_ACCELERATION * 2;
				else
					acceleration = MAX_ACCELERATION;
			}
		}
	}

	if (acceleration != 0.0f && nitro > 1.0f && (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT || App->input->GetJButton(9) == KEY_DOWN))
	{
		acceleration = acceleration * 4;
		nitro--;
	}

	else if (nitro < 99.9)
		nitro += 0.1f;

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_REPEAT)
	{
		debug = !debug;
	}

	if (debug == false)
	{
		App->camera->bodyToFollow = vehicle;
	}

	char title[80];
	sprintf_s(title, "%.1f Km/h      %.1f nitro", vehicle->GetKmh(), nitro);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



