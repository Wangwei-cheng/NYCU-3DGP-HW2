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


#ifndef __AVATAR_CONTROLLER__
#define __AVATAR_CONTROLLER__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "BasicTools.h"

using namespace Ogre;

#define ACTION_NONE	0x0000
#define ACTION_WALK_FORWARD	0x0001
#define ACTION_WALK_BACKWARD	0x0002
#define ACTION_WALK_TURNRIGHT	0x0004
#define ACTION_WALK_TURNLEFT	0x0008

enum AVATAR_CONTROLLER_MODE {
	AVATAR_CONTROLLER_MODE_TRACKING
	, AVATAR_CONTROLLER_MODE_FOLLOWING
};

class AVATAR_CONTROLLER {
public:
	AVATAR_CONTROLLER();
	AVATAR_CONTROLLER(SceneManager *sceneMgr);
	void setAvatar(SceneNode* avatarNode, CameraConstruct* cameraConstruct);
	virtual void setAvatarNode(SceneNode* avatarNode);
	virtual void setCameraConstruct(CameraConstruct* cameraConstruct);
	virtual void setYawDegree(double d);
	//
	virtual void setMode(AVATAR_CONTROLLER_MODE mode);
	virtual bool toggleActivation();
	virtual bool enable(bool flg);
		
	virtual void update(double dt);
	//
	
	//

	virtual bool isSameAvatar(const SceneNode *sceneNode) const;
	virtual bool isAvatarOn() const;
	//

	virtual void setWalkForward();
	virtual void setWalkBackward();
	virtual void unsetWalkForward();
	virtual void unsetWalkBackward();
	virtual unsigned int getActionMode() const;


protected:
	virtual void init();
	void update_Tracking(double dt);
	void update_Following(double dt);

	void walkForward(double dt);
	void walkBackward(double dt);

protected:
	SceneNode* mAvatarNode;
	CameraConstruct* mCameraConstruct;
	double mYawDegreeForLookAtDirectionAdjustment;
	AVATAR_CONTROLLER_MODE mMode;

	bool mEnabled;
	//

	Vector3 mEyePosition;
	//
	int mActionMode;
	Real mSpeedFactor;
	Real mSpeedFactor_Modifer;
};

#endif