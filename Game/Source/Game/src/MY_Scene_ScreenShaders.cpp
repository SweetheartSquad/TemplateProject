#pragma once

#include <MY_Scene_ScreenShaders.h>
#include <RenderSurface.h>
#include <StandardFrameBuffer.h>

MY_Scene_ScreenShaders::MY_Scene_ScreenShaders(Game * _game) :
	MY_Scene_Base(_game),
	screenSurfaceShader(new Shader("assets/RenderSurface_1", false, true)),
	screenSurface(new RenderSurface(screenSurfaceShader)),
	screenFBO(new StandardFrameBuffer(true))
{

	++screenSurface->referenceCount;
	++screenSurfaceShader->referenceCount;
	++screenFBO->referenceCount;
}

MY_Scene_ScreenShaders::~MY_Scene_ScreenShaders(){

	screenSurface->decrementAndDelete();
	screenSurfaceShader->decrementAndDelete();
	screenFBO->decrementAndDelete();
}


void MY_Scene_ScreenShaders::update(Step * _step){
	MY_Scene_Base::update(_step);
}

void MY_Scene_ScreenShaders::render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions){
	screenFBO->resize(game->viewPortWidth, game->viewPortHeight);

	FrameBufferInterface::pushFbo(screenFBO);

	MY_Scene_Base::render(_matrixStack, _renderOptions);

	FrameBufferInterface::popFbo();


	screenSurface->render(screenFBO->getTextureId());
}

void MY_Scene_ScreenShaders::load(){
	MY_Scene_Base::load();	

	screenSurface->load();
	screenFBO->load();
}

void MY_Scene_ScreenShaders::unload(){
	screenFBO->unload();
	screenSurface->unload();

	MY_Scene_Base::unload();	
}