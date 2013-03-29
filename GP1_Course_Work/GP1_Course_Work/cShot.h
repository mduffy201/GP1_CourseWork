#ifndef _CSHOT_H
#define _CSHOT_H
#include "cSprite.h"
#include "cD3DXSpriteMgr.h"

class cShot: public cSprite{

private:
	bool mActive;
	//direction
	//owner
	eDirection direction;
	eShooter mShooter;
	
	//speed
public:
	cShot();
	cShot(eShooter shooter, D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename);
	//init
	//draw
	void update();
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();	
	void Draw(cD3DXSpriteMgr* d3dxSRMgr);
	eShooter getShooter();
};
#endif