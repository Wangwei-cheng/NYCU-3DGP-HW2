//
// Student Name:
// Student ID:
// Student Email Address:
//
//
//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#ifndef __WeaponParticleSystemManager_h_
#define __WeaponParticleSystemManager_h_
 
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreParticleSystem.h>
#include <OgreParticleEmitter.h>
#include <string>

#include "SpecialEffectManager.h"

using namespace Ogre;

class WeaponParticleSystemManager: public SpecialEffectManager {

protected:
    mutable int mCurIndex;
public:
    WeaponParticleSystemManager();
    WeaponParticleSystemManager(SceneManager *sceneMgr);
   
    virtual void play(const Vector3 &pos);
    virtual void play(int pIndex, const Vector3 &p);
    virtual int getFreeParticleSystemIndex() const;
};

#endif
