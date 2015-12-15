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

	p.size = vec3(DIAMETER_WORLD, 0, DIAMETER_WORLD);
	p.SetPos(0, 2.5f , 0);

	plane = App->physics->AddBody(p, 0.0f);
	plane->SetAsSensor(true);
	plane->collision_listeners.add(this);

	CreateCube(vec3(0, 37, 100), vec3(6, 10, 1), 0.0f, vec3(0, 0, 0), true);


	CreateCube(vec3(0, 50, 0), vec3(10.0f, 1.0f, 30.0f));
	CreateCube(vec3(0, 49.12f, 19.7f), vec3(10.0f, 1.0f, 10.0f), 10.0f, vec3(1, 0, 0));
	CreateCube(vec3(0, 46.92f, 29.28f), vec3(10.0f, 1.0f, 10.0f), 15.0f, vec3(1, 0, 0));
	CreateCube(vec3(0, 44.22f, 38.88f), vec3(10.0f, 1.0f, 10.0f), 16.0f, vec3(1, 0, 0));
	CreateCube(vec3(0, 41.42f, 48.42f), vec3(10.0f, 1.0f, 10.0f), 17.0f, vec3(1, 0, 0));
	CreateCube(vec3(0, 38.32f, 57.9f), vec3(10.0f, 1.0f, 10.0f), 19.0f, vec3(1, 0, 0));
	CreateCube(vec3(0, 35.44f, 67.42f), vec3(10.0f, 1.0f, 10.0f), 14.5855f, vec3(1, 0, 0));
	CreateCube(vec3(0, 33.34f, 77.14f), vec3(10.0f, 1.0f, 10.0f), 9.4119f, vec3(1, 0, 0));
	CreateCube(vec3(0, 32.07f, 87.0f), vec3(10.0f, 1.0f, 10.0f), 4.9394f, vec3(1, 0, 0));
	CreateCube(vec3(0, 31.6f, 101.97f), vec3(10.0f, 1.0f, 20.0f));
	//9
	CreateCube(vec3(-0.67, 31.6f, 116.23), vec3(10.0f, 1.0f, 10.0f), -8.98, vec3(0, 1, 0));
	CreateCube(vec3(-2.76, 31.6, 125.54), vec3(10.0f, 1.0f, 10.0f), -16.0787, vec3(0, 1, 0));
	CreateCube(vec3(-5.64, 31.6f, 134.46), vec3(10.0f, 1.0f, 10.0f), -110.9619, vec3(0, 1, 0));
	CreateCube(vec3(-9.37, 31.6f, 142.99), vec3(10.0f, 1.0f, 10.0f), -116.8159, vec3(0, 1, 0));
	CreateCube(vec3(-14.22, 31.6f, 150.98), vec3(10.0f, 1.0f, 10.0f), -123.727, vec3(0, 1, 0));
	CreateCube(vec3(-19.76, 31.6f, 158.7), vec3(10.0f, 1.0f, 10.0f), -127.6666, vec3(0, 1, 0));
	CreateCube(vec3(-26.07, 31.6f, 165.69), vec3(10.0f, 1.0f, 10.0f), -134.889, vec3(0, 1, 0));
	CreateCube(vec3(-33.21, 31.6f, 172.29), vec3(10.0f, 1.0f, 10.0f), -138.8494, vec3(0, 1, 0));
	CreateCube(vec3(-40.11, 31.6f, 177.13), vec3(10.0f, 1.0f, 10.0f), -153.0961, vec3(0, 1, 0));
	CreateCube(vec3(-48.4, 31.6f, 180.31), vec3(10.0f, 1.0f, 10.0f), -75.0569, vec3(0, 1, 0));
	CreateCube(vec3(-56.6, 31.6, 181.4), vec3(10.0f, 1.0f, 10.0f));
	//20
	CreateCube(vec3(-66.45, 30.93, 181.4), vec3(10.0f, 1.0f, 10.0f), 7.8374, vec3(0, 0, 1));
	CreateCube(vec3(-76.18, 29.53, 181.4), vec3(10.0f, 1.0f, 10.0f), 7.9516, vec3(0, 0, 1));
	CreateCube(vec3(-85.81, 28.39, 181.4), vec3(10.0f, 1.0f, 10.0f), 4.6115, vec3(0, 0, 1));
	CreateCube(vec3(-95.03, 28.01, 181.4), vec3(10.0f, 1.0f, 10.0f));
	CreateCube(vec3(-104.6, 28.01, 181.4), vec3(10.0f, 1.0f, 10.0f));
	
	CreateCube(vec3(0.16f, 31.6f, 181.4), vec3(10.0f, 1.0f, 10.0f), 8.98, vec3(0, 0, 1));
	CreateCube(vec3(0.16f, 31.6f, 181.4), vec3(10.0f, 1.0f, 10.0f), 8.98, vec3(0, 0, 1));
	CreateCube(vec3(0.16f, 31.6f, 181.4), vec3(10.0f, 1.0f, 10.0f), 8.98, vec3(0, 0, 1));
	CreateCube(vec3(0.16f, 31.6f, 181.4), vec3(10.0f, 1.0f, 10.0f), 8.98, vec3(0, 0, 1));
	CreateCube(vec3(0.16f, 31.6f, 181.4), vec3(10.0f, 1.0f, 10.0f), 8.98, vec3(0, 0, 1));
	CreateCube(vec3(0.16f, 31.6f, 181.4), vec3(10.0f, 1.0f, 10.0f), 8.98, vec3(0, 0, 1));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	for (p2List_item<Cube*>* tmp = cubes.getFirst(); tmp != NULL; tmp = tmp->next)
	{
		delete tmp->data;
	}
	cubes.clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	//plane->GetTransform(&p.transform);
	if (App->player->debug)
		p.Render();

	Plane floor(0, 1, 0, 0);
	floor.axis = true;
	floor.color.Set(255, 0, 0);
	//-----------------
	mat4x4 player_pos;
	App->player->vehicle->GetTransform(&player_pos);
	floor.SetPos(player_pos.M[12], 0, player_pos.M[14]);
	//-----------------
	floor.Render();

	Cube* tmp;
	if(s.at(App->player->checkpoint, tmp))
		s.findNode(tmp)->data->Render();
	else
	{
		LOG("Win!!");
	}

	//-----------------
	for (p2List_item<Cube*>* tmp = cubes.getFirst(); tmp != NULL; tmp = tmp->next)
	{
		tmp->data->Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");

	if (body1 == plane && body2 == App->player->vehicle)
	{
		App->player->reset = true;
	}

	PhysBody3D* tmp;
	sensor.at((App->player->checkpoint), tmp);
	if (body1 == tmp && body2 == App->player->vehicle)
	{
		App->player->checkpoint++;
		App->player->vehicle->GetTransform(&App->player->last_checkpoint_matrix);
	}
}

void ModuleSceneIntro::CreateCube(const vec3& position, const vec3& size, float angle, const vec3& rotAxis, bool is_sensor)
{
	Cube* c = new Cube();
	c->size.Set(size.x, size.y, size.z);
	c->SetPos(position.x, position.y, position.z);
	if (angle != 0.0f)
		c->SetRotation(angle, rotAxis);

	if (is_sensor)
	{
		c->color.Set(0, 255, 0);
		s.add(c);
		sensor.add(App->physics->AddBody(*c, 0.0f));
		sensor.getLast()->data->SetAsSensor(true);
		sensor.getLast()->data->collision_listeners.add(this);
	}
	else
	{
		cubes.add(c);
		App->physics->AddBody(*c, 0);
	}
}

float ModuleSceneIntro::CalcAngle(const vec3& axis)
{
	return (float)sqrt((axis.x * axis.x) + (axis.y * axis.y) + (axis.z * axis.z));
}