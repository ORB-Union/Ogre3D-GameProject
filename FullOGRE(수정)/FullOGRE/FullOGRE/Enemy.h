/*
#ifndef ENEMY_H
#define ENEMY_H
#include"TutorialApplication.h"

using namespace Ogre;
using namespace OgreBites;


class Enemy
{
public :
	Enemy();
	~Enemy();
	void AddToScene();
	void EnemyMoveAI();

private :

	int Enemy_HP;

	SceneNode* mEnemyparticleNode1;
	SceneNode* mEnemyparticleNode2;
	SceneNode* mEnemyparticleNode3;
	SceneNode* mEnemyparticleNode4;

	std::deque<Ogre::Vector3> mEnemyWalkList4; //세번째적
	Ogre::Vector3 mEnemyDirection4;
	Ogre::Vector3 mEnemyDestination4;
	Ogre::Real mEnemyWalkSpd4;
	Ogre::Entity* mEnemyEntity4;
	Ogre::Real mEnemyDistance4;
	Ogre::SceneNode* mEnemyNode4; // 적
	bool nextLocation4(); // 위치자동변경
	Ogre::AnimationState* mEnemyAnimationState4;

	std::deque<Ogre::Vector3> mEnemyWalkList;
	Ogre::Vector3 mEnemyDirection;
	Ogre::Vector3 mEnemyDestination;
	Ogre::Real mEnemyWalkSpd;
	Ogre::Entity* mEnemyEntity;
	Ogre::Real mEnemyDistance;
	Ogre::SceneNode* mEnemyNode; // 적
	bool nextLocation(); // 위치자동변경
	Ogre::AnimationState* mEnemyAnimationState;

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

};


#endif
*/