//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#include <iostream>
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "BaseApplication.h"
#include "BasicTools.h"

using namespace Ogre;
using namespace std;

/**
 Default constructor

 @note This constructor invokes the constructor that accepts an argument, AppName, i.e., Ogre3D.
*/
BaseApplication::BaseApplication() :BaseApplication("Ogre3D")
{
    ns_Debug_Tool::printf<const char*>("BaseApplication::BaseApplication() :BaseApplication(\"Ogre3D\")");

}

/**
 Constructor accepts the appName as the argument.

 @param appName It is the application name.
 */
BaseApplication::BaseApplication(const Ogre::String& appName)
{
    ns_Debug_Tool::printf<const char*>("BaseApplication::BaseApplication(const Ogre::String& appName)");

    mAppName = appName;
}

/**
 Destructor 
 */
BaseApplication::~BaseApplication()
{
    ns_Debug_Tool::printf<const char*>("BaseApplication::~BaseApplication()");

    
}

/**
 This function set up create mAppContext and initialize it.
 */
bool BaseApplication::setup( ) {
    ns_Debug_Tool::printf<const char*>("BaseApplication::setup( )");


    mAppContext = new OgreBites::ApplicationContext( mAppName );
    mAppContext->initApp();
    
    return true;
}

/**
 This function sets mRoot to the root object of mAppContext.
 */
bool BaseApplication::createOgreRootObject(void)
{
    ns_Debug_Tool::printf<const char*>("BaseApplication::createOgreRootObject(void)");

    // get a pointer to the already created root
    mRoot = mAppContext->getRoot();
    return true;

}

/**
 This function uses mAppContext to create a render window.
 */
bool BaseApplication::createRenderWindow(void)
{
    ns_Debug_Tool::printf<const char*>("BaseApplication::createRenderWindow(void)");

    mRenderWindow = mAppContext->getRenderWindow( );
    return true;
}

/**
 This function invokes createSceneManager( ) to create a scene manager and stores it to mSceneMgr.
 */
void BaseApplication::chooseSceneManagers()
{
    ns_Debug_Tool::printf<const char*>("BaseApplication::chooseSceneManagers()");


    mSceneMgr = createSceneManager();

}

/**
 This function creates a scene manager and adds it to the Real Time Shader System (RTSS).
 It also sets mSceneMgr as the scene manager. So we can use mSceneMgr to access the scene manager.
 */
Ogre::SceneManager* BaseApplication::createSceneManager(void) {

    ns_Debug_Tool::printf<const char*>("BaseApplication::createSceneManager(void)");


    // create a scene manager
    SceneManager* sceneMgr = mRoot->createSceneManager();
    //SceneManager* sceneMgr = mRoot->createSceneManager("ST_EXTERIOR_REAL_FAR");
    //SceneManager *sceneMgr = mRoot->createSceneManager("ST_EXTERIOR_REAL_FAR");
    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneMgr);
    
    mSceneMgr = sceneMgr;

    ns_Debug_Tool::printf<const char*>("BaseApplication::mSceneMgr:", mSceneMgr);

    return sceneMgr;

}

