//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2022/10/05
//

#include "weapons.h"
#include "BasicTools.h"
//#include "sound.h"
//#include "sound_manager.h"
//#include "map_manager.h"

//extern SOUND* mSound;
WEAPON::WEAPON(SceneManager* a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
}

bool WEAPON::hitTarget_Sphere(
	const Vector3& p,
	Real r)
{
	bool flg = false;
	Vector3 pos = mSceneNode->getPosition();
	if (r >= pos.distance(p)) {
		Vector3 normal_dir = pos - p;
		normal_dir.normalise();
		Vector3 new_pos = p + (r + 0.5) * normal_dir;
		mSceneNode->setPosition(new_pos);
		Real d = mVelocity.dotProduct(normal_dir);
		if (0.0 >= d) {
			mVelocity = mVelocity - d * normal_dir;
			//mSound->init();
			//mSound->play();
			//SOUND_MANAGER::getInstance()->play_Explosion();

		}
		flg = true;
	}
	return flg;
}

bool WEAPON::hitTarget_Sphere(
	const Vector3& p,
	Real r,
	WeaponParticleSystemManager* wpsMgr
)
{
	bool flg = false;
	Vector3 pos = mSceneNode->getPosition();
	if (r >= pos.distance(p)) {
		Vector3 normal_dir = pos - p;
		normal_dir.normalise();
		Vector3 new_pos = p + (r + 0.5) * normal_dir;
		mSceneNode->setPosition(new_pos);
		Real d = mVelocity.dotProduct(normal_dir);
		if (0.0 >= d) {
			mVelocity = mVelocity - d * normal_dir;
			//mSound->init();
			//mSound->play();
			//SOUND_MANAGER::getInstance()->play_Explosion();
			wpsMgr->play(pos);

		}
		flg = true;
	}
	return flg;
}

//
// dt: simulation time step size
//
bool WEAPON::update(double dt)
{
	if (!mIsAlive) {
		return mIsAlive;
	}
	mLifeTime -= dt;
	if (mLifeTime < 0) {
		mLifeTime = 0;
		mSceneNode->setVisible(false);
		mIsAlive = false;
		return mIsAlive;
	}
	Vector3 pos = mSceneNode->getPosition();
	Vector3 old_pos = pos;

	pos += mVelocity * dt;

	Vector3 grav(0, -29.8, 0);
	mVelocity += grav * dt;

	/*
	Vector3 new_pos = pos;
	Real r = 5;
	new_pos -= Vector3(0, 1, 0) * r;
	bool flg = basicTool_projectScenePointOntoTerrain_PosDirection(new_pos);
	if (flg) {
		pos = new_pos + Vector3(0, 1.0, 0) + Vector3(0, 1, 0) * r;
		mVelocity.y = -mVelocity.y * 0.9;
	}
	//
	Vector3 modified_p;
	modified_p = pos;
	MAP_MANAGER::movePosition(old_pos, pos, modified_p);
	if (pos != modified_p)
	{
		Vector3 n = MAP_MANAGER::getGridNormalVector(modified_p.x, modified_p.z);
		Real len = n.length();
		if (len != 0.0) {
			float d = mVelocity.dotProduct(n);

			//mVelocity.x = -mVelocity.x;
			//mVelocity.z = -mVelocity.z;
			Vector3 new_v = mVelocity - 2 * d * n;
			mVelocity = new_v;

			cout << "normal:" << n.x << "\t" << n.y << "\t" << n.z << endl;

		}
		pos = modified_p;
	}
	*/
	//
	mSceneNode->setPosition(pos);
	return mIsAlive;
}

void WEAPON::adjustDueToMap()
{
	/*
	Vector3 pos = mSceneNode->getPosition();
	Vector3 n = MAP_MANAGER::getGridNormalVector(pos.x, pos.z);
	Real len = n.length();
	if (len != 0.0) {
		float d = mVelocity.dotProduct(n);

		//mVelocity.x = -mVelocity.x;
		//mVelocity.z = -mVelocity.z;
		Vector3 new_v = mVelocity - 2 * d * n; // reflectance direction
		mVelocity = new_v;

		//  cout << "normal:" << n.x << "\t" << n.y << "\t" << n.z << endl;

	}
	*/
}