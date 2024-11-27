//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#ifndef __WEAPONS_H__
#define __WEAPONS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include "WeaponParticleSystemManager.h"
#include "game_obj.h"
//
class WEAPON : public GAME_OBJ {
protected:
public:
	WEAPON(SceneManager *a_SceneMgr);
	virtual bool update(double dt);
	bool hitTarget_Sphere(const Vector3 &p, Real r );
    bool hitTarget_Sphere(
    const Vector3 &p, 
    Real r,
    WeaponParticleSystemManager *wpsMgr
    );
    void adjustDueToMap( );
};

#endif