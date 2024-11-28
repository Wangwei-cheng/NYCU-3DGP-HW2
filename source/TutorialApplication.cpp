//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"

#include "SystemParameter.h"

using namespace std;
using namespace Ogre;

BasicTutorial_00::BasicTutorial_00(void) : BasicTutorial_00("Hello World!")
{
  
}

BasicTutorial_00::BasicTutorial_00(const Ogre::String& appName)
    : BaseApplication(appName)
{
    init();
}

void BasicTutorial_00::init() {
    //
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::init(void)");
    //
    mMyTerrain = nullptr;
    //
    mRealTimeSimulationFlg = false; // run as fast as possible
    mRealTimeSimulationFlg = true;  // match to wall-clock time. "real life" time
    //
    mGamePosition = Vector3( 1000+2200, 0, 5000+1715);
    //
    mAngularAcceleration = SystemParameter::acceleration;
    mMaxSpeed = SystemParameter::maxSpeed;
    mRadius = SystemParameter::radius;
    mAngularSpeed = 0.0;
    mFlg_CounterClockwise = false;
    mAngle = 0.0;
    mFlg_MoveObj = false;
    //
    mFlg_MoveObj = false;
    mFlg_CounterClockwise = true;
    //
    mItemScale = 1.0;
    //
    ////////////////////////////////////////////////////////
    mFlg_Floor_Motion = false;
    mEntity_Floor = 0;
    mFloor_USpeed = 0.05;
    mFloor_VSpeed = 0.0;
    mEnabledObjectAnimation = true;
    mEnabledLightAnimation = true;
    mEnabledFog = true;

    mFXManager = 0;
    mFlg_EnableParticleSystem = true;
    //
    mFlgAllObjectsReachedTarget = false;
    //
    mPetCounter = nullptr;
    mNumberOfPets = 0;
    mFlgTarget = false;

    //
    mSphere_Radius = 100;
    mObject_radius = 20.0;
    //
    mNumofObjects = 0;
    mMaxNumofObjects = 128;
    for (int i = 0; i < mMaxNumofObjects; ++i) {
        mAnimationStateArr[i] = nullptr;
    }
    //
    mNumOfMovingObj = 0;
    mNumOfObjectsReachedTarget = 0;
    //////////////////////////////////////////////////////////
    mFlg_view_left = false;
    mFlg_view_right = false;
    //
    mAvatarController = new AVATAR_CONTROLLER();
    //
    mFlg_SelectAllObjects = false;
    //
    initViewportDimensions();

}

void BasicTutorial_00::initViewportDimensions()
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::initViewportDimensions(void)");

    mTopViewportIndex = 1;
    mViewportArrangementIndex = 1;

    mViewportDim[0].left = 0.75;
    mViewportDim[0].top = 0;
    mViewportDim[0].width = 0.25;
    mViewportDim[0].height = 0.25;
    //
    mViewportDim[1].left = 0.75;
    mViewportDim[1].top = 0.75;
    mViewportDim[1].width = 0.25;
    mViewportDim[1].height = 0.25;
    //
    mViewportDim[2].left = 0;
    mViewportDim[2].top = 0.75;
    mViewportDim[2].width = 0.25;
    mViewportDim[2].height = 0.25;
    //
    mViewportDim[3].left = 0.0;
    mViewportDim[3].top = 0.0;
    mViewportDim[3].width = 0.25;
    mViewportDim[3].height = 0.25;

    //

    mMiniMap_Dimension.x = 0.74;
    mMiniMap_Dimension.y = 0.01;
    mMiniMap_Dimension.w = 0.25;
    mMiniMap_Dimension.z = 0.25;
}

//
// chooseSceneManagers( ) is invoked in the setup process.
// We will create two scene managers.
// 
// Call createSceneManager( ) to create a scene manager.
// e.g.,
// scene manager = createSceneManager( );
//
// Store the scene managers to the pointer array, mSceneMgrArr[ ]
//
// For example,
// mSceneMgrArr[0] = createSceneManager();
// mSceneMgrArr[1] = createSceneManager();
//
// You can use mSceneMgr to point to a current scene manager.
// So you set it up here too.
// For example, set mSceneMgr to point to the first scene manager as 
// mSceneMgr = mSceneMgrArr[0];
//
void BasicTutorial_00::chooseSceneManagers()
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::chooseSceneManagers()");

    //
    mSceneMgrArr[0] = createSceneManager();
    mSceneMgrArr[1] = createSceneManager();
    //
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mSceneMgrArr[0]:", mSceneMgrArr[0]);
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mSceneMgrArr[1]:", mSceneMgrArr[1]);

    mSceneMgr = mSceneMgrArr[0]; // active scene manager

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mSceneMgr:", mSceneMgr);
}

