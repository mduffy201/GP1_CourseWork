#ifndef _CSHOT_H
#define _CSHOT_H
#include "cSprite.h"
#include "cD3DXSpriteMgr.h"

class cShot: public cSprite{

private:
	bool mActive;
	eDirection direction;
	eShooter mShooter;
	
public:
	cShot();
	cShot(eShooter shooter, D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename);   //constructor
	void update();   //Update shots position
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();	   //Check if active
	eShooter getShooter();    //Return shots "owner"
};
#endif