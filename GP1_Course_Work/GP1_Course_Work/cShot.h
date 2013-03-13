#ifndef _CSHOT_H
#define _CSHOT_H
#include "cSprite.h"
class cShot: public cSprite{

private:
	bool mActive;

	//RECT mSourceRect;
	//speed
public:
	cShot();
	cShot(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename);
	//init
	//draw
	void update(float dt);
	//RECT getSourceRect();
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();	
};
#endif