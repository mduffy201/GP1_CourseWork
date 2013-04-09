#ifndef _CENEMY_H
#define _CENEMY_H
#include "cSprite.h"
#include "cShot.h"
//#include "GameConstants.h"

class cEnemy:public cSprite{

private:
	int mID;
	int mPoints;
	float mSpeed;
	bool mActive;
	eShooter mShooter;
	D3DXVECTOR3 startPosition;
	//vector<cShot*> gShots;
public:
	cEnemy();
	cEnemy(int ID, D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice);
	void update(LPDIRECT3DDEVICE9 pd3dDevice, vector<cShot*> &gShots);
	void fire(LPDIRECT3DDEVICE9 pd3dDevice, vector<cShot*> &gShots);
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();
	vector<cShot*>	getShots();
//	list<cEnemy*> getShips(list<cEnemy*> eShips, RECT clientBounds, LPDIRECT3DDEVICE9 pd3dDevice);
};
#endif