/**
 This function creates cameras. In this case, it uses createCamera( ) to create one camera.
 */
 void BaseApplication::createCameras(void) {
     ns_Debug_Tool::printf<const char*>("BaseApplication::createCameras(void)");
     mCamera = createCamera(mSceneMgr);
}

 /**
 This function uses sceneMgr to create one camera.
 A default setting is set for the camera, including setFixedYawAxis as true, position, and look at.
 A camera scene node is also created. 
 The camare scene node is set to mCameraNode.

 @param sceneMgr It creates the camera. So the camera can be used to view the scene.
 */
 Ogre::Camera* BaseApplication::createCamera(Ogre::SceneManager* sceneMgr) {

     ns_Debug_Tool::printf<const char*>("BaseApplication::createCamera(Ogre::SceneManager* sceneMgr)");


     // also need to tell where we are
     Ogre::SceneNode* camNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
     camNode->setFixedYawAxis(true);
     camNode->setPosition(0, 0, 0);
     camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

     // create the camera
     Ogre::Camera *camera = sceneMgr->createCamera("myCamera");
     camera->setNearClipDistance(5); // specific to this sample
     camera->setAutoAspectRatio(true);
     camNode->attachObject(camera);

     mCameraNode = camNode;

     return camera;
 }

 /**
 This function creates a viewport and stores it to mViewport.
 */
 void BaseApplication::createViewports(void) {
     ns_Debug_Tool::printf<const char*>("BaseApplication::createViewports(void)");

     // and tell it to render into the main window
     mViewport = mRenderWindow->addViewport(mCamera);
     mViewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.25));
 }

 /**
This function creates lights. 
However, these lights cannot be accessed as they are not stored as data members.
*/
 void BaseApplication::createLights(void)
 {
     /*
     ns_Debug_Tool::printf<const char*>("BaseApplication::createLights(void)");


     // without light we would just get a black screen    
   Ogre::Light* light = mSceneMgr->createLight("MainLight");
   Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
   lightNode->setPosition(0, 10, 15);
   lightNode->attachObject(light);
   */
 }

 /**
This function sets up the input listener.
As this class is derived from the input listener, 
mAppContext->addInputListener(this) is called to set the input listener as the current object itself.
*/
 bool BaseApplication::createInputListener(void) 
 {
     ns_Debug_Tool::printf<const char*>("BaseApplication::createInputListener(void)");

     mAppContext->addInputListener(this);

     //mAppContext->addInputListener(mTrayMgr);
     return true;
 }

 /**
This function sets up the tray manager,  mTrayMgr.
*/
 bool BaseApplication::setupTrayManager(void)
 {

     ns_Debug_Tool::printf<const char*>("BaseApplication::setupTrayManager(void)");

     mTrayMgr = new TrayManager("InterfaceName", mRenderWindow, this);
     mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
     mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
     //mTrayMgr->hideCursor();
     mTrayMgr->showCursor();
     mAppContext->addInputListener(mTrayMgr);

     
     //scnMgr->addRenderQueueListener(mOverlaySystem);

     // create a params panel for displaying sample details
     /*
     Ogre::StringVector items;
     items.push_back("cam.pX");
     items.push_back("cam.pY");
     items.push_back("cam.pZ");
     items.push_back("");
     items.push_back("cam.oW");
     items.push_back("cam.oX");
     items.push_back("cam.oY");
     items.push_back("cam.oZ");
     items.push_back("");
     items.push_back("Filtering");
     items.push_back("Poly Mode");


     mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
     mDetailsPanel->setParamValue(9, "Bilinear");
     mDetailsPanel->setParamValue(10, "Solid");
     mDetailsPanel->hide();
     mDetailsPanel->show();
     */

     ns_Debug_Tool::printf<const char*>("BaseApplication::mTrayMgr:", mTrayMgr);
     ns_Debug_Tool::printf<const char*>("BaseApplication::mDetailsPanel:", mDetailsPanel);


     //////////////////////////////////////////////////////////
     return true;
 }

 /**
This function creates a camera man and assigns it to mCameraMan.
mCameraMan can be used to manipulate a camera easily.
*/
 void BaseApplication::createCameraMan() {
     mCameraMan = new CameraMan(mCameraNode);
 }

 /**
This function is empty.
*/
 void BaseApplication::setCameraMan()
 {

 }

 /**
This function configures the entire system.
*/
bool BaseApplication::configure(void) {

    ns_Debug_Tool::printf<const char*>("BaseApplication::configure(void)");

    //! [setup]

    createOgreRootObject( );
    createRenderWindow( );
    chooseSceneManagers( );
    createCameras( );
    createCameraMan( );
    setCameraMan( );
    createViewports( );
    //
    setupTrayManager();
    //createLights( );
    createScene( );
    
    createInputListener( );
    //setupTrayManager();

    // mRoot->showConfigDialog();
    // mAppContext->oneTimeConfig();
    // createFrameListener();
    return true;

}


/**
This function handles a keypressed event. Whenever a key is pressed, this function is invoked.
*/
bool BaseApplication::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    ns_Debug_Tool::printf<const char*>("BaseApplication::keyPressed(const OgreBites::KeyboardEvent& evt)", false);


    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        Ogre::Root::getSingleton().queueEndRendering();
    }
    return true;
}

/**
This function is empty.
*/
void BaseApplication::createFrameListener(void)
{
    
}

/**
This function is the entry point of an application.
*/
void BaseApplication::go() 
{
    ns_Debug_Tool::printf<const char*>("BaseApplication::go(void)");

    setup();
    configure();

    // ns_Debug_Tool::printf<const char*>("mRoot->startRendering()");

    mRoot->startRendering();
    //mRoot->renderOneFrame();

    mAppContext->closeApp();
}