//
// Create a camera for mSceneMgrArr[0]
//
// Set the camera position, lookat position.
// Set the clip distances, i.e., near and far distances
//
// To create a controller for the camera,
// call 
// mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);
//
//
// Later on, we can use mCameraManArr[0] 
// to receive mouse and keyboard events. 
//
void BasicTutorial_00::createCamera_00(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera_00(void)");

    mSceneMgr = mSceneMgrArr[0];
    mCameraConstruct[0] = new CameraConstruct("PlayerCamera", mSceneMgr);
    //mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCamera");
    mCameraConstruct[0]->cameraNode->setPosition(Ogre::Vector3(120, 300, 600) + mGamePosition);
    mCameraConstruct[0]->cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TransformSpace::TS_PARENT);
    //
    // near clipping distance
    //
    mCameraConstruct[0]->camera->setNearClipDistance(5);
    mCameraNode = mCameraConstruct[0]->cameraNode;
    //
    // create a default camera controller
    //

    mCameraManArr[0] = new CameraMan(mCameraConstruct[0]->cameraNode);

    mCameraManArr[0]->setTopSpeed( 250 );

    mCurrentCameraConstruct = mCameraConstruct[0];
    //mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera_00(void):mCameraConstruct[0]", mCameraConstruct[0]);

}

//
// Create a camera for mSceneMgrArr[1]
//
// Set the camera position, lookat position.
// Set the clip distances, i.e., near and far distances
//
// To create a controller for the camera,
// call 
// mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);
//
//
// Later on, we can use mCameraManArr[1] 
// to receive mouse and keyboard events. 
//
void BasicTutorial_00::createCamera_01(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera_01(void)");


    mSceneMgr = mSceneMgrArr[1];        // this scene manager is not the same as mSceneMgrArr[0]
    //mSceneMgr = mSceneMgrArr[0];      // use the scene manager [0] to create camera.


    mCameraConstruct[1] = new CameraConstruct("PlayerCamera_01", mSceneMgr);

    //
    // Add your own stuff or modify
    // Do not look down vertically
    //
    mCameraConstruct[1]->setPosition(Ogre::Vector3(mGamePosition.x, 10, mGamePosition.z));
    mCameraConstruct[1]->cameraNode->lookAt(
        Ogre::Vector3(mGamePosition.x, 0, mGamePosition.z + 0.0)
        , Node::TransformSpace::TS_PARENT
    );

    mCameraConstruct[1]->camera->setNearClipDistance(5);
    //
    mCameraManArr[1] = new CameraMan(mCameraConstruct[1]->cameraNode);

    mCurrentCameraConstruct = mCameraConstruct[1];

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera_00(void):mCameraConstruct[1]", mCameraConstruct[1]);


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    mSceneMgr = mSceneMgrArr[0];        // set it back to the main scene manager.
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

}


//
// Create a viewport for the camera, mCameraArr[0].
//
// 1.Call mWindow->addViewport(mCamera) to create the viewport.
// 2.Set the background colour.
// 3.Set the aspect ratio.
// 
//
void BasicTutorial_00::createViewport_00(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createViewport_00(void)");

    mCurrentCameraConstruct = mCameraConstruct[0];
    mCamera = mCurrentCameraConstruct->camera;

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mCurrentCameraConstruct:", mCurrentCameraConstruct);


    Ogre::Viewport* vp = mRenderWindow->addViewport(
        mCamera
    );

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::vp:", vp);
    vp->setOverlaysEnabled(true);

    vp->setBackgroundColour(Ogre::ColourValue(0, 0.0, 1.0));

    double viewport_width = Ogre::Real(vp->getActualWidth());
    double viewport_height = Ogre::Real(vp->getActualHeight());

    mCamera->setAspectRatio(viewport_width / viewport_height);

    //
    // Store the viewport point vp. 
    // So we can use the pointer later.
    //
    mViewportArr[0] = vp;
}

//
// Create a viewport for the camera, mCameraArr[1].
//
// 1.Call mWindow->addViewport(mCamera) to create the viewport.
// 2.Set the background colour.
// 3.Set the aspect ratio.
// 
//

