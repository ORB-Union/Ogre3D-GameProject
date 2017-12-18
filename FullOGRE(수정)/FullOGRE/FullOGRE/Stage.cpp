#include"Stage.h"
using namespace Ogre;

Stage::Stage(SceneManager *stage)
{
	sceneManagerstage = stage;
}

void Stage::addToScene()
{
	//기본적 배치를 위한 라이트
	//Ogre::Light* light = mSceneMgr->createLight("Ma	inLight");
	//light->setPosition(300, 300, -300);


	//스테이지 배치
	// Create a plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane("plane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		5000,5000,200,200,true, 1,3,3,Vector3::UNIT_Z);
	Ogre::Entity* ent = sceneManagerstage->createEntity("LightPlaneEntity", "plane");
	sceneManagerstage->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
	ent->setMaterialName("Examples/BeachStones");
	Ogre::SceneNode* node = sceneManagerstage->createSceneNode("Node1");
	sceneManagerstage->getRootSceneNode()->addChild(node);
	ent->setCastShadows(false);


	//왼쪽위
	Entity* minihouseEntity = sceneManagerstage->createEntity("Housekolodec_01.mesh");
	SceneNode* minihousenode1 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("minihousenode1");
	minihousenode1->setPosition(-1000,0,-1700);
	minihousenode1->setScale(1500.0f,1500.0f,1500.0f);
	minihousenode1->yaw(Degree(-45));
	minihousenode1->roll(Degree(-90));
	minihousenode1->attachObject(minihouseEntity);
	minihouseEntity->setCastShadows(true);


	//단순 오브젝트인 집들 세팅
	//왼쪽 위
	Entity* houseEntity = sceneManagerstage->createEntity("tudorhouse.mesh");
	SceneNode* housenode1 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("housenode1");
	housenode1->setPosition(-1300,250,-1100);
	housenode1->setScale(0.5f,0.5f,0.5f);
	housenode1->yaw(Degree(45));
	housenode1->attachObject(houseEntity);
	houseEntity->setCastShadows(true);
	
	//오른쪽 위
	Entity* houseEntity2 = sceneManagerstage->createEntity("tudorhouse.mesh");
	SceneNode* housenode2 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("housenode2");
	housenode2->setPosition(1300,250,-1100);
	housenode2->setScale(0.5f,0.5f,0.5f);
	housenode2->yaw(Degree(-45));
	housenode2->attachObject(houseEntity2);
	houseEntity2->setCastShadows(true);



	//오른쪽 위
	Entity* minihouseEntity2 = sceneManagerstage->createEntity("Housekolodec_01.mesh");
	SceneNode* minihousenode2 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("minihousenode2");
	minihousenode2->setPosition(1000,0,-1700);
	minihousenode2->setScale(1500.0f,1500.0f,1500.0f);
	minihousenode2->yaw(Degree(45));
	minihousenode2->roll(Degree(-90));
	minihousenode2->attachObject(minihouseEntity2);
	minihouseEntity2->setCastShadows(true);

	
	//왼쪽 아래
	Entity* houseEntity3 = sceneManagerstage->createEntity("tudorhouse.mesh");
	SceneNode* housenode3 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("housenode3");
	housenode3->setPosition(-1300,250,1100);
	housenode3->setScale(0.5f,0.5f,0.5f);
	housenode3->yaw(Degree(135));
	housenode3->attachObject(houseEntity3);
	houseEntity3->setCastShadows(true);
	
	//왼쪽 아래
	Entity* minihouseEntity3 = sceneManagerstage->createEntity("Housekolodec_01.mesh");
	SceneNode* minihousenode3 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("minihousenode3");
	minihousenode3->setPosition(-1000,0,1700);
	minihousenode3->setScale(1500.0f,1500.0f,1500.0f);
	minihousenode3->yaw(Degree(-135));
	minihousenode3->roll(Degree(-90));
	minihousenode3->attachObject(minihouseEntity3);
	minihouseEntity3->setCastShadows(true);

	//오른쪽 아래
	Entity* houseEntity4 = sceneManagerstage->createEntity("tudorhouse.mesh");
	SceneNode* housenode4 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("housenode4");
	housenode4->setPosition(1300,250,1100);
	housenode4->setScale(0.5f,0.5f,0.5f);
	housenode4->yaw(Degree(-135));
	housenode4->attachObject(houseEntity4);
	houseEntity4->setCastShadows(true);


	//오른쪽 아래
	Entity* minihouseEntity4 = sceneManagerstage->createEntity("Housekolodec_01.mesh");
	SceneNode* minihousenode4 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("minihousenode4");
	minihousenode4->setPosition(1000,0,1700);
	minihousenode4->setScale(1500.0f,1500.0f,1500.0f);
	minihousenode4->yaw(Degree(135));
	minihousenode4->roll(Degree(-90));
	minihousenode4->attachObject(minihouseEntity4);
	minihouseEntity4->setCastShadows(true);
	
	//맵에 배치할 라이트 생성
	Ogre::Light* light = sceneManagerstage->createLight("DLight");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(Ogre::ColourValue(0.15f,0.15f,0.15f));
	light->setDirection(0,-1,0);

	//왼쪽 위
	//라이트1
	Ogre::Light* light1 = sceneManagerstage->createLight("Light1");
	light1->setType(Ogre::Light::LT_SPOTLIGHT);
	light1->setDirection(Ogre::Vector3(0, -1, 0));
	light1->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	light1->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	light1->setSpotlightOuterAngle(Ogre::Degree(115.0f));

	Ogre::SceneNode* lightnode1 = node->createChildSceneNode("lightnode1");
	lightnode1->setPosition(600, 250, 600);
	lightnode1->attachObject(light1);

	Ogre::Entity* lightEnt1 = sceneManagerstage->createEntity("LightEntity1","sphere.mesh");
	Ogre::SceneNode* lightentnode1 = lightnode1->createChildSceneNode("lightentnode1");
	lightEnt1->setMaterialName("Examples/BumpyMetal");
	lightentnode1->setScale(0.1f, 0.1f, 0.1f);
	lightentnode1->attachObject(lightEnt1);

	ParticleSystem* lightparticle1 =  sceneManagerstage->createParticleSystem("LightParticle1", "Space/Sun");
	SceneNode* lightparticlenode1 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("lightparticlenode1");
	lightparticlenode1->setPosition(600,250,600);
	lightparticlenode1->attachObject(lightparticle1);
	 
	//왼쪽위 라이트 기둥
	Ogre::Entity* leftupPillar = sceneManagerstage->createEntity("leftupPillar", Ogre::SceneManager::PT_CUBE);
	leftupPillar->setMaterialName("Examples/Chrome");
	lightnode1 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("leftupPillarnode", Ogre::Vector3(600,105,600));
	lightnode1->setScale(0.3f,2.5f,0.3f);
	lightnode1->attachObject(leftupPillar);
	leftupPillar->setCastShadows(false);

	/*
	leftupPillarNode->setPosition(0, 7.5, -100);
	leftupPillarNode->setScale(4.0f, 0.25f, 0.1f);
	*/

	/*
	//중앙
	//라이트2
	Ogre::Light* light2 = sceneManagerstage->createLight("Light2");
	light2->setType(Ogre::Light::LT_SPOTLIGHT);
	light2->setDirection(Ogre::Vector3(0, -1, 0));
	light2->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	light2->setSpotlightInnerAngle(Ogre::Degree(10.0f));
	light2->setSpotlightOuterAngle(Ogre::Degree(180.0f));

	Ogre::SceneNode* lightnode2 = node->createChildSceneNode("lightnode2");
	lightnode2->setPosition(0, 250, 0);
	lightnode2->attachObject(light2);

	Ogre::Entity* lightEnt2 = sceneManagerstage->createEntity("LightEntity2","sphere.mesh");
	lightEnt2->setMaterialName("Examples/BumpyMetal");
	Ogre::SceneNode* lightentnode2 = lightnode2->createChildSceneNode("lightentnode2");
	lightentnode2->setScale(0.13f, 0.13f, 0.13f);
	lightentnode2->attachObject(lightEnt2);



	//파티클
	ParticleSystem* lightparticle2 =  sceneManagerstage->createParticleSystem("LightParticle2", "Space/Sun");
	SceneNode* lightparticlenode2 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("lightparticlenode2");
	lightparticlenode2->setPosition(0,250,0);
	lightparticlenode2->attachObject(lightparticle2);

	//중앙 기둥
	Ogre::Entity* MidPillar = sceneManagerstage->createEntity("MidPillar", Ogre::SceneManager::PT_CUBE);
	MidPillar->setMaterialName("Examples/Chrome");
	lightnode2 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("MidPillarnode", Ogre::Vector3(0,105,0));
	lightnode2->setScale(0.3f,2.5f,0.3f);
	lightnode2->attachObject(MidPillar);
	MidPillar->setCastShadows(false);
	*/
	
	//오른쪽 아래
	//라이트3
	Ogre::Light* light3 = sceneManagerstage->createLight("Light3");
	light3->setType(Ogre::Light::LT_SPOTLIGHT);
	light3->setDirection(Ogre::Vector3(0, -1, 0));
	light3->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	light3->setSpotlightInnerAngle(Ogre::Degree(4.5f));
	light3->setSpotlightOuterAngle(Ogre::Degree(130.0f));

	Ogre::SceneNode* lightnode3 = node->createChildSceneNode("lightnode3");
	lightnode3->setPosition(-800, 250, -800);
	lightnode3->attachObject(light3);

	//파티클
	ParticleSystem* lightparticle3 =  sceneManagerstage->createParticleSystem("LightParticle3", "Space/Sun");
	SceneNode* lightparticlenode3 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("lightparticlenode3");
	lightparticlenode3->setPosition(-800,250,-800);
	lightparticlenode3->attachObject(lightparticle3);

	Ogre::Entity* lightEnt3 = sceneManagerstage->createEntity("LightEntity3","sphere.mesh");
	lightEnt3->setMaterialName("Examples/BumpyMetal");
	Ogre::SceneNode* lightentnode3 = lightnode3->createChildSceneNode("lightentnode3");
	lightentnode3->setScale(0.13f, 0.13f, 0.13f);
	lightentnode3->attachObject(lightEnt3);


	//오른쪽 아래 기둥
	Ogre::Entity* RightDownPillar = sceneManagerstage->createEntity("RightDownPillar", Ogre::SceneManager::PT_CUBE);
	RightDownPillar->setMaterialName("Examples/Chrome");
	lightnode3 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("RightDownPillarnode", Ogre::Vector3(-800,105,-800));
	lightnode3->setScale(0.3f,2.5f,0.3f);
	lightnode3->attachObject(RightDownPillar);
	RightDownPillar->setCastShadows(false);


	
	//왼쪽 아래
	//라이트4
	Ogre::Light* light4 = sceneManagerstage->createLight("Light4");
	light4->setType(Ogre::Light::LT_SPOTLIGHT);
	light4->setDirection(Ogre::Vector3(0, -1, 0));
	light4->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	light4->setSpotlightInnerAngle(Ogre::Degree(4.5f));
	light4->setSpotlightOuterAngle(Ogre::Degree(130.0f));

	Ogre::SceneNode* lightnode4 = node->createChildSceneNode("lightnode4");
	lightnode4->setPosition(-800, 250, 800);
	lightnode4->attachObject(light4);

	Ogre::Entity* lightEnt4 = sceneManagerstage->createEntity("LightEntity4","sphere.mesh");
	lightEnt4->setMaterialName("Examples/BumpyMetal");
	Ogre::SceneNode* lightentnode4 = lightnode4->createChildSceneNode("lightentnode4");
	lightentnode4->setScale(0.13f, 0.13f, 0.13f);
	lightentnode4->attachObject(lightEnt4);

	////파티클
	ParticleSystem* lightparticle4 =  sceneManagerstage->createParticleSystem("LightParticle4", "Space/Sun");
	SceneNode* lightparticlenode4 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("lightparticlenode4");
	lightparticlenode4->setPosition(-800,250,800);
	lightparticlenode4->attachObject(lightparticle4);

	//왼쪽 아래 기둥
	Ogre::Entity* LeftDownPillar = sceneManagerstage->createEntity("LeftDownPillar", Ogre::SceneManager::PT_CUBE);
	LeftDownPillar->setMaterialName("Examples/Chrome");
	lightnode4 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("LeftDownPillarnode", Ogre::Vector3(-800,105,800));
	lightnode4->setScale(0.3f,2.5f,0.3f);
	lightnode4->attachObject(LeftDownPillar);
	LeftDownPillar->setCastShadows(false);

	//라이트5
	//오른쪽 위
	Ogre::Light* light5 = sceneManagerstage->createLight("Light5");
	light5->setType(Ogre::Light::LT_SPOTLIGHT);
	light5->setDirection(Ogre::Vector3(0, -1, 0));
	light5->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	light5->setSpotlightInnerAngle(Ogre::Degree(4.5f));
	light5->setSpotlightOuterAngle(Ogre::Degree(130.0f));

	Ogre::SceneNode* lightnode5 = node->createChildSceneNode("lightnode5");
	lightnode5->setPosition(600, 250, -600);
	lightnode5->attachObject(light5);

	//파티클
	ParticleSystem* lightparticle5 =  sceneManagerstage->createParticleSystem("LightParticle5", "Space/Sun");
	SceneNode* lightparticlenode5 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("lightparticlenode5");
	lightparticlenode5->setPosition(600,250,-600);
	lightparticlenode5->attachObject(lightparticle5);

	Ogre::Entity* lightEnt5 = sceneManagerstage->createEntity("LightEntity5","sphere.mesh");
	lightEnt5->setMaterialName("Examples/BumpyMetal");
	Ogre::SceneNode* lightentnode5 = lightnode5->createChildSceneNode("lightentnode5");
	lightentnode5->setScale(0.13f, 0.13f, 0.13f);
	lightentnode5->attachObject(lightEnt5);

	//오른쪽 위 기둥
	Ogre::Entity* RightUpPillar = sceneManagerstage->createEntity("RightUpPillar", Ogre::SceneManager::PT_CUBE);
	RightUpPillar->setMaterialName("Examples/Chrome");
	lightnode5 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("RightUpPillarnode", Ogre::Vector3(600,105,-600));
	lightnode5->setScale(0.3f,2.5f,0.3f);
	lightnode5->attachObject(RightUpPillar);
	RightUpPillar->setCastShadows(false);

	//왼쪽중앙
	Entity* middlehouseEntity = sceneManagerstage->createEntity("HouseLPBuildX12.mesh");
	SceneNode* middlehousenode1 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("middlehousenode1");
	middlehousenode1->setPosition(-2000,175,0);
	middlehousenode1->setScale(250.0f,250.0f,250.0f);
	middlehousenode1->yaw(Degree(90));
	//middlehousenode1->roll(Degree(-90));
	middlehousenode1->attachObject(middlehouseEntity);
	middlehouseEntity->setCastShadows(true);

	//오른쪽 중앙
	Entity* middlehouseEntity2 = sceneManagerstage->createEntity("HouseLPBuildX12.mesh");
	SceneNode* middlehousenode2 = sceneManagerstage->getRootSceneNode()->createChildSceneNode("middlehousenode2");
	middlehousenode2->setPosition(2000,175,0);
	middlehousenode2->setScale(250.0f,250.0f,250.0f);
	middlehousenode2->yaw(Degree(-90));
	//middlehousenode1->roll(Degree(-90));
	middlehousenode2->attachObject(middlehouseEntity2);
	middlehouseEntity2->setCastShadows(true);
}