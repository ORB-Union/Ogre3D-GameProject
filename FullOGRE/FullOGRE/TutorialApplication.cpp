#include "TutorialApplication.h"
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
#include<OgreMesh.h>
#include<OgreMeshManager.h>

using namespace Ogre;

TutorialApplication::TutorialApplication()
	: mRoot(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),
	mWindow(0),
	mSceneMgr(0),
	mCamera(0),
	mInputMgr(0),
	mMouse(0),
	mKeyboard(0)
{

}

TutorialApplication::~TutorialApplication()
{
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

	windowClosed(mWindow);

	delete mRoot;
}

bool TutorialApplication::go()
{

#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	mRoot = new Ogre::Root(mPluginsCfg);

	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;


			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}


	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;

	//게임 배치
	mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(10);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	// Set camera position & direction
	mCamera = mSceneMgr->createCamera("MainCam");
	mCamera->setPosition(Ogre::Vector3(600, 600, 600));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(5);
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));

	// Create a plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
	MeshManager::getSingleton().createPlane("plane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500,1500,200,200,true,1,5,5,Vector3::UNIT_Z);
	Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/BeachStones");
	Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1");
	mSceneMgr->getRootSceneNode()->addChild(node);

	// Create a spot light
	//Ogre::SceneManager::setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* light = mSceneMgr->createLight("Light1");
	light->setType(Ogre::Light::LT_SPOTLIGHT);
	light->setDirection(Ogre::Vector3(0, -1, 0));
	light->setDiffuseColour(Ogre::ColourValue(0.0f, 1.0f, 0.0f));
	light->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	light->setSpotlightOuterAngle(Ogre::Degree(90.0f));
	Ogre::SceneNode* node2 = node->createChildSceneNode("node2");
	node2->setPosition(0, 100, 0);
	node2->attachObject(light);

	Ogre::Entity* lightEnt = mSceneMgr->createEntity("MyEntity","sphere.mesh");
	Ogre::SceneNode* node3 = node->createChildSceneNode("node3");
	node3->setScale(0.1f, 0.1f, 0.1f);
	node3->setPosition(0,100,0);
	node3->attachObject(lightEnt); 

	// Create a another spot light
	Ogre::Light* light2 = mSceneMgr->createLight("Light2");
	light2->setType(Ogre::Light::LT_SPOTLIGHT);
	light2->setDirection(Ogre::Vector3(0, -1, 0));
	light2->setDiffuseColour(Ogre::ColourValue(1.0f, 0.0f, 0.0f));
	light2->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	light2->setSpotlightOuterAngle(Ogre::Degree(90.0f));
	Ogre::SceneNode* node4 = node->createChildSceneNode("node4");
	node4->setPosition(0, 100, 50);
	node4->attachObject(light2);

	Ogre::Entity* lightEnt2 = mSceneMgr->createEntity("MyEntity2","sphere.mesh");
	Ogre::SceneNode* node5 = node->createChildSceneNode("node5");
	node5->setScale(0.1f, 0.1f, 0.1f);
	node5->attachObject(lightEnt2);
	node5->setPosition(0, 100, 50);

	//수정해야함
	Ogre::Entity* entNinja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);
	Ogre::SceneNode* node6 = mSceneMgr->createSceneNode("node6");
	entNinja->setCastShadows(true);
	mSceneMgr->getRootSceneNode()->addChild(node6);
	node6->setPosition(100,0,0);
	
	
	
	//mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);

	// OIS
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	OIS::ParamList pl;
	size_t windowHandle = 0;
	std::ostringstream windowHandleStr;

	mWindow->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleStr << windowHandle;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

	mInputMgr = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(
		mInputMgr->createInputObject(OIS::OISKeyboard, false));
	mMouse = static_cast<OIS::Mouse*>(
		mInputMgr->createInputObject(OIS::OISMouse, false));

	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	mRoot->startRendering();

	return true;
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	if (mWindow->isClosed()) return false;

	mKeyboard->capture();
	mMouse->capture();

	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) return false;

	return true;
}

void TutorialApplication::windowResized(Ogre::RenderWindow* rw)
{
	int left, top;
	unsigned int width, height, depth;

	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void TutorialApplication::windowClosed(Ogre::RenderWindow* rw)
{
	if(rw == mWindow)
	{
		if(mInputMgr)
		{
			mInputMgr->destroyInputObject(mMouse);
			mInputMgr->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputMgr);
			mInputMgr = 0;
		}
	}
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		TutorialApplication app;

		try
		{
			app.go();
		}
		catch(Ogre::Exception& e)
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			/*
			MessageBox(
			NULL,
			e.getFullDescription().c_str(),
			"An exception has occured!",
			MB_OK | MB_ICONERROR | MB_TASKMODAL);
			*/
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}
#ifdef __cplusplus
}
#endif