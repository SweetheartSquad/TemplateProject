#pragma once

#include <MY_Scene_Box2D.h>

#include <Box2DWorld.h>
#include <Box2DMeshEntity.h>
#include <Box2DDebugDrawer.h>

MY_Scene_Box2D::MY_Scene_Box2D(Game * _game) :
	MY_Scene_Base(_game),
	box2dWorld(new Box2DWorld(b2Vec2(0.f, -10.0f))),
	box2dDebugDrawer(new Box2DDebugDrawer(box2dWorld))
{
	// Setup the debug drawer and add it to the scene
	childTransform->addChild(box2dDebugDrawer, false);
	box2dDebugDrawer->drawing = false;
	box2dWorld->b2world->SetDebugDraw(box2dDebugDrawer);
	box2dDebugDrawer->AppendFlags(b2Draw::e_shapeBit);
	box2dDebugDrawer->AppendFlags(b2Draw::e_centerOfMassBit);
	box2dDebugDrawer->AppendFlags(b2Draw::e_jointBit);
}

MY_Scene_Box2D::~MY_Scene_Box2D(){
}


void MY_Scene_Box2D::update(Step * _step){
	// Physics update
	box2dWorld->update(_step);
	// Scene update
	MY_Scene_Base::update(_step);
}

void MY_Scene_Box2D::enableDebug(){
	MY_Scene_Base::enableDebug();
	box2dDebugDrawer->drawing = true;
}
void MY_Scene_Box2D::disableDebug(){
	MY_Scene_Base::disableDebug();
	box2dDebugDrawer->drawing = false;
}