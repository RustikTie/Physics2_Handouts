#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include <time.h> 
#include <stdio.h>
#include <stdlib.h>

// TODO 1: Include Box 2 header and library
#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
#pragma comment (lib, "Box2D/libx86/Debug/Box2D.lib")
#endif

#ifndef _DEBUG;
#pragma comment (lib, "Box2D/libx86/Release/Box2D.lib")
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	world = new b2World(b2Vec2 (0.0f, 20.0f));

	// TODO 4: Create a a big static circle as "ground"
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(10.0f, 8.0f);
	groundBody = world->CreateBody(&groundBodyDef);

	circle.m_radius = 4.0f;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&circle, 0.0f);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	
	world->Step(timeStep, velocityIterations, positionIterations);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		tinyCircles.type = b2_dynamicBody;
		tinyCircles.position.Set(PIXEL_TO_METER(App->input->GetMouseX()), PIXEL_TO_METER(App->input->GetMouseY()));
		groundBody = world->CreateBody(&tinyCircles);

		srand(time(NULL));

		circle.m_radius = rand()%3;
		groundBody->CreateFixture(&circle, 0.0f);
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METER_TO_PIXEL(pos.x), METER_TO_PIXEL(pos.y), METER_TO_PIXEL(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete(world);

	return true;
}
