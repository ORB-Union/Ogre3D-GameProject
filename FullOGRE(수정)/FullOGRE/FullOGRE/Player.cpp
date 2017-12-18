/*
#include"TutorialApplication.h"
#include"Player.h"

#define CAMERA_NAME "SceneCamera"

using namespace Ogre;
using namespace OgreBites;


Player::Player() : playermove(400), mPlayerNode(0),  playerrotate(1), playerDirection(Vector3::ZERO), mPlayerPosition(Vector3::ZERO), HP(100), Death(false), mPlayerEntity(0), mCameraNode(0), mPlayerAnimationState(0)
{
}
Player::~Player()
{

}

void Player::AddToScene(SceneManager* mSceneMgr)
{
	//플레이어
	mPlayerEntity = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	mPlayerEntity->setCastShadows(true);
	Ogre::SceneNode* mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("playernode");
	//바운딩박스
	mPlayerNode->showBoundingBox(true);
	AxisAlignedBox box = mPlayerEntity->getBoundingBox();
	mPlayerNode->setPosition(-150,-box.getCorner(AxisAlignedBox::FAR_LEFT_BOTTOM).y,150);
	mPlayerNode->setScale(1.5f,1.5f,1.5f);
	mPlayerNode->attachObject(mPlayerEntity);
}


void Player::PlayerToCamera(SceneManager* mSceneMgr, Camera *mCamera)
{
	mPlayerAnimationState = mPlayerEntity->getAnimationState("Idle2");
	mPlayerAnimationState->setLoop(true);
	mPlayerAnimationState->setEnabled(true);

	mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerCamNode", Ogre::Vector3(2000,1000,2000));
	//mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerCamNode", Ogre::Vector3(500,500,1000));
	mPlayerNode->yaw(Degree(-35));
	mPlayerNode->pitch(Degree(-20));
	mCameraNode = mPlayerNode;
	mPlayerNode->attachObject(mCamera);

	mCamera->setPosition(Ogre::Vector3(1000, 500, 1000));//현 카메라 좌표는 2000,1000,2000
	mCamera->lookAt(Ogre::Vector3(playerDirection.x+500, playerDirection.y+500, playerDirection.z+500));
	mCamera->setNearClipDistance(20);
}


void Player::PlayerKeyPress(const OIS::KeyEvent& ke)
{
	if(!Death)
	{
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
}


void Player::PlayerKeyRealease(const OIS::KeyEvent& ke)
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
}


void Player::PlayerMove(const Ogre::FrameEvent& fe)
{	
	if(HP<= 0)
	{
		HP = 0;
		mPlayerAnimationState = mPlayerEntity->getAnimationState("Death1");
		mPlayerAnimationState->setEnabled(true);
		mPlayerAnimationState->setLoop(false);
		Death = true;

	}

	mPlayerNode->translate(playerDirection *fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	if(!Death)
	{
		mCameraNode->translate(playerDirection *fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	}
	mPlayerAnimationState->addTime(fe.timeSinceLastFrame);
}
*/