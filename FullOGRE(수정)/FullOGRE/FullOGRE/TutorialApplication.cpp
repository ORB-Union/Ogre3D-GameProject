#include "TutorialApplication.h"
#include"Stage.h"
#define CAMERA_NAME "SceneCamera"

using namespace Ogre;
using namespace OgreBites;

Stage *stageptr = NULL;

TutorialApplication::TutorialApplication()
	: mRoot(0),
	mShutdown(false),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),
	playermove(400), mWindow(0), mSceneMgr(0), mCamera(0), mInputMgr(0), mMouse(0), mKeyboard(0),
	mPlayerNode(0), mCameraMan(0), mCameraNode(0), playerrotate(1), playerDirection(Vector3::ZERO), pause(false),
	mSpotlightNode1(0), mPlayerAnimationState(0), mSecondarySceneMgr(0), mSecondTitle(false), mEnemyAnimationState(0), PlayerScore(0),
	mRaySceneQuery(0), mEnemyNode(0), mPlayerPosition(Vector3::ZERO), mEnemyEntity(0), mEnemyWalkSpd(200.0), mEnemyDirection(Vector3::ZERO),
	mEnemyDestination(Vector3::ZERO), mEnemyDistance(0), mEnemyEntity2(0), mEnemyWalkSpd2(200.0), mEnemyDirection2(Vector3::ZERO),
	mEnemyDestination2(Vector3::ZERO), mEnemyDistance2(0), mEnemyNode2(0), mEnemyEntity3(0), mEnemyWalkSpd3(200.0), mEnemyDirection3(Vector3::ZERO),
	mEnemyDestination3(Vector3::ZERO), mEnemyDistance3(0), mEnemyNode3(0), mEnemyEntity4(0), mEnemyWalkSpd4(200.0), mEnemyDirection4(Vector3::ZERO),
	mEnemyDestination4(Vector3::ZERO), mEnemyDistance4(0), mEnemyNode4(0),  mTrayMgr(0),mOverlaySystem(0),	mInfoLabel(0), scoreInfoLabel(0), 
	mEnemyparticleNode1(0), mEnemyparticleNode2(0), mEnemyparticleNode3(0), mEnemyparticleNode4(0), Health(0),
	HP(100), HeroPosition1(Vector3::ZERO), Death(false), Enemy_HP(10)
{

}

static void swap(Ogre::SceneManager *&first, Ogre::SceneManager *&second)
{
	Ogre::SceneManager *tmp = first;
	first = second;
	second = tmp;
}

