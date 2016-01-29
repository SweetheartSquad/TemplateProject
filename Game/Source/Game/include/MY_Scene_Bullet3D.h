#pragma once

#include <MY_Scene_Base.h>

class MY_Scene_Bullet3D : public MY_Scene_Base{
public:
	// The scene's physics world
	BulletWorld * bulletWorld;
	// used to draw wireframes showing physics colliders, transforms, etc
	BulletDebugDrawer * bulletDebugDrawer;

	MY_Scene_Bullet3D(Game * _game);
	~MY_Scene_Bullet3D();


	virtual void update(Step * _step) override;
	
	// overriden to add physics debug drawing
	virtual void enableDebug() override;
	// overriden to remove physics debug drawing
	virtual void disableDebug() override;
};