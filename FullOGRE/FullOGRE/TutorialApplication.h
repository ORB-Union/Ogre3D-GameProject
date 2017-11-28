
#ifndef TUTORIALAPPLICATION_H
#define TUTORIALAPPLICATION_H

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

class TutorialApplication
	: public Ogre::WindowEventListener,
	public Ogre::FrameListener,
	public OIS::KeyListener
	//public OIS::MouseListener
{
public:
	TutorialApplication();
	virtual ~TutorialApplication();
	void go();

private:

	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/*
	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	*/

	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);


	//게임실행 함수들
	bool setup();
	bool configure();

	void createFrameListener();
	void createCamera();
	void createScene();
	//void createViewports();
	void destroyScene();
	void setupResources();
	void createResourceListener();
	void loadResources();
	void chooseSceneManager();

	bool mShutdown;

	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	OgreBites::SdkCameraMan* mCameraMan;

	//개체들
	Ogre::Vector3 playerDirection; // 플레이어
	Ogre::SceneNode* mPlayerNode; // 플레이어

	Ogre::Real playermove;

	Ogre::Real mDistance;
	Ogre::Real mWalkSpd;
	Ogre::Vector3 mDirection;
	Ogre::Vector3 mDestination;
	Ogre::AnimationState* mAnimationState;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mNode;


	//Ogre::MeshManager* mMeshMgr;
	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;
	

};

#endif