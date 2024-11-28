//
// 3D Game Programming
// 
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
//
// For runtime stuff.
// Simple entry point for updating game logic.
// The high level workflow should be placed here.
// Avoid implementing low level stuff here.
//

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>

#include "TutorialApplication.h"
#include "BasicTools.h"
#include "reader_data.h"
#include "SystemParameter.h"

using namespace std;

void BasicTutorial_00::updateAvatar(Real dt)
{
	mAvatarController->update(dt);
}
//
// This function is called every frame.
//
void BasicTutorial_00::frameRendered(const Ogre::FrameEvent& evt)
{
    bool flg = true;

    double dt = evt.timeSinceLastFrame; // simulation time step size

    if (!mRealTimeSimulationFlg) { // Run in real time? That is, match to our wall-clock time?
        // No.
        // So this is not real time simulation.
        // So our program runs with a fixed time step size. 
        // If a faster computer is used, 
        // the resulting animation is faster under a fixed time duration.
        dt = SystemParameter::simulationTimeStep;
    }
    flg = updateGameState( dt );

	updateObjects( dt );

	performCollisionHandling(dt);

	updateParticleSystems();
	updateObjectInformation();

	placeGroup_OnTerrain();

	updateAvatar(dt);

	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->refreshCursor();
    
    mTrayMgr->showAll();
    mTrayMgr->frameRendered(evt);
    mCameraManArr[0]->frameRendered(evt);

	//mCameraManArr[0]->setStyle(CS_MANUAL);
	mCameraManArr[0]->setStyle(CS_FREELOOK);

    if (mMyTerrain) mMyTerrain->frameRenderingQueued(evt);

	if (mFlg_view_left) {
		MouseMotionEvent tmparg;
		tmparg.x = 0;
		tmparg.y = 0;
		tmparg.xrel = -1;
		tmparg.yrel = 0;
		mFlg_view_left = true;

		mCameraMan->mouseMoved(tmparg);
	}

	if (mFlg_view_right) {
		MouseMotionEvent tmparg;
		tmparg.x = 0;
		tmparg.y = 0;
		tmparg.xrel = 1;
		tmparg.yrel = 0;
		mFlg_view_right = true;

		mCameraMan->mouseMoved(tmparg);
	}

    //cout << "isDialogVisible:" << mTrayMgr->isDialogVisible() << endl;
    //cout << "isCursorVisible:" << mTrayMgr->isCursorVisible() << endl;
    //cout << "areTraysVisible:" << mTrayMgr->areTraysVisible() << endl;

    //mTrayMgr->frameRenderingQueued(evt);
    /*
    mTrayMgr->showTrays();
    if ( true || !mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRendered(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }
    */
  //  return flg;
}


//////////////////////
void BasicTutorial_00::lookAt_smooth(
	SceneNode* node
	, const Vector3& lookAtTarget
	, Real offset_angle_degree
	, Real dt)
{

	//current orientation
	Quaternion q0 = node->getOrientation();

	node->lookAt(lookAtTarget, Node::TS_WORLD);
	node->yaw(Degree(offset_angle_degree));

	//desired orientation
	Quaternion q1 = node->getOrientation();
	//
	Real f = READER_DATA::getSmoothRotationFacter();
	//Real f = 1.0;
	Real r = f * dt;
	if (r > 1.0) r = 1.0; // safe guard

	node->setOrientation(slerp(q0, q1, r));
}


void BasicTutorial_00::updateObjects_Positions(Real dt)
{
	if (mFlgTarget == false) return;

	for (int i = 0; i < mNumofObjects; ++i)
	{
		bool flgShow = mSceneNodeArr[i]->getShowBoundingBox();
		if (flgShow == false) continue;

		++mNumOfMovingObj;
		Vector3 d;
		d = mTargetPosition - mSceneNodeArr[i]->getPosition();
		Real len = d.length();
		Real robotTargetDistance = len;
		if (len != 0.0) d.normalise();
		
		Real walkSpeed = 100;
		//Real walkSpeed = [80, 100];

		Real walkDistance = walkSpeed * dt;
		if (robotTargetDistance < 0.01) {
			d = robotTargetDistance * 1.05 * d;
			//Vector3::ZERO;

		}
		else {
			d = d * walkDistance;
			Vector3 robotLookAtPosition = mTargetPosition;
			
			robotLookAtPosition.y = mSceneNodeArr[i]->getPosition().y; // do you need to set the y-coordinate the same?

			lookAt_smooth(
				mSceneNodeArr[i]
				, robotLookAtPosition
				, READER_DATA::getYawAngleDegreeOffset_Pet()			// correct angle is? angle correction is needed?
				, dt
			);
		}

		mObjectDisplacement[i] = d;
		mSceneNodeArr[i]->translate(d);
	}
}

