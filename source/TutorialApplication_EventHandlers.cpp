//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

//
// Handle all keyboard and mouse events. 
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


using namespace std;
using namespace Ogre;
//using namespace OIS;

void showStudentInfo() {
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "<<< 3D Game Programming <<<<<<<<<" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "Date: 2024/09/20" << endl;
    cout << endl;
    cout << "STUDENT_INFO:" << STUDENT_INFO << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    system("pause");
}

//
// Handle key events for controlling the active camera.
//
// Set the camera position and its lookat position.
//
bool BasicTutorial_00::handleKeyEvents_Camera(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;
    Keycode key = arg.keysym.sym;



    if ( key == '1') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3( 3523, 1675, 8663) );
        mCameraMan->getCamera()
            ->setDirection(Vector3(-.21, -0.7, -0.68));
    }


    if (key == '2') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(3389, -57, 7330));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.26, -0.34, -0.90));
    }

    if (key == '3') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(3364, 793, 7495));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.09, -0.82, -0.56));
    }

    if (key == '4') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(3407, -465, 7678));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.26, 0.28, -0.92));
    }

    if (key == '5') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(40.39, 155.23, 251.20) + mGamePosition);
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.02, -0.41, -0.91));
    }

    if (key == '6') {
        flg_handled = true;

        mCameraMan->getCamera()
            ->setPosition(Vector3(19.94, 822.63, 30.79) + mGamePosition);
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.00, -0.99, -0.11));
    }
    return flg_handled;
}

//
// Set the viewport attributes, 
// e.g., background colours, dimensions and locations.
//
bool BasicTutorial_00::handleKeyEvents_Viewport(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;

    Keycode key = arg.keysym.sym;
    if (key == 'M' || key == 'm') {
        flg_handled = true;

        mRenderWindow->removeViewport(mViewportArr[0]->getZOrder());
        mRenderWindow->removeViewport(mViewportArr[1]->getZOrder());

        mTopViewportIndex = 0;
        mViewportArrangementIndex = 0;

        mCameraMan = mCameraManArr[1];

        Camera* c_ptr = mCameraConstruct[0]->camera; // first scene
        Ogre::Viewport* vp = mRenderWindow->addViewport(
            c_ptr,
            1,
            0.0,
            0.0,
            0.25,
            0.25
        );
        vp->setBackgroundColour(Ogre::ColourValue(0, 0.5, 0.0));
        c_ptr->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

        mViewportArr[0] = vp;
        //

        c_ptr = mCameraConstruct[1]->camera;

        vp = mRenderWindow->addViewport(
            c_ptr,
            0
        );
        vp->setBackgroundColour(Ogre::ColourValue(0, 0.0, 0.5));
        c_ptr->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

        mViewportArr[1] = vp;
        vp->setOverlaysEnabled(false);
    }

    if (key == 'N' || key == 'n') {
        flg_handled = true;

        mRenderWindow->removeViewport(mViewportArr[0]->getZOrder());
        mRenderWindow->removeViewport(mViewportArr[1]->getZOrder());

        mTopViewportIndex = 1;
        mViewportArrangementIndex = 1;

        mCameraMan = mCameraManArr[0];
        Camera* c_ptr = mCameraConstruct[0]->camera;
        Ogre::Viewport* vp = mRenderWindow->addViewport(
            c_ptr
        );
        vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.0));
        c_ptr->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

        mViewportArr[0] = vp;
        //
        c_ptr = mCameraConstruct[1]->camera;

        vp = mRenderWindow->addViewport(
            c_ptr,
            1,
            0.75,
            0.0,
            0.25,
            0.25
        );
        vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.1, 0.5));
        c_ptr->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

        mViewportArr[1] = vp;
        vp->setOverlaysEnabled(false);

    }

    if (key == 'B' || key == 'b') {
        flg_handled = true;

        float left, top, width, height;

        left = mViewportDim[mViewportArrangementIndex].left;
        top = mViewportDim[mViewportArrangementIndex].top;
        width = mViewportDim[mViewportArrangementIndex].width;
        height = mViewportDim[mViewportArrangementIndex].height;
        mViewportArr[mTopViewportIndex]
            ->setDimensions(left, top, width, height);

        mViewportArrangementIndex = (mViewportArrangementIndex + 1) % 4;
    }

    // toggle the mini-map
    if ( key == '/')
    {
        if (mMiniMap_Dimension.w == 0.0) {
            // on
            mMiniMap_Dimension.w = 0.9;
        }
        else {
            // off
            mMiniMap_Dimension.w = 0.5;
        }
        mViewport_Map->setDimensions(
            mMiniMap_Dimension.x
            , mMiniMap_Dimension.y
            , mMiniMap_Dimension.w
            , mMiniMap_Dimension.z
        );
    }

    // Toggle overlay on the main viewport mViewportArr[0]
    if (key == 'z') {
        //
        // Add your own stuff or modify
        //
    }

    return flg_handled;
}

