//
// Student Name:
// Student ID:
// Student Email Address:
//
//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 


#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "OgreApplicationContext.h"
#include "BaseApplication.h"

using namespace Ogre;
using namespace OgreBites;

/**
* This class defines basic functions for setting up an ogre program.
* BaseApplication is derived from two listeners, InputListener and TrayListener.
* 
*/
class BaseApplication 
   : 
   public OgreBites::InputListener
    , public TrayListener
{
public:
    BaseApplication(void);
    BaseApplication(const Ogre::String& appName);
    virtual ~BaseApplication(void);

    /**
    * Invoke go( ) to run the program.
    */
    virtual void go(void); 
    
protected:
    virtual bool setup( );
    virtual bool configure(void);
    virtual bool createOgreRootObject(void);
    virtual bool createRenderWindow(void);
    virtual Ogre::SceneManager* createSceneManager(void);
    virtual void chooseSceneManagers();
    virtual void createCameras(void);
    virtual void createCameraMan();
    virtual void setCameraMan();
    virtual Ogre::Camera* createCamera(Ogre::SceneManager* sceneMgr);
    virtual void createViewports(void);
    virtual void createLights(void);
    //virtual void createScene(void) = 0; // Override me!
    virtual void createScene(void) { }; // Override me!
    virtual bool createInputListener(void);
    virtual bool setupTrayManager(void);
    //
    
    virtual void createFrameListener(void);

    //
    // InputListener
    //
    virtual bool keyPressed(const KeyboardEvent& evt);
    virtual bool keyReleased(const KeyboardEvent& evt) { return false; }
    virtual bool mouseMoved(const MouseMotionEvent& evt) { return false; }
    virtual bool mouseWheelRolled(const MouseWheelEvent& evt) { return false; }
    virtual bool mousePressed(const MouseButtonEvent& evt) { return false; }
    virtual bool mouseReleased(const MouseButtonEvent& evt) { return false; }
    //
    virtual bool touchMoved(const TouchFingerEvent& evt) { return false; }
    virtual bool touchPressed(const TouchFingerEvent& evt) { return false; }
    virtual bool touchReleased(const TouchFingerEvent& evt) { return false; }
    virtual bool textInput(const TextInputEvent& evt) { return false; }
    virtual bool axisMoved(const AxisEvent& evt) { return false; }
    virtual bool buttonPressed(const ButtonEvent& evt) { return false; }
    virtual bool buttonReleased(const ButtonEvent& evt) { return false; }
    //
    //
    //
    virtual void frameRendered(const Ogre::FrameEvent& evt) { }

protected:
    Ogre::String mAppName;                      // application name
    OgreBites::ApplicationContext* mAppContext;
    Ogre::Root* mRoot;
    Ogre::RenderWindow* mRenderWindow;
    Ogre::SceneManager* mSceneMgr;
    Ogre::Camera* mCamera;
    Ogre::SceneNode* mCameraNode;
    Ogre::Viewport* mViewport;
    //
    OgreBites::TrayManager* mTrayMgr;
    OgreBites::CameraMan* mCameraMan;           // basic camera controller
    OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel
    bool mCursorWasVisible;                    // was cursor visible before dialog appeared
    bool mShutDown;


    //OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;
};

#endif // #ifndef __BaseApplication_h_
