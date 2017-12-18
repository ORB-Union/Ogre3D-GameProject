/*
#ifndef BULLET_H
#define BULLET_H
#include"TutorialApplication.h"
using namespace Ogre;
using namespace OgreBites;

class Bullet
{
private :
	int Attack;
	Vector3 Bulletposition;
	Vector3 Bulletdirection;
	SceneNode *BullNode;
	Entity* BullEnt;

public :
	Bullet(SceneManager* bullSceneManeger, Vector3 Bullpos, std::string BullName , Vector3 Bulldirect);
	void BulletMove(const FrameEvent& evt);
};


#endif

*/