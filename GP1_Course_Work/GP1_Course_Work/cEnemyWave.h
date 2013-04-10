#ifndef _CENEMYWAVE_H
#define _CENEMYWAVE_H
#include "cSprite.h"
#include "cEnemy.h"
#include "GameConstants.h"

class cEnemyWave{

private:
	int mID;
	//int rateOfFire;
//	float shipSpeed;
	list<cEnemy*> makeWave(float speed,int fireRate,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice);
public:
	cEnemyWave(int ID,float speed,int fireRate,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice);
	list<cEnemy*> mWave;
		void setRateOfFire(int rate);
	void setShipSpeed(float speed);
};
#endif