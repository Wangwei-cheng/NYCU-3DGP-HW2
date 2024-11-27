//
// Student Name: Wei-Cheng Wang
// Student ID: 313551170
// Student Email Address: wilsonw.cs13@nycu.edu.tw
//
//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include "BaseApplication.h"
#include "BasicTools.h"

#include "myTerrain.h"

#include "SpecialEffectManager.h"
#include "digit_string_dialogue.h"
#include "selection_rectangle.h"

#include "avatar_controller.h"
using namespace Ogre;

#define STUDENT_INFO "Student Name: Wei-Cheng Wang  Student ID: 313551170"

#define PI 3.141592654

#define VIS_MASK_MINMAP 0x0001

#define MOTION_TYPE_NONE 0
#define MOTION_TYPE_IDLE 1
#define MOTION_TYPE_WALK 2

/**
* Viewport dimension structure
*/
struct ViewportDim {
	float left, top, width, height;
};


/**
 * BasicTutorial_00 is derived from BaseApplication.
 * Use BasicTutorial_00 to create a game.
 * It supports
 * scene managers
 * viewports
 * cameras
 * lights
 * keyboard events
 * mouse events, and so on.
 */
class BasicTutorial_00 : public BaseApplication
{

protected:

	/**
	* ITEM_STATE is used to set the state of an item.
	* Use the state of the item for updating the game logic of the item.
	*
	*/
	enum ITEM_STATE {
		ITEM_STATE_INACTIVE = 0,
		ITEM_STATE_ACTIVE = 1,
		ITEM_STATE_DONE = 2
	};
public:
	/**
	* No-arg constructor.
	*/
	BasicTutorial_00(void);

	/**
	* Constructor accepts a string for its application name.
	*/
	BasicTutorial_00(const Ogre::String& appName);
	//
protected:

	/**
	* Initialize data members.
	*/
	virtual void init();

	/**
	* Initialize viewport dimensions.
	*/
	virtual void initViewportDimensions();

	/**
	* Create viewports.
	*/
	virtual void createViewports(void);

	/**
	* Create scenes.
	*/
	virtual void createScene(void);

	/**
	* Create cameras.
	*/
	virtual void createCameras(void);

	/**
	* Create scene managers.
	*/
	virtual void chooseSceneManagers(void);
	
	/**
	* A runtime callback for updating game logic.
	*/
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;


	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	virtual void createViewport_00(void);

	/**
	* Create a viewport in a scene based on a scene manager.
	*/
	virtual void createViewport_01(void);
	//
	virtual void createCamera_00();
	virtual void createCamera_01();
	//

	virtual void createScene_00();
	//
	virtual void createScene_01();

	//
	//virtual void createPlaneObjectResource();
	virtual void createFloor();
	//
	void initParticleSystemForExplosion();
	void setOffParticleSystem(
		Ogre::SceneNode* fNode,
		const Ogre::String& pname,
		const Ogre::Vector3& pos);

	virtual void lookAt_smooth(
		SceneNode* node
		, const Vector3& lookAtTarget
		, Real offset_angle_degree
		, Real dt);
	//
	void bindAvatar_Selection();
	void setupAvatarController();

	//
	virtual void setFog();
	virtual void createLights();
	virtual void createPlaneObjectResource();
	virtual void createGround();
	virtual void createScene_Setup();
	virtual void createScene_Setup_FX();
	virtual void createObjects();
	virtual void createSphere();
	//

	virtual void createTerrain();

	virtual void placeOnTerrain(SceneNode* node);
	virtual void placeGroup_OnTerrain();

	virtual void updatePets(double time_step);
	virtual void updateItems(double time_step);

