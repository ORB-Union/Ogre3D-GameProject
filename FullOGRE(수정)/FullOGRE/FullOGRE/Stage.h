
#ifndef STAGE_H
#define STAGE_H
#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
#include<OgreMesh.h>
#include<OgreMeshManager.h>
#include <OgreFrameListener.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkCameraMan.h>

class Stage
{
public :
	Stage(Ogre::SceneManager* sceneManagerstage);
	~Stage();
	void addToScene();
private :
	Ogre::SceneManager* sceneManagerstage;
};


#endif