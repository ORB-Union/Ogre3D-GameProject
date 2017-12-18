
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

	//���ӽ��� �Լ���
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
	bool mSecondTitle; // �ΰ��� ����

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

	//��ü��
	Vector3 playerDirection; // �÷��̾�
	SceneNode* mPlayerNode; // �÷��̾�
	Entity* mPlayerEntity; // �÷��̾�

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

	OgreBites::Label* mInfoLabel; // ����ǥ��
	OgreBites::Label* scoreInfoLabel; // ����ǥ��

	OgreBites::Label* TitleInfoLabel; // ����ǥ��
	OgreBites::Label* TitleInfoLabel2; // ����ǥ��

	//OgreBites::Label* TitleInfoLabel3; // ����ǥ��

	OgreBites::Label* Health; // ü��ǥ��

	//OgreBites::Label* TitleInfoLabel3; // ����ǥ��
	/*
	void PlayerBulletMove(const Ogre::FrameEvent& evt);
	void PlayerBulletShoot(SceneManager* mSceneMgr, SceneNode* mSceneNode);
	int playerBullet;
	*/

	//���� ����(ù��° ��)
	std::deque<Ogre::Vector3> mEnemyWalkList;
	Ogre::Vector3 mEnemyDirection;
	Ogre::Vector3 mEnemyDestination;
	Ogre::Real mEnemyWalkSpd;
	Ogre::Entity* mEnemyEntity;
	Ogre::Real mEnemyDistance;
	Ogre::SceneNode* mEnemyNode; // ��
	bool nextLocation(); // ��ġ�ڵ�����
	Ogre::AnimationState* mEnemyAnimationState;

	Ogre::Vector3 HeroPosition1;

	//���� ����(�ι�° ��)
	std::deque<Ogre::Vector3> mEnemyWalkList2; //�ι�°��
	Ogre::Vector3 mEnemyDirection2;
	Ogre::Vector3 mEnemyDestination2;
	Ogre::Real mEnemyWalkSpd2;
	Ogre::Entity* mEnemyEntity2;
	Ogre::Real mEnemyDistance2;
	Ogre::SceneNode* mEnemyNode2; // ��
	bool nextLocation2(); // ��ġ�ڵ�����
	Ogre::AnimationState* mEnemyAnimationState2;

	std::deque<Ogre::Vector3> mEnemyWalkList3; //����°��
	Ogre::Vector3 mEnemyDirection3;
	Ogre::Vector3 mEnemyDestination3;
	Ogre::Real mEnemyWalkSpd3;
	Ogre::Entity* mEnemyEntity3;
	Ogre::Real mEnemyDistance3;
	Ogre::SceneNode* mEnemyNode3; // ��
	bool nextLocation3(); // ��ġ�ڵ�����
	Ogre::AnimationState* mEnemyAnimationState3;

	//int CollisionSphereToSphere(const Vector3* SphereCenter1, float sphereRadius1, const Vector3* SphereCenter2, float sphereRadius2);

	//���� ���ΰ��� �浹
	//bool Enemyheck_Collision(Vector3 xpos, Vector3 zpos);

	//�浹ó������
	//bool spher_collision_check(Vector3 x0, Vector3 z0, float size0, Vector3 x1, Vector3 z1, float size1);

	//�浹 �õ�
	Vector3 ChageDirect;
	void changeDirection();
	SceneNode* HeroNode;
	void HeroHit();

	std::deque<Ogre::Vector3> mEnemyWalkList4; //����°��
	Ogre::Vector3 mEnemyDirection4;
	Ogre::Vector3 mEnemyDestination4;
	Ogre::Real mEnemyWalkSpd4;
	Ogre::Entity* mEnemyEntity4;
	Ogre::Real mEnemyDistance4;
	Ogre::SceneNode* mEnemyNode4; // ��
	bool nextLocation4(); // ��ġ�ڵ�����
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