	// return true if the key event has been handled
	virtual bool handleKeyEvents_QuitProgram(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_GetCameraInformation(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_Camera(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_Lights(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_Viewport(const OgreBites::KeyboardEvent& arg);
	virtual bool handleKeyEvents_Animation(const OgreBites::KeyboardEvent& arg);

	//
	void toggleSelection_AllObjects();
	//
	// return true if the key event has been handled
	//
	virtual bool handleKeyEvents(const OgreBites::KeyboardEvent& arg);
	virtual bool updateGameState(double dt);    // dt time step size
	//
	virtual void resetItems();
	virtual void activateOneItem();
	//
	virtual void UpdateMovableObjPosition(bool flg_large = false);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& arg) override;
	virtual bool keyReleased(const OgreBites::KeyboardEvent& arg) override;
	virtual bool mousePressed(const MouseButtonEvent& arg) override;
	virtual bool mouseReleased(const MouseButtonEvent& arg) override;
	virtual bool mouseMoved(const MouseMotionEvent& arg) override;
	virtual bool mouseWheelRolled(const MouseWheelEvent& arg) override;
	///////////////////////////
	// 
	void computeTargetPosition();
	virtual bool mouseMoved_Selection(const MouseMotionEvent& arg);
	virtual bool mousePressed_Selection(const MouseButtonEvent& arg);
	virtual bool mouseReleased_Selection(const MouseButtonEvent& arg);
	int volumeSelection(const MouseButtonEvent& arg);
	int singleClickSelect(const MouseButtonEvent& arg);
	//virtual bool mouseMoved(const OIS::MouseEvent& arg);
	//virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	//virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

	///////////////////////////
	void resolveCollisionObjectPair(int objA, int objB, float rA, float rB);

	void resolveCollisionBetweenObjectsAndSphere();

	void resolveCollisionForObjects();
	//
	void updateObjects_Positions(Real dt);
	void updateObjects_Animation(Real dt);
	void checkObjects_ReachingTarget(Real dt);
	//
	void updateObjectInformation();
	void updateLight(Real dt);
	void updateParticleSystems();
	void performCollisionHandling(Real dt);
	void updateObjects(Real dt);

	void updateAvatar(Real dt);


protected:
	Ogre::Viewport* mViewportArr[8];
	CameraConstruct* mCurrentCameraConstruct;
	CameraConstruct* mCameraConstruct[8];
	// Ogre::SceneNode* mCameraNodeArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	CameraMan* mCameraManArr[8];
	//
	LightConstruct* mLightContruct[8];
	LightConstruct* mLight_SecondScene;
	//
	Vector3 mGamePosition;
	//
	bool mRealTimeSimulationFlg;
	//
	double mAngle;
	double mRadius;
	double mAngularSpeed;
	double mAngularAcceleration;
	double mMaxSpeed;
	Ogre::SceneNode* mMovableObj;
	Ogre::SceneNode* mTargetObj;
	bool mFlg_MoveObj;
	bool mFlg_CounterClockwise;
	Ogre::Vector3 mVelocity;
	//
	int mNumOfItems;
	Ogre::SceneNode* mItemArr[256];		// CAUTIOUS: maximum 256 items
	ITEM_STATE mItemStatus[256];
	Ogre::Vector3 mVelocityArr[256];
	double mItemScale;
	double mItemGroupRadius;
	//
	ViewportDim mViewportDim[4];
	int mTopViewportIndex;
	int mViewportArrangementIndex;

	MyTerrain* mMyTerrain;

	/////////////////////////////////

	PlaneBoundedVolumeListSceneQuery* mVolQuery;
	Real left, top, right, bottom;
	SelectionRectangle* mSelectionRect;
	//
	int mNumOfMovingObj;
	int mNumOfObjectsReachedTarget;
	//
	int mNumofObjects;
	int mMaxNumofObjects;
	SceneNode* mCurrentObject;
	SceneNode* mSceneNodeArr[128];
	Vector3 mObjectDisplacement[128];
	SceneNode* mParticleNode;
	Entity* mEntityArr[128];
	bool mFlgTarget;
	Vector3 mTargetPosition;
	bool mFlgSelectNow;
	AnimationState* mAnimationStateArr[128];
	int mMotionStateArr[128];

	SceneNode* mLightSceneNode;


	Viewport* mViewport_Map;
	Vector4 mMiniMap_Dimension;
	Camera* mCameraMap;
	//SOUND* mSound;
	//bool mFlgAllReached;
	bool mFlgAllObjectsReachedTarget;
	Real mSphere_Radius;
	Vector3 mSphere_Position;
	Real mObject_radius;
	SceneNode* mSphere_Node;

	SpecialEffectManager* mFXManager;

	bool mFlg_EnableParticleSystem;
	Entity* mEntity_Floor;
	Entity* mEntity_Ground;
	SceneNode* mSceneNode_Ground, * mSceneNode_Floor;
	bool mFlg_Floor_Motion;
	Real mFloor_USpeed, mFloor_VSpeed;
	Light* mLight_Point;

	int mNumberOfPets;
	DIGIT_STRING_DIALOGUE* mPetCounter;

	bool mEnabledObjectAnimation;
	bool mEnabledLightAnimation;
	bool mEnabledFog;

	//
	bool mFlg_SelectAllObjects;

	bool mFlg_view_left, mFlg_view_right;
	//
	AVATAR_CONTROLLER* mAvatarController;
};

#endif // #ifndef __BasicTutorial_00_h_