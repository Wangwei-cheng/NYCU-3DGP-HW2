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
// For an object pair, push the objects away from each other if they collide.
// objA, objB: object indices
// rA, rB: object radiuses
//
void BasicTutorial_00::resolveCollisionObjectPair(
	int objA, int objB, float rA, float rB)
{
	Vector3 posA = mSceneNodeArr[objA]->getPosition();
	Vector3 posB = mSceneNodeArr[objB]->getPosition();
	float R = rA + rB;
	Real soft_factor = 0.5;

	Vector3 vAB = posA - posB;
	vAB.y = 0; // ignore y-coordinate difference

	float d = vAB.length();
	if (R > d) {
		if (d == 0.0)	vAB = Vector3(1.0, 0.0, 0.0);
		vAB.normalise();

		double delta = R - d;

		mSceneNodeArr[objA]->translate(vAB * soft_factor * delta);
		mSceneNodeArr[objB]->translate(-vAB * soft_factor * delta);
	}
}

//
// Detect and resolve collisions for robots.
//
void BasicTutorial_00::resolveCollisionForObjects()
{
	//float ri = 25; // object radius
	//float rj = 25; // object radius

	float ri = mObject_radius;
	float rj = mObject_radius;

	for (int i = 0; i < mNumofObjects; ++i)
	{
		for (int j = i + 1; j < mNumofObjects; ++j) {
			resolveCollisionObjectPair(i, j, ri, rj);
		}
	}
}

//
// Collision detection and handling between each robot and the large shere.
//
void BasicTutorial_00::resolveCollisionBetweenObjectsAndSphere()
{
	//Real soft_factor = 0.1;
	//Real soft_factor = 0.98;
	Real soft_factor = 0.5;

	Vector3 q = mSphere_Position;
	q.y = 0.0;

	for (int i = 0; i < mNumofObjects; ++i)
	{
		Vector3 p = mSceneNodeArr[i]->getPosition(); // robot position
		p.y = 0.0;
		Vector3 pp = p - q;
		Real len = pp.length();
		if (len >= mObject_radius + mSphere_Radius)	continue;
		if (len == 0.0)	pp = Vector3(1.0, 0.0, 0.0);
		pp.normalise();

		double delta = mSphere_Radius + mObject_radius - len;

		mSceneNodeArr[i]->translate(pp * soft_factor * delta);
	}
}
//
// Perform collision handling.
//
// Step 1. Resolve collision between objects.
// Step 2. Resolve collision between objects and the large sphere.
//
void BasicTutorial_00::performCollisionHandling(Real dt)
{
	for (int i = 0; i < 7; ++i) {
		resolveCollisionForObjects();
	}
	resolveCollisionBetweenObjectsAndSphere();
}