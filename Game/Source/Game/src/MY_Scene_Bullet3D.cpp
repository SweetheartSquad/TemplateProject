#pragma once

#include <MY_Scene_Bullet3D.h>

#include <NodeBulletBody.h>
#include <BulletMeshEntity.h>
#include <BulletWorld.h>

MY_Scene_Bullet3D::MY_Scene_Bullet3D(Game * _game) :
	MY_Scene_Base(_game),
	bulletWorld(new BulletWorld(glm::vec3(0, -9.8, 0))), // we initialize the world's gravity here
	bulletDebugDrawer(new BulletDebugDrawer(bulletWorld->world))
{
	// Setup the debug drawer and add it to the scene
	bulletWorld->world->setDebugDrawer(bulletDebugDrawer);
	childTransform->addChild(bulletDebugDrawer, false);
	bulletDebugDrawer->setDebugMode(btIDebugDraw::DBG_NoDebug);
}

MY_Scene_Bullet3D::~MY_Scene_Bullet3D(){
}


void MY_Scene_Bullet3D::update(Step * _step){
	// Physics update
	bulletWorld->update(_step);
	// Scene update
	MY_Scene_Base::update(_step);
}

void MY_Scene_Bullet3D::enableDebug(){
	MY_Scene_Base::enableDebug();
	bulletDebugDrawer->setDebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
}
void MY_Scene_Bullet3D::disableDebug(){
	MY_Scene_Base::disableDebug();
	bulletDebugDrawer->setDebugMode(btIDebugDraw::DBG_NoDebug);
}