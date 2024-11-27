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

using namespace std;

//
// mTargetPosition is the target position of the robots.
//
void BasicTutorial_00::computeTargetPosition()
{
	std::cout << "BasicTutorial_00::computeTargetPosition()" << endl;

	
	/*Vector3 planeNormal = Vector3(0, 1, 0);
	Ray ray;
	ray = mTrayMgr->getCursorRay(mCamera);
	Plane p(Vector3(0, 1, 0), mSceneNode_Floor->getPosition().y);
	std::pair<bool, Real> result = ray.intersects(p);
	mTargetPosition = ray.getOrigin() + result.second * ray.getDirection();
	*/

	//mFlgTarget = true;
	mTargetPosition = mGamePosition + Vector3(0, 100, 0);

	if (mMyTerrain) {
		//mTargetPosition = mMyTerrain->getMarkerPosition();
	}

}

bool BasicTutorial_00::mousePressed_Selection(const MouseButtonEvent& arg)
{

	std::cout << "Step 1 mousePressed_Selection" << arg.x << "\t" << arg.y << endl;


	if (arg.button == BUTTON_RIGHT) {
		return true;
		//return BaseApplication::mousePressed(arg);
	}

	std::cout << "Step 2 mousePressed_Selection" << arg.x << "\t" << arg.y << endl;

	//Ogre::String ss = Ogre::StringConverter::toString(id);

	//Ogre::LogManager::getSingletonPtr()->logMessage(ss);


	mFlgSelectNow = true;

	Ray mRay = mTrayMgr->getCursorRay(mCamera);

	Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
	left = scn.x;
	top = scn.y;
	right = scn.x;
	bottom = scn.y;

	mSelectionRect->setCorners(left, top, right, bottom);
	mSelectionRect->setVisible(true);
	return false;
	//return BaseApplication::mousePressed(arg, id);
}

bool BasicTutorial_00::mouseMoved_Selection(const MouseMotionEvent& arg)
{
	std::cout << "mouseMoved_Selection" << arg.x << "\t" << arg.y << endl;

	//Ogre::String ss = Ogre::StringConverter::toString(arg.state.Z.rel);

	//Ogre::LogManager::getSingletonPtr()->logMessage(ss);

	if (mFlgSelectNow != true) return true;

		Ray mRay = mTrayMgr->getCursorRay(mCamera);

		Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
		left = scn.x;
		top = scn.y;
		cout << "left:" << left << endl;
		cout << "top:" << top << endl;
		/*
		Ogre::String ss;
		ss = Ogre::StringConverter::toString(left);
		Ogre::LogManager::getSingletonPtr()->logMessage("left:" + ss);

		ss = Ogre::StringConverter::toString(top);
		Ogre::LogManager::getSingletonPtr()->logMessage("top:" + ss);
		*/
		mSelectionRect->setCorners(left, top, right, bottom);
		mSelectionRect->setVisible(true);

		return false;

}

void BasicTutorial_00::bindAvatar_Selection()
{
	if (mCurrentObject == nullptr) return;
	mAvatarController->setAvatarNode(mCurrentObject);
}

bool BasicTutorial_00::mouseReleased_Selection(const MouseButtonEvent& arg)
{
	if (arg.button == BUTTON_RIGHT) {
		computeTargetPosition();
		mFlgAllObjectsReachedTarget = false;
		return false;
		//return BaseApplication::mouseReleased(arg, id);
	}
	
	//mFlgTarget = false;

	if (mFlgSelectNow == true) {

		for (int i = 0; i < mNumofObjects; ++i)
		{
			//mSceneNodeArr[i]->showBoundingBox(false);
		}
		if (left == right
			&&
			top == bottom)
		{
			mNumberOfPets = singleClickSelect(arg);
			bindAvatar_Selection( );

			cout << "mouseReleased_Selection:singleClickSelect:" << mNumberOfPets << endl;

		}
		else {
			mNumberOfPets = volumeSelection(arg);

			cout << "mouseReleased_Selection:volumeSelection:" << mNumberOfPets << endl;
		}
		mNumOfMovingObj = 0;

		for (int i = 0; i < mNumofObjects; ++i)
		{
			bool flg = mSceneNodeArr[i]->getShowBoundingBox();
			if (flg) mNumOfMovingObj++;
		}


		mFlgSelectNow = false;
		mSelectionRect->setVisible(false);
	}

	return false;
	//return BaseApplication::mouseReleased(arg, id);

}



