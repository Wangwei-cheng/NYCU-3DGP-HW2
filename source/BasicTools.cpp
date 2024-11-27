//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#include "BasicTools.h"

void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name)
{
	out_name= prefix + Ogre::StringConverter::toString(static_cast<int>(index));
}

/**
 This function uses a scene manager to create a light and a scene node.
 Then it initializes the light and the scene node. 
 After that, attach the light to the scene node.
 */
LightConstruct::LightConstruct(Ogre::SceneManager* creator)
{
    light = creator->createLight();
    lightNode = creator
        ->getRootSceneNode()
        ->createChildSceneNode();
    lightNode->attachObject(light);
}

void LightConstruct::setPosition(float x, float y, float z) {
    lightNode->setPosition(x, y, z);
}

void  LightConstruct::setPosition(const Ogre::Vector3& p)
{
    lightNode->setPosition( p );

}
void LightConstruct::setDiffuseColour(float r, float g, float b) {
    light->setDiffuseColour(r, g, b);

}
void LightConstruct::setSpecularColour(float r, float g, float b) {
    light->setSpecularColour(r, g, b);

}

/**
 This function uses a scene manager to create a camera with a name and a scene node.
 The camera is attached to the scene node.
 */
CameraConstruct::CameraConstruct(
    const Ogre::String& cameraName
    , Ogre::SceneManager* creator)
{
    camera = creator->createCamera(cameraName);
    cameraNode = creator
        ->getRootSceneNode()
        ->createChildSceneNode();
    cameraNode->setFixedYawAxis(true); // important. Read the manual for details
    cameraNode->attachObject(camera);
}

void CameraConstruct::setPosition(float x, float y, float z)
{
    cameraNode->setPosition(x, y, z);
}

void CameraConstruct::setPosition(const Ogre::Vector3& p)
{
    cameraNode->setPosition(p);

}

ObjectConstruct::ObjectConstruct( )
{
    objNode = nullptr;
    ent = nullptr;
}

void ObjectConstruct::setPosition(float x, float y, float z)
{
    objNode->setPosition(x, y, z);
}

void ObjectConstruct::setPosition(const Ogre::Vector3& p)
{
    objNode->setPosition(p);

}

//
// v0: current orientation
// v1: desired orientation
// Output: the intermediate orientation
// 
// f in (0, 1]. how fast the orientation is changed towards the desired orientation.
//
Ogre::Quaternion slerp(
    const Ogre::Quaternion& v0
    , const Ogre::Quaternion& v1
    , Ogre::Real f)
{
    //v0.normalise();
    //v1.normalise();

    Ogre::Quaternion u0 = v0;
    Ogre::Quaternion u1 = v1;

    Ogre::Real dot = u0.Dot(u1);
    if (dot < 0.0f) {
        u1 = -u1;
        dot = -dot;
    }
    const Ogre::Real threshold = 0.995;
    if (dot > threshold) {
        Ogre::Quaternion result = u0 + f * (u1 - u0);
        result.normalise();
        return result;
    }

    Ogre::Real theta_0 = acos(dot);
    Ogre::Real theta = theta_0 * f;
    Ogre::Real sin_theta = sin(theta);
    double sin_theta_0 = sin(theta_0);
    double s0 = cos(theta) - dot * sin_theta / sin_theta_0;
    Ogre::Real s1 = sin_theta / sin_theta_0;
    return (s0 * u0) + (s1 * u1);
}