TutorialApplication::~TutorialApplication()
{
	if(mCameraMan)	
		delete mCameraMan;
	if(mTrayMgr)
	delete mTrayMgr;
	
	if (mOverlaySystem) delete mOverlaySystem;

	//mSceneMgr->destroyQuery(mRaySceneQuery);

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

/*
bool TutorialApplication::isCollision(const Ogre::Vector3& position, const Ogre::Vector3& direction) 
{

	Ogre::Ray ray(position, direction);
	mRaySceneQuery->setRay(ray);
	Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator itr;
	for (itr = result.begin(); itr != result.end(); itr++) {
		if (itr->movable->getName().compare("enemynode") != 0) {
			return true;
		}
	}
	return false;
}
*/

void TutorialApplication::InGame(const FrameEvent& evt)
{
	char TimersText[30]; // 시간 표시
	char ScoreText[30]; // 점수 표시
	char TitleText[100]; // 제목
	char TitleText2[100]; // 설명 표시

	char HealthText[100]; // 체력 표시

	clock_t start;

	HeroPosition1 = mPlayerNode->getPosition();

	if(pause)
	{
		start = clock();
		sprintf(TimersText, "Time : %i" , start / CLOCKS_PER_SEC);
		mInfoLabel->show();
		mInfoLabel->setCaption(TimersText);

		sprintf(ScoreText, "Score : %i" , PlayerScore);
		scoreInfoLabel->show();
		scoreInfoLabel->setCaption(ScoreText);

		TitleInfoLabel->show();
		sprintf(TitleText, "Night Of Enemy Playing!");
		TitleInfoLabel->setCaption(TitleText);

		TitleInfoLabel2->show();
		sprintf(TitleText2, "Get Rid of The Enemy During Time Of Infinite!");
		TitleInfoLabel2->setCaption(TitleText2);

		sprintf(HealthText, "HP : %i" , HP);
		Health->show();
		Health->setCaption(HealthText);
	}



	if (mEnemyDirection == Ogre::Vector3::ZERO)
	{
		if (nextLocation())
		{
			mEnemyAnimationState = mEnemyEntity->getAnimationState("Walk");
			mEnemyAnimationState->setLoop(true);
			mEnemyAnimationState->setEnabled(true);
		}
	}

	if(mEnemyDirection != Ogre::Vector3::ZERO)
	{
		Ogre::Real move = mEnemyWalkSpd * evt.timeSinceLastFrame;
		mEnemyDistance -= move;

		if (mEnemyDistance <= 0.0)
		{
			mEnemyNode->setPosition(mEnemyDestination);
			mEnemyDirection = Ogre::Vector3::ZERO;

			if (nextLocation())
			{
				Ogre::Vector3 src = mEnemyNode->getOrientation() * Ogre::Vector3::UNIT_X;

				if ((1.0 + src.dotProduct(mEnemyDirection)) < 0.0001)
				{
					mEnemyNode->yaw(Ogre::Degree(180));
				}
				else
				{
					Ogre::Quaternion quat = src.getRotationTo(mEnemyDirection);
					mEnemyNode->rotate(quat);
				}
			}
			else
			{
				mEnemyAnimationState = mEnemyEntity->getAnimationState("Idle");
				mEnemyAnimationState->setLoop(true);
				mEnemyAnimationState->setEnabled(true);
			}
		}
		else
		{
			mEnemyNode->translate(move * mEnemyDirection);
			mEnemyparticleNode1->translate(move * mEnemyDirection);
		}
	}


	Vector3 EnemyPosition = mEnemyNode->getPosition();
	//왼쪽아래적 충돌처리
	if((HeroPosition1.x - 50) < (EnemyPosition.x + 1))
	{
		if((HeroPosition1.z -30) < (EnemyPosition.z + 30) &&
			(HeroPosition1.z +30) > (EnemyPosition.z -15))
		{
			HP -= 1;
			playerDirection += Vector3(0,0,0);
			mPlayerNode->setPosition((EnemyPosition.x +101), EnemyPosition.y,EnemyPosition.z+51);
		}
	}
	
	if (mEnemyDirection2 == Ogre::Vector3::ZERO)
	{
		if (nextLocation2())
		{
			mEnemyAnimationState2 = mEnemyEntity2->getAnimationState("Walk");
			mEnemyAnimationState2->setLoop(true);
			mEnemyAnimationState2->setEnabled(true);
		}
	}

	if(mEnemyDirection2 != Ogre::Vector3::ZERO)
	{
		Ogre::Real move2 = mEnemyWalkSpd2 * evt.timeSinceLastFrame;
		mEnemyDistance2 -= move2;

		if (mEnemyDistance2 <= 0.0)
		{
			mEnemyNode2->setPosition(mEnemyDestination2);
			mEnemyDirection2 = Ogre::Vector3::ZERO;

			if (nextLocation2())
			{
				Ogre::Vector3 src2 = mEnemyNode2->getOrientation() * Ogre::Vector3::UNIT_X;

				if ((1.0 + src2.dotProduct(mEnemyDirection2)) < 0.0001)
				{
					mEnemyNode2->yaw(Ogre::Degree(180));
				}
				else
				{
					Ogre::Quaternion quat2 = src2.getRotationTo(mEnemyDirection2);
					mEnemyNode2->rotate(quat2);
				}
			}
			else
			{
				mEnemyAnimationState2 = mEnemyEntity2->getAnimationState("Idle");
				mEnemyAnimationState2->setLoop(true);
				mEnemyAnimationState2->setEnabled(true);
			}
		}
		else
		{
			mEnemyNode2->translate(move2 * mEnemyDirection2);			
			mEnemyparticleNode2->translate(move2 * mEnemyDirection2);
		}
	}


	Vector3 EnemyPosition2 = mEnemyNode2->getPosition();

	if((HeroPosition1.x + 20) < (EnemyPosition2.x - 1))
	{
		if((HeroPosition1.z + 20) > (EnemyPosition2.z - 1) &&
			(HeroPosition1.z - 20) < (EnemyPosition2.z +1))
		{
			HP -= 1;
			playerDirection += Vector3(0,0,0);
			mPlayerNode->setPosition((EnemyPosition2.x -101), EnemyPosition2.y,EnemyPosition2.z-51);
		}
	}

	if (mEnemyDirection3 == Ogre::Vector3::ZERO)
	{
		if (nextLocation3())
		{
			mEnemyAnimationState3 = mEnemyEntity3->getAnimationState("Walk");
			mEnemyAnimationState3->setLoop(true);
			mEnemyAnimationState3->setEnabled(true);
		}
	}

	if(mEnemyDirection3 != Ogre::Vector3::ZERO)
	{
		Ogre::Real move3 = mEnemyWalkSpd3 * evt.timeSinceLastFrame;
		mEnemyDistance3 -= move3;

		if (mEnemyDistance3 <= 0.0)
		{
			mEnemyNode3->setPosition(mEnemyDestination3);
			mEnemyDirection3 = Ogre::Vector3::ZERO;

			if (nextLocation3())
			{
				Ogre::Vector3 src3 = mEnemyNode3->getOrientation() * Ogre::Vector3::UNIT_X;
				if ((1.0 + src3.dotProduct(mEnemyDirection3)) < 0.0001)
				{
					mEnemyNode3->yaw(Ogre::Degree(180));
				}
				else
				{
					Ogre::Quaternion quat3 = src3.getRotationTo(mEnemyDirection3);
					mEnemyNode3->rotate(quat3);
				}
			}
			else
			{
				mEnemyAnimationState3 = mEnemyEntity3->getAnimationState("Idle");
				mEnemyAnimationState3->setLoop(true);
				mEnemyAnimationState3->setEnabled(true);
			}
		}
		else
		{
			mEnemyNode3->translate(move3 * mEnemyDirection3);
			mEnemyparticleNode3->translate(move3 * mEnemyDirection3);
		}
	}

	Vector3 EnemyPosition3 = mEnemyNode3->getPosition();

	if((HeroPosition1.x - 50) < (EnemyPosition3.x + 1))
	{
		if((HeroPosition1.z -50) < (EnemyPosition3.z + 1) &&
			(HeroPosition1.z +50) > (EnemyPosition3.z - 1))
		{
			HP -= 1;
			playerDirection += Vector3(0,0,0);
			mPlayerNode->setPosition((EnemyPosition3.x +101), EnemyPosition3.y,EnemyPosition3.z+51);
		}
	}

	
	if (mEnemyDirection4 == Ogre::Vector3::ZERO)
	{
		if (nextLocation4())
		{
			mEnemyAnimationState4 = mEnemyEntity4->getAnimationState("Walk");
			mEnemyAnimationState4->setLoop(true);
			mEnemyAnimationState4->setEnabled(true);
		}
	}

	if(mEnemyDirection4 != Ogre::Vector3::ZERO)
	{
		Ogre::Real move4 = mEnemyWalkSpd4 * evt.timeSinceLastFrame;
		mEnemyDistance4 -= move4;

		if (mEnemyDistance4 <= 0.0)
		{
			mEnemyNode4->setPosition(mEnemyDestination4);
			mEnemyDirection4 = Ogre::Vector3::ZERO;

			if (nextLocation4())
			{
				Ogre::Vector3 src4 = mEnemyNode4->getOrientation() * Ogre::Vector3::UNIT_X;

				if ((1.0 + src4.dotProduct(mEnemyDirection4)) < 0.0001)
				{
					mEnemyNode4->yaw(Ogre::Degree(180));
				}
				else
				{
					Ogre::Quaternion quat4 = src4.getRotationTo(mEnemyDirection4);
					mEnemyNode4->rotate(quat4);
				}
			}
			else
			{
				mEnemyAnimationState4 = mEnemyEntity4->getAnimationState("Idle");
				mEnemyAnimationState4->setLoop(true);
				mEnemyAnimationState4->setEnabled(true);
			}
		}
		else
		{
			mEnemyNode4->translate(move4 * mEnemyDirection4);
			mEnemyparticleNode4->translate(move4 * mEnemyDirection4);
		}
	}

		//오른쪽 아래
	Vector3 EnemyPosition4 = mEnemyNode4->getPosition();

	if((HeroPosition1.x - 50) < (EnemyPosition4.x + 1))
	{
		if((HeroPosition1.z - 20) < (EnemyPosition4.z + 1) &&
			(HeroPosition1.z + 20) > (EnemyPosition4.z - 1))
		{
			HP -= 1;
			playerDirection += Vector3(0,0,0);
			mPlayerNode->setPosition((EnemyPosition4.x -101), EnemyPosition4.y,EnemyPosition4.z+51);
		}
	}
	/*
	if(mKeyboard->isKeyDown(OIS::KC_Q))
	{
		mPlayerNode->yaw(Ogre::Degree(playerrotate * 5));
		//mCameraNode->yaw(Ogre::Degree(playerrotate * 1));
	}

	if(mKeyboard->isKeyDown(OIS::KC_E))
	{
		mPlayerNode->yaw(Ogre::Degree(-playerrotate * 5));
		//mCameraNode->yaw(Ogre::Degree(-playerrotate * 1));
	}
	*/
	if(HP<= 0)
	{
		HP = 0;
		mPlayerAnimationState = mPlayerEntity->getAnimationState("Death1");
		mPlayerAnimationState->setEnabled(true);
		mPlayerAnimationState->setLoop(false);
		Death = true;

	}



	/*
	for(auto au = PlayerBulletlist.begin(); au != PlayerBulletlist.end(); au++)
	{
		(*au)->BulletMove(evt);
	}
	*/


	mPlayerNode->translate(playerDirection *evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	mPlayerAnimationState->addTime(evt.timeSinceLastFrame);

	mEnemyAnimationState->addTime(evt.timeSinceLastFrame);
	mEnemyAnimationState2->addTime(evt.timeSinceLastFrame);
	mEnemyAnimationState3->addTime(evt.timeSinceLastFrame);
	mEnemyAnimationState4->addTime(evt.timeSinceLastFrame);
	mCameraMan->frameRenderingQueued(evt);

	if(!Death)
	{
		mCameraNode->translate(playerDirection *evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	}
}

//isCollision(playerposition, playerDirection);


//조작 구현
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	if(mKeyboard->isKeyDown(OIS::KC_R))
	{
		mCameraNode->setPosition(2000,1000,2000);
	}

	mTrayMgr->frameRenderingQueued(fe);

	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		mShutdown = true;
	}

	if(mShutdown)
	{
		return false;
	}

	if (mWindow->isClosed()) return false;

	mKeyboard->capture();
	mMouse->capture();

	if(pause)
	{
		InGame(fe);
	}

	return true;
}

bool TutorialApplication::mouseMoved(const OIS::MouseEvent& me)
{
	if (mTrayMgr->injectMouseMove(me)) return true;
	mCameraMan->injectMouseMove(me);
	return true;
}
bool TutorialApplication::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	if (mTrayMgr->injectMouseDown(me, id)) return true;
	return true;
}
bool TutorialApplication::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id)
{  
	if (mTrayMgr->injectMouseUp(me, id)) return true;
	return true;
}


bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke)
{
	//mCameraMan->injectKeyDown(ke);
	//Vector3 playerposition = mPlayerNode->getPosition();

	/*
	if(isCollision(playerposition, playerDirection))
	{
		playerDirection = 0;
	}
	*/
	/*
	Vector3 playerbulldirection = Vector3::ZERO;
	playerbulldirection += mPlayerNode->getOrientation().x;
	playerbulldirection += mPlayerNode->getOrientation().y;
	playerbulldirection += mPlayerNode->getOrientation().z;
	playerbulldirection.normalise();
	PlayerBulletlist.push_back(new Bullet(mSceneMgr, mPlayerNode->getPosition(), playerbulldirection));
	*/

	if(!Death)
	{
		if(ke.key == OIS::KC_RETURN){ // C key swaps the SceneManager
			swap(mSceneMgr, mSecondarySceneMgr);
			setupViewport(mSceneMgr);
			pause = true;
		}

		switch (ke.key)
		{
		case OIS::KC_UP :
			mPlayerAnimationState = mPlayerEntity->getAnimationState("Walk");
			mPlayerAnimationState->setLoop(true);
			mPlayerAnimationState->setEnabled(true);
			playerDirection.z = -playermove;
			break;
		case OIS::KC_DOWN :
			mPlayerAnimationState = mPlayerEntity->getAnimationState("Walk");
			mPlayerAnimationState->setLoop(true);
			mPlayerAnimationState->setEnabled(true);
			playerDirection.z = playermove;
			break;
		case OIS::KC_LEFT:
			mPlayerAnimationState = mPlayerEntity->getAnimationState("Walk");
			mPlayerAnimationState->setLoop(true);
			mPlayerAnimationState->setEnabled(true);
			playerDirection.x = -playermove;
			break;
		case OIS::KC_RIGHT:
			mPlayerAnimationState = mPlayerEntity->getAnimationState("Walk");
			mPlayerAnimationState->setLoop(true);
			mPlayerAnimationState->setEnabled(true);
			playerDirection.x = playermove;
			break;
		case OIS::KC_A :
			mPlayerAnimationState = mPlayerEntity->getAnimationState("Attack3");
			mPlayerAnimationState->setLoop(true);
			mPlayerAnimationState->setEnabled(true);
			//PlayerBulletShoot(mSceneMgr);
			break;
		default:
			break;
		}
	}
	return true;
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke)
{
	if(!Death)
	{
		//mCameraMan->injectKeyUp(ke);
		mPlayerAnimationState = mPlayerEntity->getAnimationState("Idle2");
		mPlayerAnimationState->setLoop(true);
		mPlayerAnimationState->setEnabled(true);

		switch (ke.key)
		{
		case OIS::KC_UP :
			playerDirection.z = 0;
			break;
		case OIS::KC_DOWN :
			playerDirection.z = 0;
			break;
		case OIS::KC_LEFT:
			playerDirection.x = 0;
			break;
		case OIS::KC_RIGHT:
			playerDirection.x = 0;
			break;
		default:
			break;
		}
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
	createViewports();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(10);

	//mRaySceneQuery = mSceneMgr->createRayQuery(Ray());

	createResourceListener();
	loadResources();

	createScene();
	createFrameListener();

	return true;
}

bool TutorialApplication::configure(void)
{
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		return false;
	}

	mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

	return true;
}