void BasicTutorial_00::createViewport_01(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createViewport_01(void)");


    mCurrentCameraConstruct = mCameraConstruct[1];
    mCamera = mCurrentCameraConstruct->camera;

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mCurrentCameraConstruct:", mCurrentCameraConstruct);


    // Modify it ?
    Ogre::Viewport* vp = mRenderWindow->addViewport(
        mCamera,
        1,
        0.65,
        0.25,
        0.25,
        0.25
    );

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::vp:", vp);


    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 1));

    //
    // Modify them?
    //
    double viewport_width = 3;
    double viewport_height = 10;
    mCamera->setAspectRatio(viewport_width / viewport_height);


    //vp->setVisibilityMask(VIS_MASK_MINMAP);
    vp->setVisibilityMask( 0x0 ); // do not show anything

    vp->setSkiesEnabled(true); // show skies
    //
    // Make the overlay invisible in this viewport.
    //
    vp->setOverlaysEnabled(true); // show overlays
    //
    mViewport_Map = mViewportArr[1] = vp;
    
}

//
// createViewports is invoked in the setup process.
//
void BasicTutorial_00::createViewports(void)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createViewports(void)");


    createViewport_00();
    createViewport_01();
}

//
// createCamera is invoked in the setup process.
//
void BasicTutorial_00::createCameras(void) {
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createCamera(void)");

    BaseApplication::createCameras( ); // create the camera for the base class
    //
    createCamera_00();
    createCamera_01();
    //
    // A controller recieves mouse and keyboard events.
    // In this system, only one controller can be active.
    // and the other controllers are inactive.
    //
    // Set one controller as active.
    // In this case, we set mCameraManArr[0] to be active.
    // mCameraMan is used in the base class, BaseApplication.
    // The mouse and keyboard events are passed to mCameraMan.
    // Thus, we set mCameraMan = mCameraManArr[0] for the main scene.
    //

    // Set mCameraManArr[0] as active.
    mCamera = mCameraConstruct[0]->camera;
    mCameraMan = mCameraManArr[0];

    // Set mCameraManArr[1] as active.
    //mCameraMan = mCameraManArr[1];    
}


//
// Create scene node, mParticleNode.
// Create one particle system.
// Attach the particle system to scene node, mParticleNode.
//
void BasicTutorial_00::initParticleSystemForExplosion() {
    mParticleNode = static_cast<SceneNode*>(
        mSceneMgr->getRootSceneNode()->createChild());

    // Create particle system with name "explosion".
    ParticleSystem* p = mSceneMgr->createParticleSystem(
        "explosion"
        , "Examples/GreenyNimbus");

    ParticleEmitter* e = p->getEmitter(0);
    e->setEnabled(false);
    mParticleNode->attachObject(p);
    mParticleNode->setPosition(Vector3::ZERO);
    mParticleNode->setVisible(false);
}

//
// Enable the particle system which is attached to 
// scene node fNode.
// pname is the particle system name.
//
void BasicTutorial_00::setOffParticleSystem(
    Ogre::SceneNode* fNode
    , const Ogre::String& pname
    , const Ogre::Vector3& pos)
{
    fNode->setPosition(pos);
    fNode->setVisible(true);

    //Get the movable object with name pname.
    MovableObject* s = fNode->getAttachedObject(pname);

    //
    //Convert the movable object, s, to a particle system.
    //Note that: in initParticleSystemForExplosion(...), 
    //a particle system is attached to the scene node fNode.
    //Thus, the conversion static_cast<ParticleSystem*>(s) makes sense.
    // 
    ParticleSystem* p = static_cast<ParticleSystem*>(s);
    if (p == NULL) return;
    p->setVisible(true);					// set it to be visible
    ParticleEmitter* e = p->getEmitter(0);	// get the emitter with index 0
    e->setEnabled(true);					// enable the emitter
}


//
// We invokde the data reader to read parameter values
// which are stored in a text file.
// After that, we use the data reader READER_DATA 
// to access the parameter values.
// 
// At the end of this function, set the active camera.
//
void BasicTutorial_00::createScene(void) {

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::createScene(void)");


    Ogre::LogManager::getSingletonPtr()->logMessage("DATA_Reader::Read");
    READER_DATA::readData();
    
    SystemParameter::simulationTimeStep = READER_DATA::getSimulationStepSize();

    //
    createScene_00();
    createScene_01();

    mSceneMgr = mSceneMgrArr[0];  // active SceneManager
    //mSceneMgr = mSceneMgrArr[1];    // active SceneManager
    //
    //
    mCurrentCameraConstruct = mCameraConstruct[0];  // active camera
    mCamera = mCurrentCameraConstruct->camera;

    mCameraMan = mCameraManArr[0];

    //mCamera = mCameraArr[1];      // active camera

    setupAvatarController( );
}


void BasicTutorial_00::setupAvatarController()
{
    // use mCameraConstruct[0] as the camera for the avatar
    mAvatarController->setAvatar(nullptr, mCameraConstruct[0]);
}