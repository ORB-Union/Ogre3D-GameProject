
#ifndef PLAYER_H
#define PLAYER_H
#include"TutorialApplication.h"

using namespace Ogre;
using namespace OgreBites;



class Player
{
public :
	Player();
	~Player();
	void CreatePlayerCamera(void);
	void AddToScene(SceneManager* mSceneMgr);
	void PlayerKeyPress(const OIS::KeyEvent& ke);
	void PlayerKeyRealease(const OIS::KeyEvent& ke);
	void PlayerMove(const Ogre::FrameEvent& fe);
	void PlayerToCamera(SceneManager* mSceneMgr, Camera *mCamera);

private :

	int HP;
	bool Death;

	Real playermove;
	Real playerrotate;
	//��ü��
	SceneNode* mPlayerNode; // �÷��̾�
	Vector3 playerDirection; // �÷��̾�
	Entity* mPlayerEntity; // �÷��̾�
	
	SceneNode* mCameraNode;
	Vector3 mPlayerPosition;

	AnimationState* mPlayerAnimationState;
};

#endif
