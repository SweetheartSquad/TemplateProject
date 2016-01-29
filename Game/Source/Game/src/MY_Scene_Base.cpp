#pragma once

#include <MY_Scene_Base.h>

#include <MeshEntity.h>
#include <MeshInterface.h>
#include <MeshFactory.h>

#include <shader\ComponentShaderBase.h>
#include <shader\ComponentShaderText.h>
#include <shader\ShaderComponentText.h>
#include <shader\ShaderComponentTexture.h>
#include <shader\ShaderComponentDiffuse.h>
#include <shader\ShaderComponentMVP.h>

#include <RenderSurface.h>
#include <StandardFrameBuffer.h>
#include <NumberUtils.h>

#include <RenderOptions.h>

MY_Scene_Base::MY_Scene_Base(Game * _game) :
	Scene(_game),
	screenSurfaceShader(new Shader("assets/engine basics/DefaultRenderSurface", false, true)),
	screenSurface(new RenderSurface(screenSurfaceShader)),
	screenFBO(new StandardFrameBuffer(true)),
	baseShader(new ComponentShaderBase(true)),
	textShader(new ComponentShaderText(true)),
	font(MY_ResourceManager::globalAssets->getFont("DEFAULT")->font),
	uiLayer(new UILayer(0,0,0,0)),
	debugCam(new MousePerspectiveCamera())
{
	baseShader->addComponent(new ShaderComponentMVP(baseShader));
	//baseShader->addComponent(new ShaderComponentDiffuse(baseShader));
	baseShader->addComponent(new ShaderComponentTexture(baseShader));
	baseShader->compileShader();

	textShader->textComponent->setColor(glm::vec3(0.0f, 0.0f, 0.0f));

	// Set up debug camera
	cameras.push_back(debugCam); // Add it to the cameras list (this isn't strictly necessary, but is useful organizational and debugging purposes)
	childTransform->addChild(debugCam); // Add it to the scene to give it a position and remove the need to update it manually
	activeCamera = debugCam; // Make it the active camera so that it is the source for the view-projection matrices
	// configure the camera's default properties
	debugCam->farClip = 1000.f;
	debugCam->nearClip = 0.01f;
	debugCam->firstParent()->translate(5.0f, 1.5f, 22.5f);
	debugCam->yaw = 90.0f;
	debugCam->pitch = -10.0f;
	

	// reference counting for member variables
	++baseShader->referenceCount;
	++textShader->referenceCount;

	++screenSurface->referenceCount;
	++screenSurfaceShader->referenceCount;
	++screenFBO->referenceCount;
}

MY_Scene_Base::~MY_Scene_Base(){
	deleteChildTransform();

	// auto-delete member variables
	baseShader->decrementAndDelete();
	textShader->decrementAndDelete();

	screenSurface->decrementAndDelete();
	screenSurfaceShader->decrementAndDelete();
	screenFBO->decrementAndDelete();

	delete uiLayer;
}


void MY_Scene_Base::update(Step * _step){
	// basic debugging controls
	if(keyboard->keyJustDown(GLFW_KEY_ESCAPE)){
		// if the user hits escape on the menu, exit the game
		// if the user hits escape anywhere else, take them to the menu
		if(game->scenes["menu"] == this){
			game->exit();
		}else{
			game->switchScene("menu", false);
		}
	}if(keyboard->keyJustDown(GLFW_KEY_F11)){
		game->toggleFullScreen();
	}if(keyboard->keyJustDown(GLFW_KEY_1)){
		cycleCamera();
	}if(keyboard->keyJustDown(GLFW_KEY_2)){
		toggleDebug();
	}

	glm::uvec2 sd = sweet::getWindowDimensions();
	uiLayer->resize(0, sd.x, 0, sd.y);
	Scene::update(_step);
	uiLayer->update(_step);
}

void MY_Scene_Base::render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions){
	screenFBO->resize(game->viewPortWidth, game->viewPortHeight);


	FrameBufferInterface::pushFbo(screenFBO);

	_renderOptions->clear();
	Scene::render(_matrixStack, _renderOptions);
	uiLayer->render(_matrixStack, _renderOptions);

	FrameBufferInterface::popFbo();


	screenSurface->render(screenFBO->getTextureId());
}

void MY_Scene_Base::load(){
	Scene::load();	

	screenSurface->load();
	screenFBO->load();
	uiLayer->load();
}

void MY_Scene_Base::unload(){
	uiLayer->unload();
	screenFBO->unload();
	screenSurface->unload();

	Scene::unload();	
}


bool MY_Scene_Base::isDebugEnabled(){	
	return Transform::drawTransforms;
}

void MY_Scene_Base::toggleDebug(){
	isDebugEnabled() ? disableDebug() : enableDebug();
}

void MY_Scene_Base::enableDebug(){
	Transform::drawTransforms = true;
	uiLayer->bulletDebugDrawer->setDebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
}
void MY_Scene_Base::disableDebug(){
	Transform::drawTransforms = false;
	uiLayer->bulletDebugDrawer->setDebugMode(btIDebugDraw::DBG_NoDebug);
}