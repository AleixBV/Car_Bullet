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

	p.size = vec3(200, 0, 200);
	p.SetPos(0, 2.5f , 0);

	plane = App->physics->AddBody(p, 0.0f);
	plane->SetAsSensor(true);
	plane->collision_listeners.add(this);

	checkpoint = 0;

	sensor_cube.size = vec3(5, 3, 1);
	sensor_cube.SetPos(0, 2.5f, 20);

	s->getLast()->data->color.Set(0, 255, 0);

	sensor->add(App->physics->AddBody(*s->getLast()->data, 0.0f));
	sensor->getLast()->data->SetPos(0, 10.0f, 20.0f);
	sensor->getLast()->data->SetAsSensor(true);
	sensor->getLast()->data->collision_listeners.add(this);

	cc1.size.Set(10.0f, 1.0f, 100.0f);
	cc1.SetPos(0, 10, 0);
	App->physics->AddBody(cc1, 0);

	cc2.size.Set(10.0f, 1.0f, 10.0f);
	cc2.SetPos(0, 9.2f, 54.5f);
	cc2.SetRotation(10.0f, vec3(1, 0, 0));
	App->physics->AddBody(cc2, 0);

	cc3.size.Set(10.0f, 1.0f, 10.0f);
	cc3.SetPos(0, 7.2f, 63.5f);
	cc3.SetRotation(15.0f, vec3(1, 0, 0));
	App->physics->AddBody(cc3, 0);

	cc4.size.Set(10.0f, 1.0f, 10.0f);
	cc4.SetPos(0, 6.5f, 72.5f);
	cc4.SetRotation(12.0f, vec3(1, 0, 0));
	App->physics->AddBody(cc4, 0);

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
	//plane->GetTransform(&p.transform);
	if (App->player->debug)
		p.Render();

	Plane floor(0, 1, 0, 0);
	floor.axis = true;
	floor.color.Set(255, 0, 0);
	floor.Render();

	Cube* tmp;
	s->at(checkpoint, tmp);
	s->findNode(tmp)->data->Render();

	//-----------------
	cc1.Render();
	cc2.Render();
	cc3.Render();
	cc4.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");

	if (body1 == plane && body2 == App->player->vehicle)
	{
		App->player->reset = true;
	}
}

