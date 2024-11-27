//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#include "weapon_manager.h"
//#include "map_manager.h"
#include "reader_data.h"

WEAPON_MANAGER::WEAPON_MANAGER(SceneManager* a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
	mCoolDownTimeForFiring = 0.0;
	mMaxCoolDownTime = 0.1;
	//
	mMaxNum = 128;
	mCurBulletsNum = mMaxNum;
	for (int i = 0; i < mMaxNum; ++i) {
		mUsedWeaponsArr[i] = false;
		mBulletsArr[i] = new WEAPON(mSceneMgr);
		mBulletsArr[i]->createGameObj("b", "sphere.mesh");
		mBulletsArr[i]->scale(0.05, 0.05, 0.05);
		mBulletsArr[i]->setVisible(false);
		mBulletsArr[i]->getEntity()->setMaterialName("Examples/RustySteel");
	}
	mFlgTarget = false;
	//
	mWeaponParticleSystemManager = 0;
}

void WEAPON_MANAGER::setTarget(const Vector3& pos, Real radius)
{
	mTargetPos = pos;
	mTargetRadius = radius;
	mFlgTarget = true;
}


void WEAPON_MANAGER::setMaxBulletsNum(int a_Num)
{
	if (a_Num >= mMaxNum) {
		a_Num = mMaxNum;
	}

	mCurBulletsNum = a_Num;
}

void WEAPON_MANAGER::fire_Normal(const Vector3& pos, const Vector3& direction)
{

	WEAPON* g = 0;
	for (int i = 0; i < mCurBulletsNum; ++i) {
		if (mUsedWeaponsArr[i] == true) continue;
		g = mBulletsArr[i];
		mUsedWeaponsArr[i] = true;
		break;
	}
	if (g == 0) return;
	if (mCoolDownTimeForFiring < mMaxCoolDownTime) return;
	mCoolDownTimeForFiring = 0;
	g->setPosition(pos);
	float bullet_speed = READER_DATA::getBulletSpeed();
	g->setVelocity(direction * bullet_speed);
	g->setSpeedFactor(1);
	g->setLife(5, 5);
	g->makeAlive();
	//
	g->adjustDueToMap();

	//
}

void WEAPON_MANAGER::installWeaponWSManager(WeaponParticleSystemManager* wpsMgr)
{
	mWeaponParticleSystemManager = wpsMgr;
}

bool WEAPON_MANAGER::update(double dt)
{
	mCoolDownTimeForFiring += dt;
	if (mCoolDownTimeForFiring > mMaxCoolDownTime)
	{
		mCoolDownTimeForFiring = mMaxCoolDownTime;
	}
	for (int i = 0; i < mMaxNum; ++i) {
		if (mUsedWeaponsArr[i] == false) continue;
		WEAPON* g = mBulletsArr[i];
		g->update(dt);

		if (mFlgTarget) {
			if (!mWeaponParticleSystemManager) {
				g->hitTarget_Sphere(
					mTargetPos,
					mTargetRadius
				);
			}
			else {
				g->hitTarget_Sphere(
					mTargetPos,
					mTargetRadius,
					mWeaponParticleSystemManager
				);
			}
		}
		if (!g->isAlive()) {
			mUsedWeaponsArr[i] = false;
		}
	}
	return true; // Alive
}

void WEAPON_MANAGER::init_Traversal() {
	mCounter_Traversal = 0;
}

WEAPON* WEAPON_MANAGER::getObj_Traversal()
{
	WEAPON* w = nullptr;
	if (mCounter_Traversal >= mMaxNum) return w;
	while (mCounter_Traversal < mMaxNum) {
		++mCounter_Traversal;
		if (mUsedWeaponsArr[mCounter_Traversal-1]) {
			w = mBulletsArr[mCounter_Traversal-1];
			break;
		}
	}
	return w;
}