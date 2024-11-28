//
// 3D Game Programming
// 
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
//
// Purpose: Set the scenes. 
//
//
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"

#include "OgreTerrainGroup.h"
//#include "LegacyTerrainLoader.h"
//#include "HeightFunction.h"

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreApplicationContext.h"
#include "TutorialApplication.h"
#include "BasicTools.h"

#include "myTerrain.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

#include "SystemParameter.h"

//#include "terrain.h"

using namespace Ogre;


void BasicTutorial_00::placeGroup_OnTerrain() {
	for (int i = 0; i < mNumofObjects; ++i)
	{
		placeOnTerrain(mSceneNodeArr[i]);
	}
}

void BasicTutorial_00::placeOnTerrain(SceneNode *node) {
	
	    Vector3 p = node->getPosition();
		Vector3 q;
		if (mMyTerrain)  q = mMyTerrain->getTerrainSurfacePoint(p);
		else q = p;

	    node->setPosition(q);
	
}

void BasicTutorial_00::createLights( ) 
{

    mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);

   // return;

    mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

    LightConstruct* lightC = new LightConstruct(mSceneMgr);
    // 
//    light = mSceneMgr->createLight("Light1"); 
    lightC->light->setType(Light::LT_POINT);
    lightC->setPosition(Vector3(0, 250, 50) + mGamePosition);
	//lightC->setDiffuseColour(0.85, 0.85, 0.85);
	lightC->setDiffuseColour(0.5, 0.5, 0.5);
    lightC->setSpecularColour(1.0, 1.0, 1.0);
    mLightContruct[0] = lightC;

    //lightC = createPointLight(mSceneMgr, "Light2");
    lightC = new LightConstruct(mSceneMgr);
    lightC->light->setType(Light::LT_POINT);
    lightC->setPosition(Vector3(150, 300, 150) + mGamePosition);
	//lightC->setDiffuseColour(0.85, 0.85, 0.85);
	lightC->setDiffuseColour(0.5, 0.5, 0.5);
    lightC->setSpecularColour(1.0, 1.0, 1.0);	
    mLightContruct[1] = lightC;

}

void BasicTutorial_00::createScene_Setup_FX(void) {
	initParticleSystemForExplosion();
	Vector3 pos;
	pos = mSceneNodeArr[0]->getPosition();
	setOffParticleSystem(mParticleNode, "explosion", pos);


	mFXManager = new SpecialEffectManager(
		mSceneMgr,
		SystemParameter::maxNumParticleSystems);

	mFXManager->init();

	for (int i = 0;
		i < mFXManager->getNumParticleSystems();
		++i) {
		if (i >= mNumofObjects) break;

		/*mFXManager->setOffParticleSystem(
			position of mSceneNodeArr[i]
		);*/
	}
}

//
//
//
void BasicTutorial_00::setFog()
{
	ColourValue fadeColour(0.0, 0.9, 0.0);
	if (mEnabledFog) {
		mSceneMgr->setFog(FOG_LINEAR, fadeColour, 0, 50, 20000);
	}
	else {
		// add your own stuff
	}

}
void BasicTutorial_00::createScene_Setup(void)
{

	setFog();
	mSceneMgr->setSkyBox(
		true
		//,"Examples/CloudySky"
		//"Examples/EveningSkyBox"
		//"Examples/MorningCubeMap"
		//"Examples/SceneSkyBox1"
		, READER_DATA::getMaterialName_SkyBox()
		, 2000
	);
	//"Examples/SpaceSkyBox");
	//"Examples/EarlyMorningSkyBox");
	PlaneBoundedVolumeList volList;
	mVolQuery = mSceneMgr->createPlaneBoundedVolumeQuery(volList);

	mSceneMgr->setAmbientLight(ColourValue(0.9, 0.9, 0.9));
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
	//mSceneMgr->setShadowTechnique(
	//	SHADOWTYPE_STENCIL_ADDITIVE);

	mSelectionRect = new SelectionRectangle("selectionRect");
	mSceneMgr->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(mSelectionRect);
	mSelectionRect->setLightMask(0);
	mSelectionRect->setCastShadows(false);




	mPetCounter = new DIGIT_STRING_DIALOGUE(mSceneMgr);

	mFlgSelectNow = false;


}

//void BasicTutorial_00::createLights()
//{
//	//
//	Light* light = mSceneMgr->createLight("Light1");
//	light->setType(Light::LT_POINT);
//	light->setPosition(Vector3(0, 150, 250));
//	light->setDiffuseColour(1.0, 1.0, 1.0);		//red
//	light->setSpecularColour(0.5, 0.5, 0.5);	//red
//	mLight_Point = light;
//	/*
//	light = mSceneMgr->createLight("Light2");
//	light->setType(Light::LT_POINT);
//	light->setPosition(Vector3(0, 550, 250));
//	light->setDiffuseColour(0.0, 0.25, 0.0);		//red
//	light->setSpecularColour(0.0, 0.25, 0.0);	//red
//	*/
//	mLightSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//	mLightSceneNode->attachObject(light);
//}