void TutorialApplication::chooseSceneManager(void)
{
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "primary");
	mSecondarySceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "secondary");

	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
}

//카메라 생성
void TutorialApplication::createCamera(void)
{
	// Set camera position & direction
	mCamera = mSceneMgr->createCamera(CAMERA_NAME);
	mSecondarySceneMgr->createCamera(CAMERA_NAME);
	mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerCamNode", Ogre::Vector3(2000,1000,2000));
	//mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerCamNode", Ogre::Vector3(500,500,1000));
	mPlayerNode->yaw(Degree(-35));
	mPlayerNode->pitch(Degree(-20));
	mCameraNode = mPlayerNode;
	mPlayerNode->attachObject(mCamera);

	mCamera->setPosition(Ogre::Vector3(1000, 500, 1000));//현 카메라 좌표는 2000,1000,2000
	mCamera->lookAt(Ogre::Vector3(playerDirection.x+500, playerDirection.y+500, playerDirection.z+500));
	mCamera->setNearClipDistance(20);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);

	//mCameraNode = mPlayerNode;
	//mPlayerNode->attachObject(mCamera);

}

void TutorialApplication::setupViewport(Ogre::SceneManager *curr) 
{
	mWindow->removeAllViewports();
	Ogre::Camera *cam = curr->getCamera(CAMERA_NAME);
	Ogre::Viewport* vp = mWindow->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void TutorialApplication::createViewports(void)
{
	setupViewport(mSecondarySceneMgr); // 타이틀 화면 먼저 세팅
	mSceneMgr->setAmbientLight(ColourValue(0.2, 0.2, 0.2)); 
}

void TutorialApplication::dualViewport(Ogre::SceneManager *primarySceneMgr, Ogre::SceneManager
									   *secondarySceneMgr)
{
	mWindow->removeAllViewports();
	Ogre::Viewport *vp = 0;
	Ogre::Camera *cam = primarySceneMgr->getCamera(CAMERA_NAME);
	vp = mWindow->addViewport(cam, 0, 0, 0, 0.5, 1);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	cam = secondarySceneMgr->getCamera(CAMERA_NAME);
	vp = mWindow->addViewport(cam, 1, 0.5, 0, 0.5, 1);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//개체들 배치
void TutorialApplication::createScene(void)
{
	stageptr = new Stage(mSceneMgr);
	stageptr->addToScene();
	mSceneMgr->setSkyBox(true,"Examples/CloudyNoonSkyBox");
	//mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	//기본적 배치를 위한 라이트
	//Ogre::Light* light = mSceneMgr->createLight("MainLight");
	//light->setPosition(300, 300, -300);

	//플레이어
	mPlayerEntity = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	mPlayerEntity->setCastShadows(true);
	Ogre::SceneNode* playernode = mSceneMgr->getRootSceneNode()->createChildSceneNode("playernode");
	//바운딩박스
	playernode->showBoundingBox(true);
	AxisAlignedBox box = mPlayerEntity->getBoundingBox();
	playernode->setPosition(-150,-box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y,150);
	playernode->setScale(1.5f,1.5f,1.5f);
	playernode->attachObject(mPlayerEntity);

	mPlayerNode = playernode;

	mPlayerAnimationState = mPlayerEntity->getAnimationState("Idle2");
	mPlayerAnimationState->setLoop(true);
	mPlayerAnimationState->setEnabled(true);



	//첫번째 적(왼쪽 아래)
	mEnemyEntity = mSceneMgr->createEntity("Robot", "DustinBody.mesh");
	mEnemyEntity->setCastShadows(true);
	Ogre::SceneNode* enemynode = mSceneMgr->getRootSceneNode()->createChildSceneNode("enemynode");
	enemynode->showBoundingBox(true);
	AxisAlignedBox Ebox = mEnemyEntity->getBoundingBox();
	enemynode->setPosition(-800,-Ebox.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y,650);
	enemynode->yaw(Ogre::Degree(20));
	enemynode->setScale(1.5f,1.5f,1.5f);
	enemynode->attachObject(mEnemyEntity);

	mEnemyNode = enemynode;

	Vector3 Enemypositional1 = mEnemyNode->getPosition();

	ParticleSystem* EnemyParticle1 = mSceneMgr->createParticleSystem("EnemyParticle1", "Examples/Aureola");
	SceneNode* EparticleNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode("EnemyParticle1");
	EparticleNode1->setPosition(Enemypositional1);
	EparticleNode1->attachObject(EnemyParticle1);

	mEnemyparticleNode1 = EparticleNode1;
	mEnemyAnimationState = mEnemyEntity->getAnimationState("Idle");
	mEnemyAnimationState->setLoop(true);
	mEnemyAnimationState->setEnabled(true);

	//적의 위치 루프 설정
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-150.0, 0, -200.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-800, 0, 650.0));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 950.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-150,0,150));
	mEnemyWalkList.push_back(Ogre::Vector3(-100,0,100));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-150.0, 0, -200.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-800, 0, 650.0));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 950.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-150,0,150));
	mEnemyWalkList.push_back(Ogre::Vector3(-100,0,100));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-150.0, 0, -200.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-800, 0, 650.0));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(100,0,150));
	mEnemyWalkList.push_back(Ogre::Vector3(-1000.0, 0, -700.0));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-150.0, 0, -200.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-800, 0, 650.0));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(100,0, -150));
	mEnemyWalkList.push_back(Ogre::Vector3(-1000.0, 0, -700.0));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-150.0, 0, -200.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-800, 0, 650.0));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-100,0, 300));
	mEnemyWalkList.push_back(Ogre::Vector3(-1000.0, 0, -700.0));
	mEnemyWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
	mEnemyWalkList.push_back(Ogre::Vector3(-150.0, 0, 200.0));

	//두번째 적(오른쪽 아래)
	mEnemyEntity2 = mSceneMgr->createEntity("Robot2", "DustinBody.mesh");
	mEnemyEntity2->setCastShadows(true);
	Ogre::SceneNode* enemynode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("enemynode2");
	enemynode2->setPosition(830,0,520);
	enemynode2->yaw(Ogre::Degree(135));
	enemynode2->setScale(1.5f,1.5f,1.5f);

	enemynode2->attachObject(mEnemyEntity2);

	mEnemyNode2 = enemynode2;
	Vector3 Enemypositional2 = mEnemyNode2->getPosition();

	ParticleSystem* EnemyParticle2 = mSceneMgr->createParticleSystem("EnemyParticle2", "Examples/Aureola");
	SceneNode* EparticleNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("EnemyParticle2");
	EparticleNode2->setPosition(Enemypositional2);
	EparticleNode2->attachObject(EnemyParticle2);

	mEnemyparticleNode2 = EparticleNode2;

	mEnemyAnimationState2 = mEnemyEntity2->getAnimationState("Idle");
	mEnemyAnimationState2->setLoop(true);
	mEnemyAnimationState2->setEnabled(true);

	mEnemyWalkList2.push_back(Ogre::Vector3(830.0, 0, 600.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-300.0, 0, 180.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-600.0, 0, 350.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(130.0, 0, -500.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(830.0, 0, -950.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(300.0, 0, 180.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-600.0, 0, -350.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(130.0, 0, -500.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-830.0, 0, 950.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(300.0, 0, 180.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(600.0, 0, -350.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-130.0, 0, 500.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(200,0,200));
	mEnemyWalkList2.push_back(Ogre::Vector3(830.0, 0, 950.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-300.0, 0, 180.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-600.0, 0, 350.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(130.0, 0, -500.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(830.0, 0, -950.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(300.0, 0, 180.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-600.0, 0, -350.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(130.0, 0, -500.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-830.0, 0, 950.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(300.0, 0, 180.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(600.0, 0, -350.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(-130.0, 0, 500.0));
	mEnemyWalkList2.push_back(Ogre::Vector3(200,0,200));

	//세번째(왼쪽위)
	mEnemyEntity3 = mSceneMgr->createEntity("Robot3", "robot.mesh");
	mEnemyEntity3->setCastShadows(true);
	Ogre::SceneNode* enemynode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode("enemynode3");
	enemynode3->setPosition(-830,0,-520);
	enemynode3->yaw(Ogre::Degree(-45));
	enemynode3->setScale(3.0f,3.0f,3.0f);
	enemynode3->attachObject(mEnemyEntity3);

	mEnemyNode3 = enemynode3;

	Vector3 Enemypositional3 = mEnemyNode3->getPosition();

	ParticleSystem* EnemyParticle3 = mSceneMgr->createParticleSystem("EnemyParticle3", "Examples/Aureola");
	SceneNode* EparticleNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode("EnemyParticle3");
	EparticleNode3->setPosition(Enemypositional3);
	EparticleNode3->attachObject(EnemyParticle3);

	mEnemyparticleNode3 = EparticleNode3;

	mEnemyAnimationState3 = mEnemyEntity3->getAnimationState("Idle");
	mEnemyAnimationState3->setLoop(true);
	mEnemyAnimationState3->setEnabled(true);

	mEnemyWalkList3.push_back(Ogre::Vector3(-900.0, 0, -500.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-700.0, 0, 150.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(500.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-100, 0, -600.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(480.0, 0, 0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-1000.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-700.0, 0, 150.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(500.0, 0, -300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-100, 0, -600.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-480.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-200,0,-200));
	mEnemyWalkList3.push_back(Ogre::Vector3(-1000.0, 0, -300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-700.0, 0, 150.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(500.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-100, 0, -600.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(480.0, 0, 0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-1000.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-700.0, 0, 150.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(500.0, 0, -300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-100, 0, -600.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-480.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-1000.0, 0, -300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-700.0, 0, 150.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(500.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-100, 0, -600.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(480.0, 0, 0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-1000.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-700.0, 0, 150.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(500.0, 0, -300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-100, 0, -600.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-480.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-200,0,-200));
	mEnemyWalkList3.push_back(Ogre::Vector3(-1000.0, 0, -300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-700.0, 0, 150.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(500.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-100, 0, -600.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(480.0, 0, 0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-1000.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-700.0, 0, 150.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(500.0, 0, -300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-100, 0, -600.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-480.0, 0, 300.0));
	mEnemyWalkList3.push_back(Ogre::Vector3(-200,0,-200));

	//네번째(오른쪽아래)
	mEnemyEntity4 = mSceneMgr->createEntity("Robot4", "robot.mesh");
	mEnemyEntity4->setCastShadows(true);
	Ogre::SceneNode* enemynode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode("enemynode4");
	enemynode4->setPosition(630,0,-780);
	enemynode4->yaw(Ogre::Degree(-45));
	enemynode4->setScale(3.0f,3.0f,3.0f);
	enemynode4->attachObject(mEnemyEntity4);

	mEnemyNode4 = enemynode4;

	Vector3 Enemypositional4 = mEnemyNode4->getPosition();

	ParticleSystem* EnemyParticle4 = mSceneMgr->createParticleSystem("EnemyParticle4", "Examples/Aureola");
	SceneNode* EparticleNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode("EnemyParticle4");
	EparticleNode4->setPosition(Enemypositional4);
	EparticleNode4->attachObject(EnemyParticle4);

	mEnemyparticleNode4 = EparticleNode4;

	mEnemyAnimationState4 = mEnemyEntity4->getAnimationState("Idle");
	mEnemyAnimationState4->setLoop(true);
	mEnemyAnimationState4->setEnabled(true);

	mEnemyWalkList4.push_back(Ogre::Vector3(550.0, 0, -700.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(800.0, 0, 620.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-300.0, 0, 120.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-800.0, 0, -370.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(570.0, 0, 480.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(100.0, 0, -150.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(300.0, 0, 0.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-400.0, 0, 0.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(500.0, 0, 500.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-800.0, 0, -30.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(550.0, 0, -630.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(800.0, 0, 620.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-300.0, 0, 120.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-800.0, 0, -370.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(570.0, 0, 480.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(100.0, 0, -150.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(300.0, 0, 0.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-400.0, 0, 0.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(500.0, 0, 500.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-800.0, 0, -30.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(550.0, 0, -630.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(800.0, 0, 620.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-300.0, 0, 120.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-800.0, 0, -370.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(570.0, 0, 480.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(100.0, 0, -150.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(300.0, 0, 0.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-400.0, 0, 0.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(500.0, 0, 500.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-800.0, 0, -30.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(550.0, 0, -630.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(800.0, 0, 620.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-300.0, 0, 120.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-800.0, 0, -370.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(570.0, 0, 480.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(100.0, 0, -150.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(300.0, 0, 0.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-400.0, 0, 0.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(500.0, 0, 500.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-800.0, 0, -30.0));
	mEnemyWalkList4.push_back(Ogre::Vector3(-200,0,200));

	//이러한 접근도 가능함 참고
	//mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);
	//Ogre::SceneNode* playernode =  mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode", Ogre::Vector3( 0, 0, 0 ));
	//playernode->attachObject(entNinja);

	mSecondarySceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
}

void TutorialApplication::destroyScene(void)
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

	mInputContext.mKeyboard = mKeyboard;
	mInputContext.mMouse = mMouse;

	mTrayMgr = new SdkTrayManager("InterfaceName", mWindow, mInputContext, this);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
	mTrayMgr->hideCursor();

		mInfoLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Time", "", 150);
		scoreInfoLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "Score", "", 150);
		TitleInfoLabel = mTrayMgr->createLabel(TL_BOTTOM, "Title", "", 500);
		TitleInfoLabel2 = mTrayMgr->createLabel(TL_TOP, "Title2", "Press Enter to Start", 500);
		Health = mTrayMgr->createLabel(TL_LEFT, "HP", "", 200);

		//TitleInfoLabel3 = mTrayMgr->createLabel(TL_CENTER, "Title3", "", 500);
	//TitleInfoLabel3 = mTrayMgr->createLabel(TL_CENTER, "MainTitle", "", 500);

	mRoot->addFrameListener(this);

	Ogre::LogManager::getSingletonPtr()->logMessage("Finished");
}



void TutorialApplication::setupResources(void)
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

void TutorialApplication::createResourceListener(void)
{

}

void TutorialApplication::loadResources(void)
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


bool TutorialApplication::nextLocation()
{
	if (mEnemyWalkList.empty())
		return false;

	mEnemyDestination = mEnemyWalkList.front();
	mEnemyWalkList.pop_front();
	mEnemyDirection = mEnemyDestination - mEnemyNode->getPosition();
	mEnemyDistance = mEnemyDirection.normalise();

	return true;
}

bool TutorialApplication::nextLocation2()
{
	if (mEnemyWalkList2.empty())
		return false;

	mEnemyDestination2 = mEnemyWalkList2.front();
	mEnemyWalkList2.pop_front();
	mEnemyDirection2 = mEnemyDestination2 - mEnemyNode2->getPosition();
	mEnemyDistance2 = mEnemyDirection2.normalise();

	return true;
}


bool TutorialApplication::nextLocation3()
{
	if (mEnemyWalkList3.empty())
		return false;

	mEnemyDestination3 = mEnemyWalkList3.front();
	mEnemyWalkList3.pop_front();
	mEnemyDirection3 = mEnemyDestination3 - mEnemyNode3->getPosition();
	mEnemyDistance3 = mEnemyDirection3.normalise();

	return true;
}


bool TutorialApplication::nextLocation4()
{
	if (mEnemyWalkList4.empty())
		return false;

	mEnemyDestination4 = mEnemyWalkList4.front();
	mEnemyWalkList4.pop_front();
	mEnemyDirection4 = mEnemyDestination4 - mEnemyNode4->getPosition();
	mEnemyDistance4 = mEnemyDirection4.normalise();

	return true;
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
			
			//MessageBox(
			//NULL,
			//e.getFullDescription().c_str(),
			//"An exception has occured!",
			//MB_OK | MB_ICONERROR | MB_TASKMODAL);
			
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