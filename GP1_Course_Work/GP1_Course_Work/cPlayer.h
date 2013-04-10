#ifndef _CPLAYER_H
#define _CPLAYER_H
#include "cSprite.h"
#include "cShot.h"
#include "cD3DXSpriteMgr.h"
#include "GameConstants.h"

class cPlayer: public cSprite{

private:

	float mSpeed;
	vector<cShot*> gShots;
	eShooter mShooter;
	bool bActive;
public:
	
	cPlayer(); //constructor
	cPlayer(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice);
	void update();	  //Update player position
	void moveUp();   //Move player up
	void moveDown();    //Move player down
	void moveLeft();   // Move player left
	void moveRight();   //Mover player right
	void fire(vector<cShot*> &gShots, LPDIRECT3DDEVICE9 pd3dDevice);    // Add new shot to collection
	void Death();     // Kill player
	bool isActive();    //Check if active
	void Respawn();    //Respawn player
};
#endif