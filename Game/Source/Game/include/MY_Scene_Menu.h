#pragma once

#include <MY_Scene_Base.h>

class MY_Scene_Menu : public MY_Scene_Base{
public:
	virtual void update(Step * _step) override;

	MY_Scene_Menu(Game * _game);
	~MY_Scene_Menu();
};