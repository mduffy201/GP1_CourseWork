#ifndef _CENEMYWAVE_H
#define _CENEMYWAVE_H
#include "cSprite.h"
#include "cEnemy.h"
#include "GameConstants.h"

class cEnemyWave{

private:
	int mID;
	
	list<cEnemy*> makeWave(RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice);
public:
	cEnemyWave(int ID,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice);
	list<cEnemy*> mWave;
};
#endif