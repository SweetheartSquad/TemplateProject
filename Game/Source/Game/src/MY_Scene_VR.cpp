#pragma once

#include <MY_Scene_VR.h>

#include <shader/ShaderComponentMVP.h>
#include <shader/ShaderComponentTexture.h>
#include <shader/ShaderComponentDiffuse.h>
#include <shader/ShaderComponentPhong.h>
#include <shader/ShaderComponentBlinn.h>
#include <shader/ShaderComponentToon.h>
#include <RampTexture.h>

#include <MeshFactory.h>

#include <PointLight.h>

#include <StereoCamera.h>

MY_Scene_VR::MY_Scene_VR(Game * _game) :
	MY_Scene_Base(_game),
	vrCam(new StereoCamera())
{
	childTransform->addChild(vrCam);
	activeCamera = vrCam;

	vrCam->childTransform->addChild(new CameraController(vrCam), false);

	// We need some stuff to look at, so we set up a diffuse shader, a light, and some simple objects
	ComponentShaderBase * diffuseShader = new ComponentShaderBase(true);
	diffuseShader->addComponent(new ShaderComponentMVP(diffuseShader));
	diffuseShader->addComponent(new ShaderComponentDiffuse(diffuseShader, false));
	diffuseShader->addComponent(new ShaderComponentTexture(diffuseShader));
	diffuseShader->compileShader();


	
	// add a bunch of cubes arranged in a circle
	MeshInterface * cubeMesh = MeshFactory::getCubeMesh();
	for(signed long int i = 0; i < 32; ++i){
		MeshEntity * me = new MeshEntity(cubeMesh, diffuseShader);
		childTransform->addChild(me)->translate(cos(i/32.f * glm::pi<float>()*2)*10, 0, sin(i/32.f * glm::pi<float>()*2)*10, false);
		//me->mesh->pushTexture2D(MY_ResourceManager::globalAssets->getTexture("DEFAULT")->texture);
	}
	
	// create our light and add it to the scene
	PointLight * light = new PointLight(glm::vec3(1), 0.05f, 0.001f, -1);
	childTransform->addChild(light);
	lights.push_back(light);
	// add a cube to the light too so that we can see it without having to use the debug mode
	light->childTransform->addChild(new MeshEntity(cubeMesh, baseShader), false);
}

void MY_Scene_VR::render(sweet::MatrixStack * _matrixStack, RenderOptions * _renderOptions){
	vrCam->renderStereo([this, _matrixStack, _renderOptions](){
		MY_Scene_Base::render(_matrixStack, _renderOptions);
	});
	// If an hmd is connected, we blit the stereo camera's buffers back to the screen after we're done rendering
	if(sweet::ovrInitialized){
		vrCam->blitTo(0);
	}
}