//
// Set the object states for animation or simulation.
// Try not to perform complex tasks in a key handler.
//
bool BasicTutorial_00::handleKeyEvents_Animation(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;
    Keycode key = arg.keysym.sym;

    if (key == 'j' || key == 'J')
    {
        flg_handled = true;

        mRealTimeSimulationFlg = !mRealTimeSimulationFlg;
    }

    // Press Space bar to toggle the avatar mode
    if (key == SDLK_SPACE)
    {
        flg_handled = true;

        //
        // Add your own stuff or modify
        // 
    }

    if (key == 'K' || key == 'k')
    {
        flg_handled = true;

        resetItems();
    }

    if (key == 'P' || key == 'p') {
        mFlg_EnableParticleSystem = !mFlg_EnableParticleSystem;

        //
        // Add your own stuff or modify
        // mFXManager

        return true;
    }


    if (key == SDLK_F1) {
        // add your own stuff or modify
        return true;
    }

    if (key == SDLK_F2) {
        // add your own stuff or modify
        mEntity_Floor->setMaterialName("Examples/Rocky");

        return true;
    }

    if (key == SDLK_F3) {
        // add your own stuff or modify
        mEntity_Floor->setMaterialName("Examples/Rocky");
        return true;
    }

    if (key == SDLK_F5) {
        //mEnabledFog = !mEnabledFog;
        //setFog();

        return true;
    }


    if (key == 'y' || key == 'Y') {
        mSceneNode_Floor->translate(Vector3(0, -200, 0));
        //
        // add your own stuff or modify
        //
    }

    if (key == 'u' || key == 'U') {
        //
        // add your own stuff or modify
        //
    }

    if (key == 't' || key == 'T') {
        //
        // add your own stuff or modify
        //
    }

    return flg_handled;
}


//
// Get the camera position and direction.
// Save them to the log file.
//
bool BasicTutorial_00::handleKeyEvents_GetCameraInformation(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;

    stringstream ss;
    Keycode key = arg.keysym.sym;
    if (key == 'C' || key == 'c') {

        flg_handled = true;

        //How to clear ss?
        ss.str("");
        ss.clear();

        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camera position?
        //-----------------------------
        // This is incorrect.
        // Vector3 pos = mCamera->getPosition();
        // The controller may have its own 
        // set of attributes to control the camera.
        //
        //We use the controller to get the camera information.
        //-----------------------------
        //
        //
        // The following is correct.
        //
        Vector3 pos = mCameraMan->getCamera()->getPosition();
        ss << std::fixed << std::setprecision(2)
            << "CameraPosition:"
            << pos.x << "\t"
            << pos.y << "\t"
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage(ss.str());
        //
        ss.str("");
        ss.clear();
        //Vector3 dir = mCameraMan->getCamera()->getDirection();
        //Vector3 dir = mCameraMan->getCamera()->getAutoTrackLocalDirection();
        //Vector3 dir = mCameraMan->->getDirection();
        Quaternion q = mCameraMan->getCamera()->getOrientation();
        Vector3 dir = q * Vector3(1, 0, 0);
        ss << std::fixed << std::setprecision(2)
            << "CameraDirection:"
            << dir.x << "\t"
            << dir.y << "\t"
            << dir.z << "\n";


        dir = q * Vector3(0, 0, 1);
        ss << std::fixed << std::setprecision(2)
            << "CameraDirection:"
            << dir.x << "\t"
            << dir.y << "\t"
            << dir.z << "\n";


        dir = q * Vector3(-1, 0, 0);
        ss << std::fixed << std::setprecision(2)
            << "CameraDirection:"
            << dir.x << "\t"
            << dir.y << "\t"
            << dir.z << "\n";

        dir = q * Vector3(0, 0, -1);
        ss << std::fixed << std::setprecision(2)
            << "CameraDirection:"
            << dir.x << "\t"
            << dir.y << "\t"
            << dir.z << "\n";

        Ogre::LogManager::getSingletonPtr()
            ->logMessage(ss.str());
    }

    return flg_handled;
}

bool BasicTutorial_00::handleKeyEvents_QuitProgram(const OgreBites::KeyboardEvent& arg)
{
    if (arg.keysym.sym == OgreBites::SDLK_ESCAPE) {
        showStudentInfo();
        Ogre::Root::getSingleton().queueEndRendering();
        return true;
    }
    return false;
}

