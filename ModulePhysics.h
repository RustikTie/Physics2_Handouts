#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D\Box2D\Box2D.h"

/*class b2World; // or #include "Box2D/Box2D/Box2D.h" but defining is better (doesn't waste time)
class b2Body;
class b2BodyDef;
class b2PolygonShape; */

#define PIXEL_PER_METER 50.0f
#define METER_PER_PIXEL 0.02f
#define METER_TO_PIXEL(m) ((int)PIXEL_PER_METER*m)
#define PIXEL_TO_METER(p) ((float)METER_PER_PIXEL*p)

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

	b2World* world;
	b2Body* groundBody;
	b2BodyDef groundBodyDef;
	b2PolygonShape groundBox;
	b2CircleShape circle;
	b2BodyDef tinyCircles;
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	bool debug;
};