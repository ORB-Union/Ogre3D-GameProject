
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include<OgreRoot.h>
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
#include <OgreConfigFile.h>
#include<OgreParticle.h>
#include <OgreResourceGroupManager.h>
#include <OgreColourValue.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include<stdio.h>
#include<Ogre.h>
#include<vector>
#include <SdkCameraMan.h>
#include<SdkTrays.h>
#include<OgreSceneQuery.h>
#include<time.h>

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif


using namespace Ogre;
using namespace OgreBites;


class TutorialApplication
	: public Ogre::WindowEventListener,
	public Ogre::FrameListener,
	public OIS::KeyListener,
	public OIS::MouseListener,
	public OgreBites::SdkTrayListener
	//public OIS::MouseListener
{
public:
	TutorialApplication();
	virtual ~TutorialApplication();
	void go();

protected :

	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual void InGame(const Ogre::FrameEvent& fe);

	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

	virtual void setupViewport(Ogre::SceneManager *curr);
	virtual void dualViewport(Ogre::SceneManager *primarySceneMgr, Ogre::SceneManager *secondarySceneMgr);

	//virtual void setupViewport(Ogre::SceneManager *curr);
	//virtual void dualViewport(Ogre::SceneManager *primarySceneMgr, Ogre::SceneManager* secondarySceneMgr);

	//bool isCollision(const Ogre::Vector3& position, const Ogre::Vector3& direction);

	//게임실행 함수들
	bool setup();
	bool configure(void);

	bool pause;

	virtual void createFrameListener(void);
	void createCamera(void);
	void createScene(void);
	void destroyScene(void);
	void setupResources(void);
	void createResourceListener(void);
	void loadResources(void);

	void createViewports(void);

	void chooseSceneManager(void);

	bool mShutdown;
	bool mSecondTitle; // 인게임 여부

	bool Death;

	Root* mRoot;
	String mResourcesCfg;
	String mPluginsCfg;
	RenderWindow* mWindow;
	Camera* mCamera;
	SdkCameraMan* mCameraMan;

	//std::stringstream PlayerbulletsName;

	InputContext mInputContext;
	SdkTrayManager*	mTrayMgr;

	SceneManager* mSceneMgr;
	SceneManager* mSecondarySceneMgr;

	//개체들
	Vector3 playerDirection; // 플레이어
	SceneNode* mPlayerNode; // 플레이어
	Entity* mPlayerEntity; // 플레이어

	AnimationState* mPlayerAnimationState;

	SceneNode* mCameraNode;

	SceneNode* mEnemyparticleNode1;
	SceneNode* mEnemyparticleNode2;
	SceneNode* mEnemyparticleNode3;
	SceneNode* mEnemyparticleNode4;

	Vector3 mPlayerPosition;
	Quaternion mPlayerOrientation;
	Vector3 mPlayerScale;
	Real playermove;
	Real playerrotate;

	int PlayerScore;

	int HP;

	int Enemy_HP;
	Ogre::OverlaySystem*        mOverlaySystem;
	//Ogre::OverlaySystem*        mOverlaySystem2;

	OgreBites::Label* mInfoLabel; // 정보표시
	OgreBites::Label* scoreInfoLabel; // 정보표시

	OgreBites::Label* TitleInfoLabel; // 정보표시
	OgreBites::Label* TitleInfoLabel2; // 정보표시

	//OgreBites::Label* TitleInfoLabel3; // 정보표시

	OgreBites::Label* Health; // 체력표시

	//OgreBites::Label* TitleInfoLabel3; // 정보표시
	/*
	void PlayerBulletMove(const Ogre::FrameEvent& evt);
	void PlayerBulletShoot(SceneManager* mSceneMgr, SceneNode* mSceneNode);
	int playerBullet;
	*/

	//적의 정보(첫번째 적)
	std::deque<Ogre::Vector3> mEnemyWalkList;
	Ogre::Vector3 mEnemyDirection;
	Ogre::Vector3 mEnemyDestination;
	Ogre::Real mEnemyWalkSpd;
	Ogre::Entity* mEnemyEntity;
	Ogre::Real mEnemyDistance;
	Ogre::SceneNode* mEnemyNode; // 적
	bool nextLocation(); // 위치자동변경
	Ogre::AnimationState* mEnemyAnimationState;

	Ogre::Vector3 HeroPosition1;

	//적의 정보(두번째 적)
	std::deque<Ogre::Vector3> mEnemyWalkList2; //두번째적
	Ogre::Vector3 mEnemyDirection2;
	Ogre::Vector3 mEnemyDestination2;
	Ogre::Real mEnemyWalkSpd2;
	Ogre::Entity* mEnemyEntity2;
	Ogre::Real mEnemyDistance2;
	Ogre::SceneNode* mEnemyNode2; // 적
	bool nextLocation2(); // 위치자동변경
	Ogre::AnimationState* mEnemyAnimationState2;

	std::deque<Ogre::Vector3> mEnemyWalkList3; //세번째적
	Ogre::Vector3 mEnemyDirection3;
	Ogre::Vector3 mEnemyDestination3;
	Ogre::Real mEnemyWalkSpd3;
	Ogre::Entity* mEnemyEntity3;
	Ogre::Real mEnemyDistance3;
	Ogre::SceneNode* mEnemyNode3; // 적
	bool nextLocation3(); // 위치자동변경
	Ogre::AnimationState* mEnemyAnimationState3;

	//int CollisionSphereToSphere(const Vector3* SphereCenter1, float sphereRadius1, const Vector3* SphereCenter2, float sphereRadius2);

	//적이 주인공과 충돌
	//bool Enemyheck_Collision(Vector3 xpos, Vector3 zpos);

	//충돌처리조건
	//bool spher_collision_check(Vector3 x0, Vector3 z0, float size0, Vector3 x1, Vector3 z1, float size1);

	//충돌 시도
	Vector3 ChageDirect;
	void changeDirection();
	SceneNode* HeroNode;
	void HeroHit();

	std::deque<Ogre::Vector3> mEnemyWalkList4; //세번째적
	Ogre::Vector3 mEnemyDirection4;
	Ogre::Vector3 mEnemyDestination4;
	Ogre::Real mEnemyWalkSpd4;
	Ogre::Entity* mEnemyEntity4;
	Ogre::Real mEnemyDistance4;
	Ogre::SceneNode* mEnemyNode4; // 적
	bool nextLocation4(); // 위치자동변경
	Ogre::AnimationState* mEnemyAnimationState4;

	Ogre::SceneNode* mSpotlightNode1;

	Ogre::RaySceneQuery *mRaySceneQuery;

	//Ogre::MeshManager* mMeshMgr;
	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;	
};



#ifdef OGRE_STATIC_LIB
	Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif


#endif