#ifndef _CENEMY_H
#define _CENEMY_H
#include "cSprite.h"
#include "cShot.h"


class cEnemy:public cSprite{

private:
	int mID;
	bool mActive;
	eShooter mShooter;
	int rateOfFire;
	float shipSpeed;   
public:
	cEnemy();
	cEnemy(int ID,float speed,int fireRate, D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice);   //Constructor
	void update(LPDIRECT3DDEVICE9 pd3dDevice, vector<cShot*> &gShots);    //Update emeny position and shots
	void fire(LPDIRECT3DDEVICE9 pd3dDevice, vector<cShot*> &gShots);  //Add new shot to vector
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();    //Check if active

};
#endif