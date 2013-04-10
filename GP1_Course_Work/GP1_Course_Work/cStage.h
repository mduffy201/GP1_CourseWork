#ifndef _CSTAGE_H
#define _CSTAGE_H
#include "cEnemy.h"
#include "GameConstants.h"

class cStage{

private:
	int mWaves;
	int mCounter;
	bool active;
	int rateOfFire;
	float speed;
public:
	cStage();   //Constructor
	void Update(list<cEnemy*> &eShips,RECT clientBounds,LPDIRECT3DDEVICE9 pd3dDevice);    //Update satge, introduce enemy waves
	bool isActive();   //Check if active
	void startLevel();     //Initialise level
};
#endif