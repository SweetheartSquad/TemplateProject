#pragma once

#include <MY_Scene_Shaders.h>

MY_Scene_Shaders::MY_Scene_Shaders(Game * _game) :
	MY_Scene_Base(_game)
{
}

MY_Scene_Shaders::~MY_Scene_Shaders(){
}


void MY_Scene_Shaders::update(Step * _step){
	MY_Scene_Base::update(_step);
}