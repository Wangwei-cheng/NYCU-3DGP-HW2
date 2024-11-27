//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#include <string>
#include "WeaponParticleSystemManager.h"

const std::string particleSystemNames[] = {
    "Examples/JetEngine1"
    ,"Examples/Rain"
    ,"Examples/JetEngine2"
    ,"Examples/Snow"
    ,"Examples/Smoke"
    ,"Examples/Fireworks"
    ,"Examples/upSmoke"
    ,"Examples/Smoke"
    ,"Examples/upSmoke"
    ,"Examples/Smoke"
    ,"Examples/upSmoke"
    ,"Examples/Smoke"
    ,"Examples/Snow"
    ,"Examples/Snow"
    ,"Examples/Snow"
    ,"Examples/Snow"
    ,"Examples/Snow"
    //"Examples/Smoke"
};

WeaponParticleSystemManager::WeaponParticleSystemManager( void )
        :mCurIndex( 0 )
{
}

WeaponParticleSystemManager::WeaponParticleSystemManager(
    SceneManager *sceneMgr
    ):
mCurIndex( 0 )
,SpecialEffectManager(
    sceneMgr,
    particleSystemNames,
    sizeof(particleSystemNames)/sizeof(std::string)
    )
{
    
}

int WeaponParticleSystemManager::getFreeParticleSystemIndex() const
{
    if (mCurIndex<0 || mCurIndex >= mNumParticleSystems) {
        mCurIndex = 0;
    }
    int index = mCurIndex;
    mCurIndex = (mCurIndex+1)%mNumParticleSystems;

    return index;
}

void WeaponParticleSystemManager::play(int pIndex, const Vector3 &p)
{
    if (pIndex<0 || pIndex >= mNumParticleSystems) {
        pIndex = 0;
    }
    setOffParticleSystem(pIndex, p);
}

void WeaponParticleSystemManager::play(const Vector3 &p)
{
    if (mCurIndex<0 || mCurIndex >= mNumParticleSystems) {
        mCurIndex = 0;
    }
    setOffParticleSystem(mCurIndex, p);
    mCurIndex = (mCurIndex+1)%mNumParticleSystems;
}