bool BasicTutorial_00::handleKeyEvents_Lights(const OgreBites::KeyboardEvent& arg)
{
    Keycode key = arg.keysym.sym;

    if (key == 'r') {
        mLightContruct[0]->light->setDiffuseColour(0.5, 0.5, 0.5);
        mLightContruct[0]->light->setSpecularColour(1.0, 1.0, 1.0);
    }

    if (key == '7') {
        mLightContruct[0]->light->setDiffuseColour(0.5, 0.0, 0.0);
        mLightContruct[0]->light->setSpecularColour(1.0, 0.0, 0.0);
    }

    if ( key == '8') {
        mLightContruct[0]->light->setDiffuseColour(0.0, 0.5, 0.0);
        mLightContruct[0]->light->setSpecularColour(0.0, 1.0, 0.0);
    }

    if ( key == '9') {
        mLightContruct[0]->light->setDiffuseColour(0.0, 0.0, 0.5);
        mLightContruct[0]->light->setSpecularColour(0.0, 0.0, 1.0);
    }

    if ( key == '0') {
        mLightContruct[0]->light->setDiffuseColour(0.5, 0.5, 0.5);
        mLightContruct[0]->light->setSpecularColour(1.0, 1.0, 1.0);
    }


    //COMMA
    if (key == ',') {
        double dv = 0.1;
        ColourValue c = mSceneMgr->getAmbientLight();
        //
        // add your own stuff or modify
        //
        mSceneMgr->setAmbientLight(c);
    }
    //PERIOD
    if (key == '.') {
        double dv = 0.1;
        ColourValue c = mSceneMgr->getAmbientLight();
        //
        // add your own stuff or modify
        //
        mSceneMgr->setAmbientLight(c);

    }

    if (key == 'U' || key == 'u') {
        mLight_SecondScene->light->setDiffuseColour(0.8, 0.0, 0.0);
        mLight_SecondScene->light->setSpecularColour(1.0, 0.0, 0.0);

    }

    if (key == 'I' || key == 'i') {
        mLight_SecondScene->light->setDiffuseColour(0.0, 0.8, 0.0);
        mLight_SecondScene->light->setSpecularColour(0.0, 1.0, 0.0);
        
    }

    if (key == 'O' || key == 'o') {
        mLight_SecondScene->light->setDiffuseColour(0.8, 0.8, 0.8);
        mLight_SecondScene->light->setSpecularColour(1.0, 1.0, 1.0);

    }


    return true;
}

//
// return true if the key event has been handled
//
bool BasicTutorial_00::handleKeyEvents(const OgreBites::KeyboardEvent& arg)
{
    bool flg_handled = false;

    //
    // Use the OR operator to turn on the flag
    //
    // Make sure that the same key is not used in
    // two or more functions.
    //

    if (handleKeyEvents_QuitProgram(arg)) {
        return false;
    }

    flg_handled |= handleKeyEvents_GetCameraInformation(arg);
    flg_handled |= handleKeyEvents_Camera(arg);
    flg_handled |= handleKeyEvents_Viewport(arg);
    flg_handled |= handleKeyEvents_Lights(arg);
    flg_handled |= handleKeyEvents_Animation(arg);

    return flg_handled;
}

bool BasicTutorial_00::keyPressed(const OgreBites::KeyboardEvent& arg)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::keyPressed()");

    bool flg = true;

    Keycode key = arg.keysym.sym;

    mCameraMan->keyPressed(arg);
    //mCameraManArr[0]->keyPressed(arg);
    mCameraManArr[1]->keyPressed(arg);

    if (mMyTerrain) mMyTerrain->keyPressed(arg);

    if (key == 'v' || key == 'V') {
        toggleSelection_AllObjects();
    }

    if (key == 'W' || key == 'w') {
        mAvatarController->setWalkForward();
    }

    if (key == 'S' || key == 's') {
        mAvatarController->setWalkBackward();
    }

    return handleKeyEvents(arg);
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
// 
// To find out the answer:
// Go to see the definition of KeyEvent
//

bool BasicTutorial_00::keyReleased(const OgreBites::KeyboardEvent& arg)
{

    bool flg = true;
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::keyReleased(const OgreBites::KeyboardEvent& evt)", arg.keysym.sym, false);

    mCameraMan->keyReleased(arg);
    //mCameraManArr[0]->keyReleased(arg);
    mCameraManArr[1]->keyReleased(arg);

    Keycode key = arg.keysym.sym;

    if (key == 'W' || key == 'w') {
        mAvatarController->unsetWalkForward();
    }

    if (key == 'S' || key == 's') {
        mAvatarController->unsetWalkBackward();
    }

    return flg;
}

