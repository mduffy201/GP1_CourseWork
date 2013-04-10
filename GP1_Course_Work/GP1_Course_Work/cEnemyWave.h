#ifndef _CENEMYWAVE_H
#define _CENEMYWAVE_H
#include "cSprite.h"
#include "cEnemy.h"
#include "GameConstants.h"

class cEnemyWave{

private:
	int mID;
	list<cEnemy*> makeWave(float speed,int fireRate,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice);    //Construct wave of enemies
public:
	cEnemyWave(int ID,float speed,int fireRate,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice);   //Constructor
	list<cEnemy*> mWave;   //collection of enemies

};
#endif