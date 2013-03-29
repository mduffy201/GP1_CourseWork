#ifndef _CPLAYER_H
#define _CPLAYER_H
#include "cSprite.h"
#include "cShot.h"
#include "cD3DXSpriteMgr.h"
#include "GameConstants.h"

class cPlayer: public cSprite{

private:
	int mScore;
	int mLives;
	float mSpeed;
	vector<cShot*> gShots;
	eShooter mShooter;
public:
	//constructor
	cPlayer();
	cPlayer(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice);
	void update();	
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void fire(vector<cShot*> &gShots, LPDIRECT3DDEVICE9 pd3dDevice);

	//void fire(LPDIRECT3DDEVICE9 pd3dDevice);
	float getSpeed();
	void Draw(cD3DXSpriteMgr* d3dxSRMgr,float dt);
	vector<cShot*> getShots();
	void setShots(vector<cShot*> &gShots);
	
};
#endif