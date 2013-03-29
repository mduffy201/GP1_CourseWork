#ifndef _CSTAGE_H
#define _CSTAGE_H
#include "cEnemy.h"
#include "GameConstants.h"

class cStage{

private:
	int mWaves;
	int mCounter;
public:
	cStage();
	void Update(list<cEnemy*> &eShips,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice);
};
#endif