void BasicTutorial_00::updateObjects_Animation(Real dt)
{
	if (!mEnabledObjectAnimation) return;
	for (int i = 0; i < mNumofObjects; ++i) {


		bool flgShow = mSceneNodeArr[i]->getShowBoundingBox();
		if (flgShow == false) {
			if (mAnimationStateArr[i]) {
				mAnimationStateArr[i]->setEnabled(false);
				mAnimationStateArr[i]->setLoop(false);
			}
			mAnimationStateArr[i] = mEntityArr[i]->getAnimationState("Idle");
			//
			// add your own stuff or modify
			// Enable the animation and set loop
			//
			mAnimationStateArr[i]->setEnabled(true);
			mAnimationStateArr[i]->setLoop(true);
		}
		else {
			if (mAnimationStateArr[i]) {
				mAnimationStateArr[i]->setEnabled(false);
				mAnimationStateArr[i]->setLoop(false);
			}
			mAnimationStateArr[i] = mEntityArr[i]->getAnimationState("Walk");
			//
			// add your own stuff or modify
			//
			mAnimationStateArr[i]->setEnabled(true);
			mAnimationStateArr[i]->setLoop(true);
		}
	}

	//
	// add time to the animation clip
	//
	for (int i = 0; i < mNumofObjects; ++i) {
		mAnimationStateArr[i]->addTime(dt * 2);
	}
}

//
// Add your own stuff or modify
//
void BasicTutorial_00::checkObjects_ReachingTarget(Real dt)
{
	if (mFlgTarget == false) return;

	mNumOfMovingObj = 0;
	mNumOfObjectsReachedTarget = 0;

	float threshold = mObject_radius;
	for (int i = 0; i < mNumofObjects; ++i)
	{
		bool flgShow = mSceneNodeArr[i]->getShowBoundingBox();
		if (flgShow == false) continue;
		++mNumOfMovingObj;
	}

	double region_scale = 3;
	if (mNumOfMovingObj >= 1) {
		threshold = 100; // do you know how large a robot is? Can all the robots move to a single point?
	}

	for (int i = 0; i < mNumofObjects; ++i)
	{
		bool flgShow = mSceneNodeArr[i]->getShowBoundingBox();
		if (flgShow == false) continue;

		Vector3 curPos = mSceneNodeArr[i]->getPosition();
		//Vector3 displacement = mObjectDisplacement[i];
		//Real result = (mTargetPosition - curPos).dotProduct(displacement);

		Vector3 pq = mTargetPosition - curPos;	// difference between two points, i.e., the vector between them
		pq.y = 0;								// ignore the y-coordinate difference, i.e., the height.
		Real result = pq.length();				// consider the vector length on the x-z plane only.

		if (result <= threshold) {
			// The robot reaches the target position.
			++mNumOfObjectsReachedTarget;
			mSceneNodeArr[i]->showBoundingBox(false);
		}
	}
}

//
// Update the objects.
//
void BasicTutorial_00::updateObjects(Real dt)
{
	updateObjects_Positions(dt);

	checkObjects_ReachingTarget(dt);

	if (mNumOfObjectsReachedTarget > 0) {
		if (mNumOfObjectsReachedTarget == mNumOfMovingObj) {
			mFlgAllObjectsReachedTarget = true;
		}
	}

	if (mFlgAllObjectsReachedTarget) {
		//mSound->play();
		mFlgAllObjectsReachedTarget = false;
	}

	updateObjects_Animation(dt);
}


//
// Update the particle systems
//
void BasicTutorial_00::updateParticleSystems()
{
	Vector3 pos;
	pos = mSceneNodeArr[0]->getPosition();
	setOffParticleSystem(mParticleNode, "explosion", pos);

	//if mFlg_EnableParticleSystem 
	//	for (int i = 0; i < mNumofObjects; ++i)
	//	{
	//		/*mFXManager->setOffParticleSystem(
	//			particle system index
	//			, position of mSceneNodeArr[i]
	//		);*/
	//	}
	//end if
}

//
// change the light position
//
void BasicTutorial_00::updateLight(Real dt) {
	if (!mEnabledLightAnimation) return;
	static Real a = 0;
	Real r = 400;
	Vector3 Lpos;
	Lpos.y = 300;
	Lpos.x = r * cos(a);
	Lpos.z = r * sin(a);
	a += dt;
	if (a > 3.14159 * 2) a -= 3.14159 * 2;
	mLightSceneNode->setPosition(Lpos);
}

//
// Show the information about the scene
// Example:
// The number of objects, selected objects, etc.
//
void BasicTutorial_00::updateObjectInformation() {
	mPetCounter->setScore(mNumOfMovingObj, .05, 0.05);
}