#pragma once

#include <MY_Scene_Base.h>

class Box2DWorld;
class Box2DDebugDrawer;

class MY_Scene_Box2D : public MY_Scene_Base{
public:
	// The scene's physics world
	Box2DWorld * box2dWorld;
	// used to draw wireframes showing physics colliders, transforms, etc
	Box2DDebugDrawer * box2dDebugDrawer;

	MY_Scene_Box2D(Game * _game);
	~MY_Scene_Box2D();

	virtual void update(Step * _step) override;
	
	// overriden to add physics debug drawing
	virtual void enableDebug() override;
	// overriden to remove physics debug drawing
	virtual void disableDebug() override;
};