// Add your own stuff or modify
void BasicTutorial_00::createPlaneObjectResource()
{
	//
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"ground_00", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1800, 1800, 	// width, height
		20, 20, 		// x- and y-segments
		true, 		// normal
		1, 		// num texture sets
		5, 5, 		// x- and y-tiles
		Vector3::UNIT_Z	// upward vector
	);

}

// Add your own stuff or modify
void BasicTutorial_00::createGround()
{
	Entity* ent = nullptr;
	ent = mSceneMgr->createEntity(
		"GroundEntity_02", "ground_00");
	ent->setMaterialName("Examples/BeachStones");
	ent->setQueryFlags(0x0);

	mSceneNode_Ground = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(Vector3(0.0, -30.0, 0.0));

	mSceneNode_Ground->attachObject(ent);
	mEntity_Ground = ent;
	
	mSceneNode_Ground->setPosition(mGamePosition + Vector3(0, -200, 0));
	mSceneNode_Ground->translate(Vector3(0, -20, 0));
	
}

// Add your own stuff or modify
void BasicTutorial_00::createFloor()
{
	Entity* ent = nullptr;

	ent = mSceneMgr->createEntity(
		"GroundEntity_03", "ground_00");
	ent->setMaterialName(READER_DATA::getWaterMaterialName());
	//ent->setMaterialName("Examples/Rocky");
	ent->setQueryFlags(0x0);

	mSceneNode_Floor = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode();

	mSceneNode_Floor->attachObject(ent);
	mEntity_Floor = ent;

	mSceneNode_Floor->setPosition(mGamePosition + Vector3(0, -200,0));

}

//
// Add your own stuff or modify
//
void BasicTutorial_00::createSphere()
{
	mSphere_Position = Vector3(0.0, 0.0, 0.0);
	SceneNode* sphere_scn = mSphere_Node = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	sphere_scn->setPosition(mGamePosition);

	Entity* sphere_ent
		= mSceneMgr
		->createEntity("s", "sphere.mesh");
	sphere_scn->attachObject(sphere_ent);
	auto bb = sphere_ent->getBoundingBox();
	Real sizeX = bb.getMaximum().x - bb.getMinimum().x;
	Real sf = 2 * mSphere_Radius / sizeX;
	/*Real sf = 10.0;*/
	sphere_scn->scale(sf, sf, sf);
	sphere_ent->setMaterialName("Examples/SphereMappedRustySteel");

	sphere_scn->translate( Vector3(0, -200, 0 ));
	mSphere_Position = sphere_scn->getPosition();
}

