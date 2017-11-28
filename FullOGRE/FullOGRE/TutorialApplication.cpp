#include "TutorialApplication.h"


using namespace Ogre;

TutorialApplication::TutorialApplication()
	: mRoot(0),
	mShutdown(false),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),
	playermove(250),
	mWindow(0),
	mSceneMgr(0),
	mCamera(0),
	mInputMgr(0),
	mMouse(0),
	mKeyboard(0),
	mPlayerNode(0),
	mCameraMan(0),
	playerDirection(Vector3::ZERO)
{

}

TutorialApplication::~TutorialApplication()
{
	if(mCameraMan)
		delete mCameraMan;

	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete mRoot;
}

void TutorialApplication::go()
{

#ifdef _DEBUG
	mResourcesCfg = "resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

	if (!setup())
		return;


	//if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		//return false;

	mRoot->startRendering();

	destroyScene();

}

//조작 구현
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		mShutdown = true;
	}

	if(mShutdown)
	{
		return false;
	}


	if (mWindow->isClosed()) return false;

	//
	//mPlayerNode->translate(playerDirection *fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	mKeyboard->capture();
	mMouse->capture();

	mPlayerNode->translate(playerDirection *fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
 
	mCameraMan->frameRenderingQueued(fe);

	return true;
}


bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke)
{
	//mCameraMan->injectKeyDown(ke);
	
	switch (ke.key)
	{
	case OIS::KC_W :
		playerDirection.z = -playermove;
		break;
	case OIS::KC_S :
		playerDirection.z = playermove;
		break;
	case OIS::KC_A:
		playerDirection.x = -playermove;
		break;
	case OIS::KC_D:
		playerDirection.x = playermove;
		break;
	default:
		break;
	}
	
	return true;
}
bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke)
{
	 //mCameraMan->injectKeyUp(ke);

	switch (ke.key)
	{
	case OIS::KC_W :
		playerDirection.z = 0;
		break;
	case OIS::KC_S :
		playerDirection.z = 0;
		break;
	case OIS::KC_A:
		playerDirection.x = 0;
		break;
	case OIS::KC_D:
		playerDirection.x = 0;
		break;
	default:
		break;
	}
	return true;
}

//세팅
bool TutorialApplication::setup()
{
	mRoot = new Ogre::Root(mPluginsCfg);

	setupResources();

	if (!configure())
		return false;

	chooseSceneManager();
	createCamera();
	//createViewports();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(10);

	createResourceListener();
	loadResources();

	createScene();

	createFrameListener();

	return true;
}


bool TutorialApplication::configure()
{
  if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
  {
    return false;
  }

  mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

  return true;
}

void TutorialApplication::chooseSceneManager()
{
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}


//카메라 생성
void TutorialApplication::createCamera()
{
	// Set camera position & direction
	mCamera = mSceneMgr->createCamera("MainCam");
	mCamera->setPosition(Ogre::Vector3(1500, 1500, 1500));
	//mCamera->rotate
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(20);
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));


	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}


//개체들 배치
void TutorialApplication::createScene()
{
	//mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	//기본적 배치를 위한 라이트
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(300, 300, -300);

	// Create a plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane("plane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		3000,3000,200,200,true,1,3,3,Vector3::UNIT_Z);
	Ogre::Entity* ent = mSceneMgr->createEntity("LightPlaneEntity", "plane");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/BeachStones");
	Ogre::SceneNode* node = mSceneMgr->createSceneNode("Node1");
	mSceneMgr->getRootSceneNode()->addChild(node);

	
	Ogre::Entity* entNinja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	entNinja->setCastShadows(true);
	Ogre::SceneNode* playernode = mSceneMgr->getRootSceneNode()->createChildSceneNode("playernode");
	playernode->setPosition(0,0,0);
	playernode->attachObject(entNinja);

	//이러한 접근도 가능함 참고
	//mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);
	//Ogre::SceneNode* playernode =  mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", Ogre::Vector3( 0, 0, 0 ));
	//playernode->attachObject(entNinja);


	mPlayerNode = playernode;
}

void TutorialApplication::destroyScene()
{

}

void TutorialApplication::createFrameListener()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputMgr = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(
		mInputMgr->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(
		mInputMgr->createInputObject(OIS::OISMouse, true));

	mKeyboard->setEventCallback(this);
	//mMouse->setEventCallback(this);

	windowResized(mWindow);

	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	Ogre::LogManager::getSingletonPtr()->logMessage("Finished");
}

void TutorialApplication::setupResources()
{
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
}

void TutorialApplication::createResourceListener()
{

}

void TutorialApplication::loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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