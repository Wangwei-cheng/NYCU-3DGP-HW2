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

#include "avatar_controller.h"


AVATAR_CONTROLLER::AVATAR_CONTROLLER(): AVATAR_CONTROLLER(nullptr){
	
}
AVATAR_CONTROLLER::AVATAR_CONTROLLER(SceneManager* sceneMgr) {
	init();
}

void AVATAR_CONTROLLER::init() {
	mAvatarNode = nullptr;
	mCameraConstruct = nullptr;
	mYawDegreeForLookAtDirectionAdjustment = 0;

	mMode = AVATAR_CONTROLLER_MODE_TRACKING;
	mEnabled = true;
	//mEnabled = false;
	//

	mEyePosition = Vector3(0, 120, 0);
	//
	mActionMode = ACTION_NONE;
	//
	mSpeedFactor = 200.0;
	mSpeedFactor_Modifer = 2.0;

	//mActionMode |= ACTION_WALK_FORWARD;
}

bool AVATAR_CONTROLLER::isAvatarOn() const
{
	return mEnabled && (mAvatarNode!=nullptr);
}

void AVATAR_CONTROLLER::setAvatar(SceneNode* avatarNode, CameraConstruct* cameraConstruct) {
	mAvatarNode = avatarNode;
	mCameraConstruct = cameraConstruct;

}

void AVATAR_CONTROLLER::setAvatarNode(SceneNode* avatarNode) {
	mAvatarNode = avatarNode;

}

void AVATAR_CONTROLLER::setCameraConstruct(CameraConstruct* cameraConstruct) {
	mCameraConstruct = cameraConstruct;

}

void AVATAR_CONTROLLER::setMode(AVATAR_CONTROLLER_MODE mode)
{
	mMode = mode;
}

bool AVATAR_CONTROLLER::toggleActivation()
{
	//mEnabled = !mEnabled;
	//return mEnabled;

	return (mEnabled = !mEnabled);
}
bool AVATAR_CONTROLLER::enable(bool flg)
{
	mEnabled = flg;
	return mEnabled;
}

bool AVATAR_CONTROLLER::isSameAvatar(const SceneNode* sceneNode) const
{
	if (!mEnabled) return false;
	return (mAvatarNode == sceneNode);
}

void AVATAR_CONTROLLER::update_Following(double dt) {

}

//
// Move the camera smoothly to the selected avatar.
// Add your own stuff or modify.
//
void AVATAR_CONTROLLER::update_Tracking(double dt) 
{
	Vector3 q = mAvatarNode->getPosition();

	Vector3 p = q;

	p += Vector3(0, 1, 0);

	Vector3 cp = mCameraConstruct->cameraNode->getPosition();

	double f = 2.5;

	cp = cp + f * (p - cp);
	
	mCameraConstruct->cameraNode->setPosition(cp);
}

void AVATAR_CONTROLLER::update(double dt) 
{
	if (mAvatarNode == nullptr || mCameraConstruct == nullptr) return;
	if (!mEnabled) return;

	switch (mMode) {
	case AVATAR_CONTROLLER_MODE_TRACKING:
		update_Tracking(dt);
		break;
	case AVATAR_CONTROLLER_MODE_FOLLOWING:
		update_Following(dt);

		break;
	}

	if (mActionMode & ACTION_WALK_FORWARD) {
		walkForward(dt);
	}
	
	//
	// add your own stuff for backward movement
	//
}

void AVATAR_CONTROLLER::setYawDegree(double d) {
	mYawDegreeForLookAtDirectionAdjustment = d;
}


unsigned int AVATAR_CONTROLLER::getActionMode() const {
	return mActionMode;
}

void AVATAR_CONTROLLER::setWalkForward()
{
	mActionMode |= ACTION_WALK_FORWARD;
}
void AVATAR_CONTROLLER::setWalkBackward()
{
	//mActionMode |= ACTION_WALK_BACKWARD;

}

void AVATAR_CONTROLLER::unsetWalkForward()
{
	mActionMode ^= ACTION_WALK_FORWARD;
}
void AVATAR_CONTROLLER::unsetWalkBackward()
{
	//mActionMode ^= ACTION_WALK_BACKWARD;

}

//
// Main steps
// (1) Update the position of the avatar.
// (2) Adjust the orientation of the avatar.
//
void AVATAR_CONTROLLER::walkForward(double dt)
{
    Quaternion cq = mCameraConstruct->cameraNode->getOrientation();
    Vector3 initial_dir = Vector3(0, 0, -1); // initial direction
    Vector3 view_dir = cq * initial_dir;

	view_dir.y = 0;
	if (view_dir.x == 0.0 && view_dir.z == 0) {
		view_dir.x = 1.0;
	}
	else {
		view_dir.normalise();
	}
	//displacement vector
    Vector3 dis = view_dir * mSpeedFactor * dt
        * mSpeedFactor_Modifer; 


	//SceneNode* node = mCameraConstruct->cameraNode;
	SceneNode *node = mAvatarNode;
	node->translate(dis);

	/////////////////////////////////////
	//Adjust the orientation of the robot
	/////////////////////////////////////
	Quaternion q0 = mAvatarNode->getOrientation();

	Vector3 p = mAvatarNode->getPosition();

	//
	// Add your own stuff or modify
	//
}

void AVATAR_CONTROLLER::walkBackward(double dt)
{
	Quaternion cq = mCameraConstruct->cameraNode->getOrientation();
	
	Vector3 initial_dir = Vector3(0, 0, -1);	// initial direction
	//////////////////////////////////////////////////////////
	// This line dose not work. It does not reverse the direction correctly.
	// Why? The operator * is overloaded. It does not operate in the way that we think: 
	// - (cq * initial_dir) != -cq * initial_dir
	// 
	// Vector3 view_dir = -cq * initial_dir;
	//////////////////////////////////////////////////////////
	// The correct way to get the reverse direction of the camera direction.
	Vector3 view_dir = cq * initial_dir;		
	view_dir = -view_dir; // reverse direction
	//////////////////////////////////////////////////////////


	view_dir.y = 0;
	if (view_dir.x == 0.0 && view_dir.z == 0) {
		view_dir.x = 1.0;
	}
	else {
		view_dir.normalise();
	}

	//displacement vector
	Vector3 dis = view_dir * mSpeedFactor * dt
		* mSpeedFactor_Modifer;


	SceneNode* node = mAvatarNode;
	node->translate(dis);

	
	/////////////////////////////////////
	//Adjust the orientation of the robot
	/////////////////////////////////////
	Quaternion q0 = mAvatarNode->getOrientation();

	Vector3 p = mAvatarNode->getPosition();
	p = p - view_dir;

	//
	// Add your own stuff or modify
	//
}