#pragma once
#include "Module.h"
#include "Globals.h"

class b2World; // or #include "Box2D/Box2D/Box2D.h" but defining is better (doesn't waste time)
class b2Body;

#define PIXELS_PER_METER 50.0f
#define METERS_PER_PIXEL 0.02f
#define METER_TO_PIXEL(m) ((int)PIXELS_PER_METER*m)
#define PIXEL_TO_METER(p) ((float)METERS_PER_PIXEL*p)

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:

	b2World *world;
	b2Body* groundBody;
	bool debug;
};