//
// return the number of selected robots. In this case, it is one.
//
int BasicTutorial_00::singleClickSelect(const MouseButtonEvent& arg)
{
	int numSelectedObj = 0;	// number of selected objects

	Ray mRay = mTrayMgr->getCursorRay(mCamera);

	//mRaySceneQuery = mSceneMgr->createRayQuery(Ray());

	//mRaySceneQuery->setSortByDistance(true);

	//mRaySceneQuery->setRay(mRay);
	//Perform the scene query
	//RaySceneQueryResult& result = mRaySceneQuery->execute();
	//RaySceneQueryResult::iterator itr = result.begin();

	// Get the results, set the camera height
	// We are interested in the first intersection. It is ok to traverse all the results.
	//for (itr = result.begin(); itr != result.end(); itr++) {

		//if (itr->movable && itr->movable->getName().substr(0, 5) != "tile[" )
		//if ( itr->movable )
		//{
		//	if (itr->movable->getName().substr(0, 5) != "robot") continue;

		//	node = itr->movable->getParentSceneNode();
		//	
		//	if (mAvatarController->isSameAvatar(node)) continue;

		//	mCurrentObject = node;
		//	if (mCurrentObject == mSphere_Node) continue;
		//	flgShow = mCurrentObject->getShowBoundingBox();
		//	flgShow = !flgShow;
		//	mCurrentObject->showBoundingBox(flgShow);
		//	if (flgShow) numSelectedObj = 1;
		//	break;
		//} // if
	//}

	return numSelectedObj;
}

//
// Add your own stuff or modify
//
int BasicTutorial_00::volumeSelection(const MouseButtonEvent& arg)
{
	int numSelectedObj = 0;
	//
	if (left > right) {
		// left or right?
	}
	if (bottom < top) {
		// bottom or top?
	}

	cout << "left:" << left << endl;
	cout << "right:" << right << endl;
	cout << "top:" << top << endl;
	cout << "bottom:" << bottom << endl;

	Real nleft = left;
	Real nright = right;
	Real ntop = top;
	Real nbottom = bottom;
	//
	Ray topLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, ntop));
	Ray topRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, ntop));
	Ray bottomLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, nbottom));
	Ray bottomRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, nbottom));
	//End Using mTrayMgr=============

	// The plane faces the counter clockwise position.
	PlaneBoundedVolume vol;
	int np = 100;
	vol.planes.push_back(Plane(topLeft.getPoint(3), topRight.getPoint(3), bottomRight.getPoint(3)));         // front plane
	vol.planes.push_back(Plane(topLeft.getOrigin(), topLeft.getPoint(np), topRight.getPoint(np)));         // top plane
	vol.planes.push_back(Plane(topLeft.getOrigin(), bottomLeft.getPoint(np), topLeft.getPoint(np)));       // left plane
	vol.planes.push_back(Plane(bottomLeft.getOrigin(), bottomRight.getPoint(np), bottomLeft.getPoint(np)));   // bottom plane
	vol.planes.push_back(Plane(bottomRight.getOrigin(), topRight.getPoint(np), bottomRight.getPoint(np)));     // right plane 

	PlaneBoundedVolumeList volList;
	volList.push_back(vol);
	mVolQuery->setVolumes(volList);

	SceneQueryResult result = mVolQuery->execute();

	SceneQueryResultMovableList::iterator itr = result.movables.begin();


	// Get the results, set the camera height
	// We are interested in the first intersection. 
	// It is ok to traverse all the results.
	for (itr = result.movables.begin(); itr != result.movables.end(); ++itr)
	{
		if ((*itr)->getName().substr(0, 5) != "robot") continue;

		if (*itr)
		{
			
			mCurrentObject = (*itr)->getParentSceneNode();

			// is it the sphere node?
			if (mCurrentObject == mSphere_Node) {
				//
				// if yes, ignore this node. and check another node.
				//
				
				// mCurrentObject = 0;
				// continue;
			}

			// So mCurrentObject is a robot node.
			// Toggle the boundng box
			// Also, update the number of selected robots.
			bool flgShow = mCurrentObject->getShowBoundingBox();
			//flgShow = !flgShow;
			//mCurrentObject->showBoundingBox(flgShow);
			if (flgShow)  ++numSelectedObj;
		}
	}
	return numSelectedObj;

}