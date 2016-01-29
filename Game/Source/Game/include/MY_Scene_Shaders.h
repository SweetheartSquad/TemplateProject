#pragma once

#include <MY_Scene_Base.h>

class MY_Scene_Shaders : public MY_Scene_Base{
public:
	virtual void update(Step * _step) override;

	MY_Scene_Shaders(Game * _game);
	~MY_Scene_Shaders();
};