//
// Add your own stuff or modify
//
void BasicTutorial_00::createObjects()
{
	int i;
	std::string petMeshName = READER_DATA::getMeshName_Pet();
	float scale = READER_DATA::getMeshScale_Pet();
	float yaw_angle_offset = READER_DATA::getYawAngleDegreeOffset_Pet();

	mNumofObjects = 0;
	int numRobots = 25;
	Real r = 350;
	for (int k = 0; k < numRobots; ++k, ++mNumofObjects)
	{
		i = k;
		String name;
		genNameUsingIndex("robot_", i, name);

		mEntityArr[i]
			= mSceneMgr
			->createEntity(name, petMeshName);

		mEntityArr[i]->setVisibilityFlags(VIS_MASK_MINMAP);


		mAnimationStateArr[i] = mEntityArr[i]->getAnimationState("Idle");
		mMotionStateArr[i] = MOTION_TYPE_IDLE;

		mAnimationStateArr[i]->setEnabled(true);
		mAnimationStateArr[i]->setLoop(true);

		mSceneNodeArr[i]
			= mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode();

		Vector3 p;
		Real a = i / (Real)numRobots * PI * 2.0;
		p.x = r * cos(a);
		p.z = r * sin(a);

		p.y = 0.0;

		p = p + mGamePosition;

		mSceneNodeArr[i]->setPosition(p);
		//
		Vector3 robotLookAtPosition;
		robotLookAtPosition.y = mSceneNodeArr[i]->getPosition().y;
		mSceneNodeArr[i]->lookAt(robotLookAtPosition, Node::TS_WORLD);
		//mSceneNodeArr[i]->yaw(Degree(90));
		mSceneNodeArr[i]->yaw(Degree(yaw_angle_offset));
		//
		mSceneNodeArr[i]->attachObject(mEntityArr[i]);

		mSceneNodeArr[i]->setScale(scale, scale, scale);

		auto bb = mEntityArr[i]->getBoundingBox();
		Real sizeX = bb.getMaximum().x - bb.getMinimum().x;
		
		mObject_radius = scale*sizeX / 2.0;
		//mObject_radius = mObject_radius;

		if (i == 0) {
			mSceneNodeArr[i]->setScale(2, 2, 2);
		}
	}

	r = 250;
	for (int k = 0; k < numRobots; ++k, ++mNumofObjects)
	{
		i = k + numRobots;
		String name;
		genNameUsingIndex("robot_inside_", i, name);

		mEntityArr[i]
			= mSceneMgr
			->createEntity(name, "robot.mesh");
		mEntityArr[i]->setVisibilityFlags(VIS_MASK_MINMAP);

		mAnimationStateArr[i] = mEntityArr[i]->getAnimationState("Idle");
		mMotionStateArr[i] = MOTION_TYPE_IDLE;

		mAnimationStateArr[i]->setEnabled(true);
		mAnimationStateArr[i]->setLoop(true);

		mSceneNodeArr[i]
			= mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode();

		Vector3 p;
		Real a = i / (Real)numRobots * PI * 2.0;
		p.x = r * cos(a);
		p.z = r * sin(a);

		p.y = 0.0;

		p = p + mGamePosition;

		mSceneNodeArr[i]->setPosition(p);
		//
		Vector3 robotLookAtPosition;
		robotLookAtPosition.y = mSceneNodeArr[i]->getPosition().y;
		mSceneNodeArr[i]->lookAt(robotLookAtPosition, Node::TS_WORLD);
		mSceneNodeArr[i]->yaw(Degree(90));
		//
		mSceneNodeArr[i]->attachObject(mEntityArr[i]);

	}


	//Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing SCENE ***");

	//
	mCurrentObject = mSceneNodeArr[0];

}


//
// Set mSceneMgr = mSceneMgrArr[0];
// Then we use mSceneMgr to create objects in the second scene.
// Because we use mSceneMgr, we keep our code consistent.
// But need to bear in mind that which scene manager that we are using.
// 
void BasicTutorial_00::createScene_00(void) 
{
    mSceneMgr = mSceneMgrArr[0];
    ////////////////////////////////////////////////////
    // Now we can use mSceneMgr to create objects as usual.
    ////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // Enjoy modular programming experience
    ////////////////////////////////////////////////////
    createScene_Setup();
    createLights();
    createPlaneObjectResource();
	
    createGround();
	 
    createFloor();
	//
    createObjects();
	 //system("pause");
    createSphere();

    createScene_Setup_FX();

    //
    createTerrain();


   if (auto overlaySystem = mAppContext->getOverlaySystem())
       mSceneMgr->addRenderQueueListener(overlaySystem);
}

void BasicTutorial_00::createTerrain() 
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createTerrain():", mTrayMgr);
	MyTerrain* terrain = new MyTerrain(mSceneMgr, mCamera, mCameraNode, mTrayMgr);
	terrain->setupContent();
	terrain->setupControls();
	terrain->setShaderGenerator(Ogre::RTShader::ShaderGenerator::getSingletonPtr());
    mMyTerrain = terrain;
    return;
}
//
// Set mSceneMgr = mSceneMgrArr[1];
// Then we use mSceneMgr to create objects in the second scene.
// Because we use mSceneMgr, we keep our code consistent.
// But need to bear in mind that which scene manager that we are using.
// 
void BasicTutorial_00::createScene_01(void) 
{
    ////////////////////////////////////////////////////
    mSceneMgr = mSceneMgrArr[1];
    ////////////////////////////////////////////////////
    // Now we can use mSceneMgr to create objects as usual.
    ////////////////////////////////////////////////////

   // createTerrain();
    /*
    Ogre::TerrainGroup* terrain;
    terrain = loadLegacyTerrain("terrain.cfg", mSceneMgr);
    */
   // new Sample_Terrain( );
   // createTerrain(mSceneMgr);
    //createTerrain();
//    return;

    //mSceneMgr->setAmbientLight( ColourValue( 1.0,1.0, 1.0 ) ); 
    mSceneMgr->setAmbientLight( ColourValue( 0.0,0.0, 0.0 ) );  
  //  mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 
    //mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);

    
    LightConstruct *light = new LightConstruct(mSceneMgr);
    light->light->setType(Light::LT_POINT); 
    light->setPosition(Vector3(25, 150, -50)); 
    light->setDiffuseColour(0.0, 0.8, 0.0);		
    light->setSpecularColour(0.0, 1.0, 0.0);	
    mLight_SecondScene = light;
    //
}
