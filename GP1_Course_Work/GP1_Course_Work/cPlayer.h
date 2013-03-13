#ifndef _CPLAYER_H
#define _CPLAYER_H
#include "cSprite.h"

class cPlayer: public cSprite{

private:
	int mScore;
	int mLives;
	float mSpeed;
	//D3DXVECTOR2 mScale;
	//float mRotation;
	//power;
public:
	//constructor
	cPlayer();
	cPlayer(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice);
	void update();	
	//void update(float dt);	
	//die
	void fire();
	float getSpeed();
	//setspeed
	
};
#endif