bool BasicTutorial_00::mouseWheelRolled(const MouseWheelEvent& arg)
{
    bool flg = true;

    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseWheelRolled(const OgreBites::KeyboardEvent& arg)", arg.y, false);

    mCameraMan->mouseWheelRolled(arg);
    mTrayMgr->mouseWheelRolled(arg);

    //
    // Zoom in or out using the camera along the camera view direction (local)
    //
    if (arg.y != 0) {
        Vector3 p = mCameraMan->getCamera()->getPosition();

        double wheel_diff = arg.y;

        Real factor = 100.0;

        
        // The following implementation is wrong.
        Real dy = factor*wheel_diff;
        p.x += wheel_diff * factor;
        p.y -= dy;
        Real dz = factor * wheel_diff;
        p.z -= dz;
        mCameraMan->getCamera()->setPosition(p);

        //
        // Add your own stuff or modify
        //
    }


    return flg;
}

bool BasicTutorial_00::mousePressed(const MouseButtonEvent& arg)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mousePressed(const MouseButtonEvent& arg)", arg.button, false);

    mCameraMan->mousePressed(arg);

    //if (mTrayMgr->mousePressed(arg)) return true;
    
    std::cout << "BasicTutorial_00::mousePressed:mCameraConstruct[0]->camera:" << mCameraConstruct[0]->camera << std::endl;
    std::cout << "BasicTutorial_00::mTrayMgr:" << mTrayMgr << std::endl;
    std::cout << "BasicTutorial_00::arg:" << arg.x << std::endl;
    std::cout << "BasicTutorial_00::arg:" << arg.y << std::endl;

    Ogre::FrameEvent evt;
    evt.timeSinceLastFrame = 10.0;
    if (mMyTerrain) {
        mMyTerrain->setCamera(mCameraConstruct[0]->camera);
        mMyTerrain->frameRenderingQueued(evt);
    }

    //
    mousePressed_Selection(arg);
    
    return true;
}

bool BasicTutorial_00::mouseReleased(const MouseButtonEvent& arg)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseReleased(const MouseButtonEvent& evt)", arg.button, false);

    mouseReleased_Selection(arg);


    mCameraMan->mouseReleased(arg);
    if (mTrayMgr->mouseReleased(arg)) return true;
    
    
    return true;
}

bool BasicTutorial_00::mouseMoved(const MouseMotionEvent& arg)
{
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseMoved(const MouseButtonEvent& evt):x:", arg.x, false);
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseMoved(const MouseButtonEvent& evt):y:", arg.y, false);
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseMoved(const MouseButtonEvent& evt):xrel:", arg.xrel, false);
    ns_Debug_Tool::printf<const char*>("BasicTutorial_00::mouseMoved(const MouseButtonEvent& evt):yrel:", arg.yrel, false);


    if (!mouseMoved_Selection(arg)) return false;

    MouseMotionEvent tmparg = arg;
    tmparg.xrel *= 2;
    tmparg.yrel *= 2;

    if (tmparg.x <= 10) {
        tmparg.xrel = -abs(tmparg.yrel);
        mFlg_view_left = true;
    }
    else {
        mFlg_view_left = false;
    }

    //

    cout << "mViewportArr[0]->getActualWidth():" << mViewportArr[0]->getActualWidth() << endl;

    if (tmparg.x >= mViewportArr[0]->getActualWidth() - 10) {
        mFlg_view_right = true;
        tmparg.xrel = abs(tmparg.yrel);
    }
    else {
        mFlg_view_right = false;
    }

    if (mNumOfMovingObj <= 0 || mAvatarController->isAvatarOn()) {
        mCameraMan->mouseMoved(tmparg);
    }

    return true;
}


void BasicTutorial_00::toggleSelection_AllObjects() 
{
    mFlg_SelectAllObjects = !mFlg_SelectAllObjects;
    mFlgAllObjectsReachedTarget = false;
    mFlgTarget = false;

    if (mFlg_SelectAllObjects) {
        mNumberOfPets = mNumofObjects;
        mNumOfMovingObj = mNumberOfPets;
    }
    else {
        // set mNumberOfPets and mNumOfMovingObj to zero here.
    }

    //
    // turn on or off bounding box based on the flag mFlg_SelectAllObjects
    //
    for (int i = 0; i < mNumofObjects; ++i)
    {
        if (mFlg_SelectAllObjects); {}
            //mSceneNodeArr[i]
    }
}