//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 
#ifndef __BASIC_TOOLS_H__
#define __BASIC_TOOLS_H__

#include <iostream>
#include <string>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

/**
 * This function 
 * 
 */

/**
* Define DO_NOT_SHOW_DEBUG_MESSAGE so no debug messages are shown.
* If DO_NOT_SHOW_DEBUG_MESSAGE is not defined, debug messages may be shown.
*/
//#define DO_NOT_SHOW_DEBUG_MESSAGE


/**
* Define DEBUG_PHASE so for each message, there is a pause.
* If DEBUG_PHASE is not defined, there is no pause after showing each message.
*/
//#define DEBUG_PHASE

/**
* ns_Debug_Tool contains some tools for showing messages for debugging purposes.
*/
namespace ns_Debug_Tool {
	template <typename T> void printf(T header, bool puase_flg = true) {
#ifndef DO_NOT_SHOW_DEBUG_MESSAGE
		std::cout << header << std::endl;
#ifdef DEBUG_PHASE
		if (puase_flg) system("pause");
#endif

#endif
	}

	template <typename T, typename T2> void printf(T header, T2 msg, bool puase_flg = true) {
#ifndef DO_NOT_SHOW_DEBUG_MESSAGE
		std::cout << header << "\t" << msg << std::endl;
#ifdef DEBUG_PHASE
		if (puase_flg) system("pause");
#endif
#endif
	}
};


/**
* This construct contains a light and a scene node.
*/
class LightConstruct {
public:
	LightConstruct(Ogre::SceneManager* creator);
	Ogre::Light* light;
	Ogre::SceneNode* lightNode;

	void setPosition(float x, float y, float z);
	void setPosition(const Ogre::Vector3 &p);
	void setDiffuseColour(float r, float g, float b);
	void setSpecularColour(float r, float g, float b);
};

/**
* This construct contains a camera and a scene node.
*/
class CameraConstruct {
public:
	CameraConstruct(const Ogre::String& cameraName, Ogre::SceneManager* creator);
	Ogre::Camera* camera;
	Ogre::SceneNode* cameraNode;
	void setPosition(float x, float y, float z);
	void setPosition(const Ogre::Vector3& p);
};

class ObjectConstruct {
public:
	ObjectConstruct( );
	Ogre::SceneNode* objNode;
	Ogre::Entity* ent;
	void setPosition(float x, float y, float z);
	void setPosition(const Ogre::Vector3& p);
};

/**
* This function generates a name combined with prefix and index.
* 
* @param prefix The prefix of the name.
* @param index The number appended to prefix.
* @param out_name The generated name for prefix and index.
*/
extern void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name);

extern Ogre::Quaternion slerp(
	const Ogre::Quaternion& v0
	, const Ogre::Quaternion& v1
	, Ogre::Real f);

#endif // #ifndef __BASIC_TOOLS_H__